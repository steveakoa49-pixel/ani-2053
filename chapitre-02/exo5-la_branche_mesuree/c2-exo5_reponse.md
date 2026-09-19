# Exercice 5 : La branche, mesurée

## Mesures de taille du dossier .git
- Taille initiale (avant la branche) : 57,2666 Ko
- Taille après 3 commits sur la branche : 62,3554 Ko
- Différence observée : +5,0888 Ko

## Explication des résultats
La création d'une branche dans Git n'occupe quasiment aucun espace disque supplémentaire (environ 41 octets pour créer un simple fichier pointeur dans `.git/refs/heads/`).

L'augmentation de taille observée (+5,09 Ko) provient uniquement des objets générés lors des 3 nouveaux commits (les contenus de fichiers, arborescences tree et métadonnées de commits enregistrés), et non de la création de la branche elle-même.