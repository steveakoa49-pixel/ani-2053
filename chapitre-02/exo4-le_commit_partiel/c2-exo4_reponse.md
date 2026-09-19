# Exercice 4 : Le commit partiel

## Journal des 2 derniers commits

```text
e81e2ba (HEAD -> main) Ajout des notes de mise à jour pour la version 2.
5fdadb1 Correction de la documentation du projet
```

## Explication de la méthode
- Utilisation de `git add -p` pour découper les modifications d'un même fichier en plusieurs blocs (hunks).
- Sélection du premier bloc avec `y` pour créer un commit dédié uniquement au premier sujet.
- Sélection du second bloc lors d'un second passage pour créer un commit séparé sur le deuxième sujet.