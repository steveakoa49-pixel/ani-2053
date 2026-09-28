# Exercice 11 : Deux Fenêtres

## 1. Contexte du test
L'objectif de cet exercice est de créer simultanément deux fenêtres distantes ("Fenetre 1 - Principale" et "Fenetre 2 - Secondaire"), de déterminer l'origine de chaque événement de clic, puis d'identifier les éléments manquants pour pouvoir effectuer du rendu graphique dans les deux instances.

---

## 2. Compte rendu de compilation et d'exécution

| Phase | Commande | Résultat | Constats et détails |
| :--- | :--- | :--- | :--- |
| **Compilation** | `Jenga build` | **SUCCÈS** | Compilation réussie en 4.29s via la chaîne d'outils Clang-MinGW sans erreur. |
| **Exécution** | `Jenga run` | **SUCCÈS (FIGÉ)** | Les 2 fenêtres sont créées à l'écran, mais elles se figent en "(Ne répond pas)" en l'absence de dépilage d'événements. |

---

## 3. Observation des fenêtres et événements

| Fenêtre | État visuel | Événements / Clics |
| :--- | :--- | :--- |
| **Fenetre 1 - Principale** | Instanciée et affichée à l'écran | En attente de gestionnaire d'événements dédié |
| **Fenetre 2 - Secondaire** | Instanciée et affichée à l'écran | En attente de gestionnaire d'événements dédié |

---

## 4. Analyse technique : Ce qu'il manquerait pour dessiner dans les deux fenêtres

Pour pouvoir effectuer un rendu graphique (dessiner des formes, du texte ou des images) dans chacune des deux fenêtres, il nous manque actuellement :

1. **Un contexte d'affichage / graphique distinct pour chaque fenêtre :**
   - Chaque fenêtre nécessite son propre contexte graphique (OpenGL, Vulkan, Direct3D ou un Canvas/Renderer 2D).
   - Sans contexte associé à la fenêtre, la carte graphique ne sait pas sur quel tampon de rendu (*framebuffer*) ou quelle surface l'affichage doit être dirigé.

2. **La gestion de la bascule de contexte (Context Switching / Active Window) :**
   - Avant de lancer les commandes de dessin, le moteur doit basculer sur le contexte actif approprié (par exemple `MakeCurrent(window1)` avant de dessiner sur la première, puis `MakeCurrent(window2)` pour la seconde).

3. **Une boucle de rendu avec permutation de tampons (*Swap Buffers*) :**
   - Il faut une boucle principale qui rafraîchit chaque fenêtre à chaque trame (frame) et effectue un `SwapBuffers()` individuel pour mettre à jour ce qui est affiché dans chaque fenêtre.

4. **Un gestionnaire d'événements ciblé par fenêtre :**
   - Il faut associer à chaque événement (clic de souris, touche de clavier) l'identifiant (*Window ID* ou pointeur) de la fenêtre qui l'a émis afin de rediriger les actions graphiques uniquement sur la fenêtre ciblée.