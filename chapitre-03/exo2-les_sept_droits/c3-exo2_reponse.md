# Réponse à l'exercice 2 : Les sept droits

## 1. Tableau d'observation des 7 droits

J'ai testé chaque droit individuellement en le passant à `false` dans le fichier `c3-exo2_main.cpp` (pendant que les 6 autres restaient à `true`), puis j'ai compilé et exécuté l'application à chaque étape pour observer le comportement réel de la fenêtre sous Windows.

| Droit désactivé | Effet attendu | Effet réellement observé lors du test |
| :--- | :--- | :--- |
| `frame` | Suppression de la barre de titre et des bordures système | La fenêtre s'est affichée complètement nue, sans barre de titre ni bordures. |
| `resizable` | Maintien d'une taille fixe (1280x720) et bordures non étirables | La fenêtre est restée bloquée à 1280x720. Le curseur de redimensionnement n'apparaissait plus sur les bords. |
| `minimizable` | Désactivation ou masquage du bouton de réduction | Aucun changement. J'ai pu réduire la fenêtre dans la barre des tâches normalement en cliquant sur le bouton. |
| `movable` | Impossibilité de déplacer la fenêtre à la souris | Aucun changement. J'ai attrapé la barre de titre et la fenêtre s'est déplacée normalement sur mon écran. |
| `closable` | Désactivation ou masquage de la croix de fermeture | Aucun changement. La croix est restée rouge/active et cliquer dessus a fermé l'application immédiatement. |
| `maximizable` | Désactivation ou masquage du bouton d'agrandissement | Aucun changement. Le bouton d'agrandissement fonctionnait toujours et le double-clic maximisait la fenêtre. |
| `canFullscreen` | Rejet des requêtes de passage en plein écran | Aucun changement. La fenêtre a continué d'accepter les basculements en plein écran. |

---

## 2. Analyse du code backend (Moteur)

### Explication des écarts constatés
En inspectant le code source de la couche système du moteur sous Windows, j'ai constaté que **seuls les réglages de structure de bordure (`frame`) et de redimensionnement (`resizable`) sont réellement lus et transmis à l'API système Windows**.

Les 5 autres champs de la structure `NkWindowConfig` (`movable`, `closable`, `maximizable`, `canFullscreen`, `minimizable`) sont ignorés par le backend :
- **Absence de vérification** : Le code du moteur ne contient aucune condition (`if`) vérifiant la valeur de ces booléens lors de la création ou de la gestion de la fenêtre.
- **Transparence pour l'API Windows** : Comme le moteur ne transmet pas ces contraintes au gestionnaire de fenêtres Windows (DWM), ce dernier applique le comportement par défaut d'une fenêtre standard. C'est pourquoi les boutons restent actifs et la fenêtre demeure déplaçable.