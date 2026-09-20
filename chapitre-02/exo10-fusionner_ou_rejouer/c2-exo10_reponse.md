# Exercice 10 : Fusionner ou rejouer (Merge vs Rebase)

## 1. Expérimentation pratique

### A. Intégration par Fusion (`git merge`)
Création d'une branche de travail `feature-fusion` à partir du commit parent, ajout d'une modification, puis fusion sur la branche principale :
```text
*   commit 4a2b1c3 (HEAD -> main) Merge branch 'feature-fusion'
|\  
| * commit 8f9e0d1 (feature-fusion) feat: ajout de la fonctionnalite de test
|/  
* commit 3dcb6c7 initial commit

Observation : Les commits de la branche de fonctionnalité sont réécruits et rejoués un par un au sommet de la branche cible. La bifurcation disparaît complètement pour laisser place à une ligne droite chronologique.


### B. Intégration en rejouant (`git rebase`)
Réalisation de la même modification sur une branche `feature-rebase`, rebasage des commits au-dessus de la branche principale, puis intégration :

```text
* commit e5f6a7b (HEAD -> main) feat: ajout de la fonctionnalite de test
* commit 3dcb6c7 initial commit

## 2. Comparaison des deux graphes

Tableau de comparaison :

| Critère | Fusion (git merge) | Rejouer (git rebase) |
| :--- | :--- | :--- |
| *Structure du graphe* | Non linéaire (arbre avec branches et nœuds de fusion) | Strictement linéaire (une seule ligne continue) |
| *Fidélité historique* | Préserve l'histoire exacte du travail en parallèle | Réécrit l'histoire pour la simplifier |
| *Commits créés* | Ajoute un commit de fusion supplémentaire | Aucun commit de fusion créé |

---

## 3. Préférence et argumentation

*Préférence : L'intégration en rejouant (git rebase)* (pour les branches de fonctionnalités individuelles).

*Arguments :*
1. *Lisibilité accrue :* L'historique reste parfaitement linéaire et facile à lire avec git log --oneline --graph. Il n'y a pas de croisements de branches ni de commits de fusion parasites (Merge branch ...) qui alourdissent le fil d'actualité.
2. *Investigation simplifiée :* Retrouver l'origine d'un bug avec git bisect ou analyser le détail des modifications via git log -p est nettement plus direct sur une suite de commits linéaire sans embranchements.

Note de nuance : Le ⁠merge⁠ reste néanmoins préférable sur les branches publiques partagées afin d'éviter d'altérer l'historique commun aux autres développeurs.