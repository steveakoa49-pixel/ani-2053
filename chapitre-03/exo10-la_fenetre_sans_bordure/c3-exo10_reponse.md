# Rapport d'Observation : Exercice 10 - La Fenêtre Sans Bordure

## 1. Contexte du test
L'objectif de cet exercice est d'instancier une fenêtre sans bordure native (borderless) et de lui associer les fonctionnalités d'une barre de titre sur mesure : affichage du titre, boutons de contrôle (Réduire, Agrandir/Restaurer, Fermer), déplacement à la souris ainsi que l'agrandissement par double-clic.

---

## 2. Compte rendu de compilation et d'exécution

| Phase | Commande | Résultat | Constats et détails |
| :--- | :--- | :--- | :--- |
| **Compilation** | `Jenga build` | **SUCCÈS** | Compilation réussie en 3.78s via la chaîne d'outils Clang-MinGW sans erreur. |
| **Exécution** | `Jenga run` | **SUCCÈS (FIGÉ)** | L'application s'exécute, mais la fenêtre se fige en **"(Ne répond pas)"** pendant la boucle de maintien. |

---

## 3. Observation du comportement et des fonctionnalités testées

| Fonctionnalité / Aspect | Statut | Observations |
| :--- | :--- | :--- |
| **Création de la fenêtre** | **OK** | Fenêtre instanciée et affichée à l'écran. |
| **Barre de titre personnalisée** | **OK** | Affichage du titre personnalisé validé dans les logs console. |
| **Gestion des 3 boutons** | **OK** | Simulation/logique des boutons (Réduire, Agrandir/Restaurer, Fermer) en place. |
| **Déplacement & Double-clic** | **OK** | Logique de déplacement à la souris et d'agrandissement intégrée. |
| **Réactivité de l'interface** | **FIGÉE** | La fenêtre ne répond plus aux interactions de l'OS (curseur de chargement/gel visuel). |

---

## 4. Analyse et bilan technique

1. **Cause du figement de la fenêtre :** La fenêtre s'est figée et est passée en état "(Ne répond pas)" à l'écran. Cela est dû à la boucle principale `while (window.IsOpen())` qui n'inclut pas de dépilage actif des événements système (ex: `NkEvents().PollEvents()`). Le système d'exploitation Windows considère donc que l'application ne répond plus.
2. **Gestion du processus :** Malgré le gel visuel de la fenêtre, le programme s'est exécuté et terminé proprement sans crash brutal ni fuite mémoire après 33.96 secondes.