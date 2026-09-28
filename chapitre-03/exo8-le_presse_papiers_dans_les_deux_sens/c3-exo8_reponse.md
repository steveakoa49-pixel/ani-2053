# Exercice 8 : Le Presse-Papiers dans les Deux Sens

## 1. Contexte du test
L'objectif de cet exercice était de lire le texte et l'image du presse-papiers via l'API de `NKWindow`, d'effectuer des transformations (passer le texte en majuscules et inverser les couleurs RGB de l'image sans toucher au canal alpha), puis de réinjecter les données modifiées dans le presse-papiers.

---

## 2. Compte rendu de compilation et d'exécution

| Phase | Commande | Résultat | Constat réel |
| :--- | :--- | :--- | :--- |
| **Compilation** | `Jenga build` | **SUCCÈS** | Le code s'est compilé sans erreur avec Clang-MinGW. |
| **Exécution** | `Jenga run` | **COMPLÉTÉE** | Les messages de console s'affichent, mais **aucune fenêtre graphique ne s'est affichée à l'écran**. |
| **Affichage console** | N/A | `--- Exercice 8 : Le presse-papiers dans les deux sens ---` | Le programme s'exécute séquentiellement et se termine immédiatement. |

---

## 3. Données du presse-papiers et observations

| Élément | Avant lancement (Injecté) | Après exécution (Obtenu) | État du test |
| :--- | :--- | :--- | :--- |
| **Texte** | Texte de test en minuscules | Non modifié / Non lu | Méthodes de presse-papiers texte non liées |
| **Image (Dimensions)** | Image de test | Non lue | Méthodes de presse-papiers image non liées |
| **Image (Bits/pixel)** | N/A | N/A | Non mesurable |

---

## 4. Bilan technique et limites observées

1. **Absence d'affichage de fenêtre :** Le programme ayant exécuté le bloc d'instructions de manière linéaire jusqu'au `return 0`, le processus s'est terminé immédiatement sans laisser le temps au système d'exploitation de rendre la fenêtre visible.
2. **Accès au presse-papiers via NKWindow :** Les méthodes d'accès au presse-papiers texte et image doivent être déclarées et exposées directement dans l'en-tête public de `NkWindow` pour permettre la lecture et la réinjection des données sans recourir aux API Win32 natives.