## 1. États de départ (avant la fusion)

Sortie de `git log --oneline` dans le Dépôt A (modification locale) :
```text
9bac9fa Modification du bas du fichier par depot A
1f10c1f Initialisation de fichier.txt avec plusieurs lignes

Sortie de ⁠git log --oneline⁠ dans le Clone B (modification poussée sur origin) :

264a8b2 Modification du haut du fichier par clone B
1f10c1f Initialisation de fichier.txt avec plusieurs lignes

## 2. Commande de fusion et réponse complète de la machine

Commande ⁠git pull origin main⁠ exécutée dans le Dépôt A :

From [https://github.com/steveakoa49-pixel/ani-2053](https://github.com/steveakoa49-pixel/ani-2053)
 * branch            main       -> FETCH_HEAD
Merge made by the 'ort' strategy.
 chapitre-02/exo7-le_conflit_qui_n_en_est_pas_un/fichier.txt | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

 ## 3. Contenu du fichier après la fusion (sans intervention humaine)

Sortie de la commande d'affichage du fichier réuni par Git :

Get-Content chapitre-02/exo7-le_conflit_qui_n_en_est_pas_un/fichier.txt
Ligne 1 : modifiee par le clone B
Ligne 2
Ligne 3
Ligne 4
Ligne 5 : modifiee par le depot A

