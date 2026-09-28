# Exercice 7 : Le Glisser qui Sort

## 1. Contexte du test
L'objectif de cet exercice était de tester le comportement d'un clic-glisser (glisser de la souris) initié à l'intérieur de la fenêtre et se poursuivant vers l'extérieur, dans un premier temps sans capture de la souris, puis avec capture.

---

## 2. Compte rendu réel des phases de compilation et d'exécution

| Phase | Commande | Résultat | Détails et logs observés |
| :--- | :--- | :--- | :--- |
| **Compilation** | `Jenga build` | **SUCCÈS** | `✓ Compiled: main.cpp` / `✓ Built: Window.exe` (Durée : 3.75s). |
| **Exécution** | `Jenga run` | **BLOQUÉ / FIGÉ** | Console : `--- Exercice 7 : Le glisser qui sort ---` puis `Fenetre creee avec succes.`. |
| **Comportement visuel** | N/A | **Ne répond pas** | La fenêtre `Exo 7 - Le glisser qui sort` s'ouvre mais passe immédiatement en état **"(Ne répond pas)"**. |
| **Fin d'exécution** | Fermeture forcée | **Terminé avec code** | Fermeture après 59.52s avec le code de sortie `3489660927`. |

---

## 3. Observations du comportement lors du glisser

En raison du gel immédiat de la fenêtre graphique en état "(Ne répond pas)" lors de la boucle `while (window.IsOpen()) {}`, les messages du système d'exploitation n'ont pas été traités. Les observations visuelles du glisser vers l'extérieur ont donné les résultats suivants :

| Mode | Comportement à l'intérieur | Comportement lors du glisser vers l'extérieur |
| :--- | :--- | :--- |
| **Sans capture** | Fenêtre bloquée, le clic n'est pas traité par la fenêtre. | Impossible d'interagir ; le curseur reste le symbole de chargement de l'OS[cite: 3]. |
| **Avec capture** | Non testable en l'absence de boucle d'événements active. | Aucune capture active n'a pu être déclenchée. |

---

## 4. Analyse backend et conclusion

1. **Causes du blocage :** La boucle principale `while (window.IsOpen()) {}` tourne sans pomper la file de messages du système Windows. Le système d'exploitation marque donc l'application comme inresponsive.
2. **Gestion de la capture :** Pour qu'un glisser vers l'extérieur conserve la capture de la souris (afin de continuer à recevoir les événements `WM_MOUSEMOVE` et `WM_LBUTTONUP` hors fenêtre), l'application doit impérativement traiter la boucle d'événements globale du moteur à chaque frame.