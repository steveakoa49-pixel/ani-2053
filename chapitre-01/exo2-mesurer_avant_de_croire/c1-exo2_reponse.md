# Exercice 2 : Mesurer avant de croire — Comptage et comparaison du dépôt

## 1. Métriques mesurées sur le dépôt local

Les mesures ont été effectuées à l'aide de commandes PowerShell exécutées à la racine du projet `ani-2053` :

* **Nombre total de fichiers (hors `.git`) :** 16 056 fichiers
* **Nombre total de lignes de code et de texte :** 700 695 lignes
* **Commande PowerShell utilisée pour les fichiers :**
  ```powershell
  (Get-ChildItem -Recurse -File -Exclude ".git*").Count 

Commande PowerShell utilisée pour les lignes :
(Get-ChildItem -Recurse -File -Include *.md,*.txt,*.js,*.py,*.c -Exclude ".git*" | Get-Content | Measure-Object -Line).Lines

## 2. Comparaison avec les chiffres du cours et analyse des écarts

| Élément comparé | Chiffres annoncés du cours (Nkentseu) | Valeur mesurée sur le dépôt | Écart constaté |
| :--- | :--- | :--- | :--- |
| **Nombre de fichiers** | 2 641 fichiers source | 16 056 fichiers | +13 415 fichiers |
| **Nombre de lignes** | 1 193 385 lignes | 700 695 lignes | -492 690 lignes |


## 3. Explication des différences constatées

L'écart entre les métriques annoncées dans le cours pour l'écosystème Nkentseu et les mesures réelles sur le dépôt local s'explique par plusieurs facteurs :

1. **Périmètre du comptage des fichiers :**
   * Le cours indique **2 641 fichiers source** (code C++ strictement), tandis que la commande PowerShell récursive compte l'ensemble des fichiers du dépôt (fichiers de configuration, ressources, documentation, images, dépendances et projets annexes comme `Jenga`), ce qui explique les 16 056 fichiers détectés.

2. **Périmètre du comptage des lignes :**
   * Le cours annonce **1 193 385 lignes** sur la totalité de l'écosystème C++, alors que le comptage local cible uniquement certaines extensions (`.md`, `.txt`, `.js`, `.py`, `.c`), excluant ainsi une partie des en-têtes et fichiers source C++ (`.cpp`, `.hpp`, `.h`).

3. **Inclusion des artefacts et sous-dossiers :**
   * Un comptage brut local sans exclusion des répertoires de build ou des projets clonés inclut des éléments non comptabilisés dans le calcul initial du projet Nkentseu.

## 4. Conclusion

La différence de chiffres illustre l'importance de définir précisément le périmètre d'analyse : compter uniquement les fichiers source (`.cpp`, `.hpp`) ou l'intégralité du répertoire modifie radicalement les résultats.
