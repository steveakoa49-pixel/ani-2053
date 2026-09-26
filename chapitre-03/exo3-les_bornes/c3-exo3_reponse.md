# Exercice 3 : Les bornes

## 1. Protocole de test et observations

J'ai configuré la fenêtre avec une taille initiale de `800 x 600` et j'ai défini des bornes minimales dans la structure de configuration (`minWidth = 400`, `minHeight = 300`). 

J'ai ensuite compilé le programme puis tenté de réduire la fenêtre au maximum à la souris en attrapant ses bordures.

- **Comportement avec bornes (`400 x 300`)** : La fenêtre s'est réduite normalement jusqu'à atteindre la limite de `400 x 300` pixels. Impossible de la réduire davantage à la souris, le curseur bloquait sur cette taille.
- **Comportement sans bornes / aux limites extrêmes (`135 x 110`)** : J'ai ensuite testé en supprimant la limite minimale (`minWidth = 400`, `minHeight = 300`). En essayant de réduire la fenêtre au minimum absolu, Windows a refusé de la réduire en dessous d'environ `135 x 110` pixels.

---

## 2. Taille minimale acceptée par le système

- **Taille minimale réelle observée à l'écran :** Environ **`135 x 110` pixels**.
- **Explication du comportement système :** 
  Même lorsque le code autorise une taille de `400 x 300`, le gestionnaire de fenêtres du système d'exploitation impose une taille minimale matérielle irréductible. Cette limite correspond à la largeur exacte nécessaire pour afficher la barre de titre et ses trois boutons de contrôle système (Réduire, Agrandir, Fermer) ainsi que l'icône d'application.

---

## 3. Analyse du code backend (Moteur)

En vérifiant l'implémentation dans la couche backend du moteur :
- Les champs `minWidth` et `minHeight` sont bien lus par le backend Windows et transmis à l'API système lors de la gestion des messages de redimensionnement (`WM_GETMINMAXINFO`).
- Cependant, le moteur ne peut pas outrepasser la limite minimale native de Windows. Si la valeur transmise par le développeur est inférieure à la taille minimale requise par l'OS pour afficher la barre de titre, c'est la limite de Windows ( `135 x 110` px) qui prend la priorité.