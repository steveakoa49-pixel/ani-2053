# Exercice 9 : Les Quatre Dialogues

## 1. Contexte du test
L'objectif de cet exercice était de tester les quatre dialogues natifs du moteur (Message, Ouvrir un fichier, Sauvegarder un fichier, Choisir un dossier) et de vérifier que l'annulation ou la fermeture intempestive de ces boîtes de dialogue est correctement gérée sans provoquer de plantage du programme.

---

## 2. Compte rendu de compilation et d'exécution

| Phase | Commande | Résultat | Constats et détails |
| :--- | :--- | :--- | :--- |
| **Compilation** | `Jenga build` | **SUCCÈS** | Le code a été compilé avec succès sans aucune erreur sous Clang-MinGW. |
| **Exécution** | `Jenga run` | **COMPLÉTÉE** | La séquence de test s'exécute dans la console, mais la fenêtre se fige en "(Ne répond pas)". |

---

## 3. Observation du traitement de l'annulation des 4 dialogues

| Type de dialogue | Action utilisateur | Comportement du programme | Résultat |
| :--- | :--- | :--- | :--- |
| **1. Message** | Fermeture / Annulation | Annulation gérée correctement, aucun crash | **Conforme** |
| **2. Ouvrir fichier** | Fermeture sans sélection | Détection de chaîne vide, aucun crash | **Conforme** |
| **3. Sauvegarder fichier** | Annulation de la boîte | Détection de chaîne vide, aucun crash | **Conforme** |
| **4. Choisir dossier** | Fermeture sans choix | Détection de chaîne vide, aucun crash | **Conforme** |

---

## 4. Analyse et bilan technique

1. **Gestion des annulations :** L'annulation et la fermeture de chacune des quatre boîtes de dialogue ont été interceptées correctement sans provoquer de fuite mémoire ni de plantage de l'application.
2. **Gel visuel de la fenêtre :** La boucle de maintien brute `while (window.IsOpen())` n'effectue pas le dépilage des événements système (event queue). Windows détecte que la fenêtre ne traite pas ses messages et l'affiche comme "(Ne répond pas)".