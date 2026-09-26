# Exercice 1 : La fenêtre nue

## Nombre total de lignes
Le programme `c3-exo1_main.cpp` comporte au total **19 lignes** de code.

---

## Explication et correspondance des lignes de notre fichier (`c3-exo1_main.cpp`)

- **Lignes 1 à 2** : Inclusions des entêtes nécessaires (`#include "NKWindow/NKWindow.h"` et `#include "NKWindow/NKMain.h"`).
- **Ligne 4** : Point d'entrée principal du programme (`int nkmain(const NkEntryState &state)`).
- **Lignes 5 à 9** : Configuration de la fenêtre (`NkWindowConfig cfg;` ainsi que la définition du titre, de la largeur et de la hauteur).
- **Ligne 11** : Création et ouverture de l'instance de la fenêtre (`NkWindow window(cfg);`).
- **Lignes 12 à 15** : Test de sécurité vérifiant si l'ouverture de la fenêtre a échoué (`if (!window.IsOpen())`).
- **Ligne 16** : Boucle `while (window.IsOpen())` qui maintient la fenêtre ouverte.
- **Ligne 17** : Instruction `return 0;` pour la fin du programme.

---

## Preuve / Observation lors de l'exécution

Lors de l'exécution du programme privé de sa boucle de gestion des événements, la fenêtre s'ouvre correctement mais ne traite aucun message système. Par conséquent, l'interface gèle et le système d'exploitation affiche l'avertissement *"Ne répond pas"*.

![Capture d'écran - Fenêtre figée (Ne répond pas)](./capture_execution.png)

*Note : La capture d'écran ci-dessus montre le comportement observé à l'écran lors du lancement de `c3-exo1_main.cpp`.*