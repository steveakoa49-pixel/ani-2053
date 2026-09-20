# Exercice 10 : Merge vs Rebase — Comparaison et expérimentation

## 1. Intégration par Fusion (Merge)

### Graphe issu de `git log --graph --oneline`
```text
*   8abb900 (HEAD -> main) Merge branch 'feature-fusion'
|\  
| * cb44c2d (feature-fusion) feat: ajout de la fonctionnalite
* | 56f3658 docs: mise a jour doc
|/  
* a6acd10 initial commit

### Explication de l'intégration par Merge
La fusion conserve la bifurcation d'origine (⁠|\⁠ et ⁠|/⁠) et crée un commit de fusion dédié (⁠8abb900⁠) ayant deux parents (⁠56f3658⁠ et ⁠cb44c2d⁠). L'historique conserve fidèlement l'aspect non-linéaire du développement en parallèle.

## 2. Intégration par Rejeu (Rebase)

### Graphe issu de ⁠git log --graph --oneline
* 188c9b5 (HEAD -> main, feature-fusion) feat: ajout de la fonctionnalite
* 56f3658 docs: mise a jour doc
* a6acd10 initial commit

### Explication de l'intégration par Rebase
Le rejeu réécrit l'historique en déplaçant la base de la branche au sommet de la branche cible. La bifurcation disparaît complètement pour laisser place à une ligne droite chronologique, sans commit de fusion supplémentaire (le hash du commit de la fonctionnalité passe ainsi de ⁠cb44c2d⁠ à ⁠188c9b5⁠).

## 3. Tableau comparatif
| Critère | Fusion (`git merge`) | Rejeu (`git rebase`) |
| :--- | :--- | :--- |
| **Structure de l'historique** | Non-linéaire (conserve les bifurcations) | Parfaitement linéaire (historique plat) |
| **Commit de fusion** | Oui (crée un commit explicite : `8abb900`) | Non (avance en Fast-forward) |
| **Fidélité historique** | Totale (reflète exactement les dates/actions) | Modifiée (réécrit le hash de `cb44c2d` en `188c9b5`) |
| **Risque** | Faible (aucune réécriture de l'historique) | Élevé si appliqué sur une branche publique |

## 4. Préférence argumentée et nuances

 ### Préférence recommandée : Privilégier le Rebase sur les branches de fonctionnalités locales/personnelles avant de faire une Pull Request pour maintenir un historique propre.
 ###Nuance fondamentale : Utiliser exclusivement le Merge sur la branche principale (⁠main⁠) et les branches partagées afin d'éviter la réécriture d'un historique partagé par plusieurs développeurs.