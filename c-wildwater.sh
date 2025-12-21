#!/bin/bash

# Ce script automatise l'intégralité du flux de travail :
# 1. Validation de l'environnement : Vérification des arguments, existence du fichier CSV.
# 2. Compilation : Appel automatique du Makefile si l'exécutable 'c-wire' est absent.
# 3. Pré-traitement ETL : Nettoyage des données (suppression '\r') et filtrage 
#    spécifique via AWK selon le mode choisi.
# 4. Traitement : Exécution du programme C pour l'agrégation et le tri via AVL.
# 5. Post-traitement & Visualisation :
#    - Mode 'histo' : Tri final, extraction des extrêmes (Top 10 / Bottom 50) 
#      et génération de graphiques via Gnuplot.
#    - Mode 'leaks' : Analyse ciblée des fuites pour une station donnée.
#
# Usage : ./c-wildwater.sh <fichier_csv> <commande> <argument>
# Commandes supportées : histo (max, src, real, hvb, hva, lv), leaks <ID>



START_TIME=$(date +%s%3N)


fin_script() {
    CODE_RETOUR=$1
    END_TIME=$(date +%s%3N)
    DURATION=$((END_TIME - START_TIME))
    echo "Durée totale : ${DURATION} ms"
    exit $CODE_RETOUR
}


if [ "$1" = "-h" ]; then
    echo "Usage: $0 <fichier_csv> <commande> <argument>"
    echo "Commandes : histo (max, src, real, hvb, hva, lv) | leaks <ID>"
    fin_script 0
fi

if [ "$#" -ne 3 ]; then
    echo "Erreur : Nombre d'arguments incorrect."
    fin_script 1
fi

FICHIER_CSV="$1"
COMMANDE="$2"
ARGUMENT="$3"

if [ ! -f "$FICHIER_CSV" ]; then
    echo "Erreur : Le fichier '$FICHIER_CSV' est introuvable."
    fin_script 1
fi


if [ ! -x "c-wire" ]; then
    echo "Compilation en cours..."
    make
    if [ $? -ne 0 ]; then
        echo "Erreur : La compilation a échoué."
        fin_script 1
    fi
fi


TMP_INPUT="input_data.tmp"
TMP_STATS="stats.csv"
FICHIER_PROPRE="clean_data.tmp"

tr -d '\r' < "$FICHIER_CSV" > "$FICHIER_PROPRE"

if [ "$COMMANDE" = "histo" ]; then
    echo "Traitement en mode HISTOGRAMME ($ARGUMENT)..."
    
    case "$ARGUMENT" in
        "max")
            awk -F';' 'NR>1 && $2 ~ "Plant" && $4 != "-" { print $2";"$4";0" }' "$FICHIER_PROPRE" > "$TMP_INPUT"
            COL_TRI=2
            TITRE="Capacité Maximale (Plants)"
            ;;
        "src")
            awk -F';' 'NR>1 && $2 ~ "Source|Spring|Resurgence|Well|Fountain" { print $3";0;"$4 }' "$FICHIER_PROPRE" > "$TMP_INPUT"
            COL_TRI=3
            TITRE="Volume Capté (Sources)"
            ;;
        "real")
            awk -F';' 'NR>1 && $2 ~ "Source|Spring|Resurgence|Well|Fountain" { 
                vol=$4; fuite=($5=="-"?0:$5); 
                reel=vol*(1-fuite/100); 
                printf "%s;0;%.6f\n", $3, reel 
            }' "$FICHIER_PROPRE" > "$TMP_INPUT"
            COL_TRI=3
            TITRE="Volume Réel Traité"
            ;;
        "hvb")
            awk -F';' 'NR>1 && $2 == "HVB" && $7 != "-" { print $2";"$7";"$8 }' "$FICHIER_PROPRE" > "$TMP_INPUT"
            COL_TRI=2
            TITRE="Stations HVB"
            ;;
        "hva")
            awk -F';' 'NR>1 && $2 == "HVA" && $7 != "-" { print $2";"$7";"$8 }' "$FICHIER_PROPRE" > "$TMP_INPUT"
            COL_TRI=2
            TITRE="Stations HVA"
            ;;
        "lv")
            awk -F';' 'NR>1 && $2 == "LV" && $8 != "-" { print $2";"$7";"$8 }' "$FICHIER_PROPRE" > "$TMP_INPUT"
            COL_TRI=3
            TITRE="Consommation LV"
            ;;
        *)
            echo "Erreur : Argument '$ARGUMENT' non géré pour histo."
            fin_script 1
            ;;
    esac

    if [ ! -s "$TMP_INPUT" ]; then
        echo "Erreur : Aucune donnée trouvée pour '$ARGUMENT'."
        fin_script 1
    fi

    ./c-wire "$TMP_INPUT"
    
    if [ ! -s "$TMP_STATS" ]; then
        echo "Erreur : Le programme C a échoué."
        fin_script 1
    fi

    sort -t';' -k"${COL_TRI},${COL_TRI}nr" "$TMP_STATS" > "sorted_all.tmp"

    FICHIER_MAX="histo_${ARGUMENT}_max.csv"
    echo "Station;Valeur" > "$FICHIER_MAX"
    head -n 10 "sorted_all.tmp" >> "$FICHIER_MAX"

    FICHIER_MIN="histo_${ARGUMENT}_min.csv"
    echo "Station;Valeur" > "$FICHIER_MIN"
    tail -n 50 "sorted_all.tmp" >> "$FICHIER_MIN"
    
    echo "Fichiers générés : $FICHIER_MAX et $FICHIER_MIN"

    if command -v gnuplot &> /dev/null; then
        gnuplot -persist <<-EOF
            # Configuration globale de l'image (haute résolution pour 2 graphes)
            set terminal png size 1600,900 enhanced font "Arial,10"
            set output 'graph_${ARGUMENT}.png'
            
            set datafile separator ";"
            set grid y
            set style data histograms
            set style fill solid 1.0 border -1
            
            # Configuration Multiplot (1 ligne, 2 colonnes)
            set multiplot layout 1,2 title "Statistiques : ${TITRE}" font "Arial,16"
            
            # --- GRAPHIQUE 1 : TOP 10 (GAUCHE) ---
            set title "Top 10 (Les plus grands)" font "Arial,12"
            set ylabel "Volume (m3)"
            set boxwidth 0.7 relative
            set xtics rotate by -45 font "Arial,10"
            set bmargin 10
            # Couleur Verte
            plot "$FICHIER_MAX" using ${COL_TRI}:xtic(1) notitle linecolor rgb "#2E8B57"
            
            # --- GRAPHIQUE 2 : BOTTOM 50 (DROITE) ---
            set title "Les 50 plus petits" font "Arial,12"
            
            # MODIFICATION ICI : On remet le ylabel pour le graphique de droite
            set ylabel "Volume (m3)"
            
            set boxwidth 0.9 relative
            # Police plus petite pour faire tenir 50 noms sur l'axe X
            set xtics rotate by -45 font "Arial,6" 
            set bmargin 10
            # Couleur Rouge pour différencier
            plot "$FICHIER_MIN" using ${COL_TRI}:xtic(1) notitle linecolor rgb "#B22222"
            
            unset multiplot
EOF
        echo "Graphique double généré : graph_${ARGUMENT}.png"
    fi
    
    rm -f "sorted_all.tmp"

elif [ "$COMMANDE" = "leaks" ]; then
    echo "Traitement en mode LEAKS (Station : $ARGUMENT)..."

    awk -F';' 'NR>1 && $1!="" && $2!="" { 
        vol = ($4 == "-" ? 0 : $4);
        fuite = ($5 == "-" ? 0 : $5);
        print $1";"$2";"vol";"fuite 
    }' "$FICHIER_PROPRE" > "$TMP_INPUT"
    
    ./c-wire "$TMP_INPUT" "$ARGUMENT"
    
    if [ -s "$TMP_STATS" ]; then
        mv "$TMP_STATS" "leaks.csv"
        
        echo "Fichier généré : leaks.csv"
        echo "Resultat :"
        sed "s/$/ m3 de fuite d'eau/" "leaks.csv"
    else
        echo "Station '$ARGUMENT' introuvable ou erreur."
        rm -f "leaks.csv" 
    fi
else
    echo "Erreur : Commande inconnue."
    fin_script 1
fi

fin_script 0