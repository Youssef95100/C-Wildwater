# C-Wildwater

Projet C-Wildwater

groupe: MEF1-C
composé de: GALIZZI Lucas, El IDRISSI Youssef, MAHYO Nawfal

Description du projet:
C-WildWater est une application hybride (Shell/C) dédiée à l'analyse de données massives pour les réseaux de distribution d'eau. Elle combine l'efficacité du Shell pour le nettoyage et le filtrage des données avec la puissance du C pour la modélisation structurelle, notamment via les AVL.

Comment utiliser notre programme:

1. Cloner le dépôt avec la commande : git clone https://github.com/Youssef95100/C-Wildwater

2. Se déplacer dans le bon dossier si nécessaire: cd C-Wildwater

2.1. AJOUTER LE FICHIER c-wildwater_v3.dat (OU LE FICHIER QUE VOUS SHOUAITEZ ANALYSER) :Le fichier de données étant trop volumineux pour GitHub (500 Mo), il doit être ajouté manuellement.

    2.2.  Téléchargez ou récupérez le fichier `c-wildwater_v3.dat`.
    2.3.  Placez-le à la racine du dossier du projet.

3. On vérifie que les fichiers sont présents: ls -l

4. On rend le script éxecutable: chmod +x c-wildwater.sh

5. On compile la partie C : make

6. Pour le calcul max: ./c-wildwater.sh c-wildwater_v3.dat histo max

7. Pour afficher l'histogramme du calcul max: xdg-open graph_max.png

8. Pour le calcul src: ./c-wildwater.sh c-wildwater_v3.dat histo src

9. Pour afficher l'histogramme du calcul src: xdg-open graph_src.png

10. Pour le calcul real: ./c-wildwater.sh c-wildwater_v3.dat histo real

11. Pour afficher l'histogramme du calcul real: xdg-open graph_real.png

12. Pour lancer le calcul de perte d'eau pour une usine comme par exemple Plant #SO200633G: ./c-wildwater.sh c-wildwater_v3.dat leaks "Plant #SO200633G"

13. Pour ré-afficher la perte d'eau sur l'usine précedente: cat leaks.csv