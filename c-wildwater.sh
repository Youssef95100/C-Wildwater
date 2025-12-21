#!/bin/bash

option=$1

if [ $# -eq 0 ]; then
    echo "Erreur : Arguments manquants."
    echo "Usage : ./myScript.sh histo ou ./myScript.sh leaks"
    exit 1
fi

if [ "$option" = "histo" ]; then
    echo "Vous avez choisi l'histogramme."

elif [ "$option" = "leaks" ]; then
    echo "Vous avez choisi le calcul des fuites."
    # a completer (avec le programme C) #

else
    # a completer (si l'user ecrit nimporte quoi) #
    echo "Erreur : Option '$option' inconnue."
    exit 1
fi