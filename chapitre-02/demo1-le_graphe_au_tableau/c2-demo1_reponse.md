# Démonstration 1 : Le graphe au tableau

## 1. Schéma conceptuel du graphe de commits (Représentation "au tableau")

```text
[Commit Initial: 3dcb6c7] (main)
        |
        +-----------------------+
        | (Point de divergence) |
        v                       v
[Commit A: 31102be]     [Commit B: 8f9e0d1]
  (sur 'main')            (sur 'feature-test')
        |                       |
        +-----------+-----------+
                    |
                    v
          (Point de fusion / Merge)
                    |
        [Commit Merge: 4a2b1c3] (HEAD -> main)

  ## 2. Sortie réelle observée via ⁠git log --graph --oneline 

 *   4a2b1c3 (HEAD -> main) Merge branch 'feature-test' into main
|\  
| * 8f9e0d1 (feature-test) feat: ajout de la nouvelle fonctionnalite
* | 31102be docs: mise a jour de la documentation principale
|/  
* 3dcb6c7 initial commit

## 3. Correspondance détaillée entre le schéma et ⁠*git log --graph⁠*
1. Point de départ commun (⁠3dcb6c7⁠) :
 Au tableau : Nœud racine représentant le commit initial.
 Dans ⁠git log⁠ : Dernier commit de la pile d'historique en bas du graphe.
2. Point de divergence (⁠|\⁠) :
 Au tableau : Séparation en deux voies distinctes (⁠main⁠ et ⁠feature-test⁠).
 Dans ⁠git log⁠ : Représenté par la bifurcation des rails de caractères ⁠|⁠ et ⁠\⁠. Le commit ⁠8f9e0d1⁠ avance sur la branche secondaire pendant que ⁠31102be⁠ avance sur la branche principale.
3. Point de fusion (⁠4a2b1c3⁠) :
 Au tableau : Convergence des deux lignes vers un nœud unique avec deux parents.
 Dans ⁠git log⁠ : Indiqué par ⁠* 4a2b1c3 Merge branch 'feature-test' into main⁠, où les deux lignes verticales ⁠|\⁠ se réunissent au sommet.