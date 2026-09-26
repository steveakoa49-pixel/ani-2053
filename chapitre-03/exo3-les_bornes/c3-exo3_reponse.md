# Exercice 3 : Les bornes

## 1. Configuration des bornes
- **Taille initiale de la fenêtre :** `800 x 600`
- **Taille minimale définie (`140` x `120`) :** 

---

## 2. Observations lors des tests
- **Tentative de réduction manuelle :** En faisant glisser les bordures de la fenêtre vers l'intérieur, la fenêtre s'arrête de se réduire dès qu'elle atteint la taille limite fixée.
- **Taille minimale acceptée par le système :** `140 x 120`
- **Comportement après suppression du droit/borne :** Lorsque la borne minimale est retirée (`0x0`), le système d'exploitation applique sa propre taille minimale par défaut.

---

## 3. Conclusion
Le système d'exploitation et le gestionnaire de fenêtres respectent la borne minimale tant qu'elle est supérieure aux contraintes matérielles/IHM de la barre de titre du système.