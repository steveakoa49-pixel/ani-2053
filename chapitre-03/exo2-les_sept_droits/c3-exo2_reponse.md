# Exercice 2 : Les sept droits

## Tableau d'observation des 7 droits

| Droit désactivé | Effet attendu | Effet observé |
| :--- | :--- | :--- |
| `frame` | Fenêtre sans bordure ni barre de titre | *[La fenêtre n'a pas de bordure. Seul la fenêtre nue s'affiche. La barre de titre et la bordure rectangulaire du système disparaissent totalement.]* |
| `resizable` | Empêche le redimensionnement manuel | *[La fenêtre conserve strictement les dimensions définies à son initialisation 1280x720.]* |
| `minimizable` | Désactive ou masque le bouton "Réduire" | *[La fenêtre reste visible sur le bureau et ne peut être fermée ou masquée qu'en la fermant explicitement ou en changeant d'application au premier plan.]* |
| `movable` | Empêche de déplacer la fenêtre à la souris | *[Cliquer et maintenir le bouton de la souris sur la barre de titre pour la faire glisser ne produit aucun effet. La fenêtre reste ancrée aux coordonnées où elle a été créée à l'écran.]* |
| `closable` | Désactive ou masque le bouton de fermeture (croix) | *[La Croix de fermeture (X) en haut à droite de la fenêtre devient grisée, inactive ou disparaît.]* |
| `maximizable` | Désactive ou masque le bouton "Agrandir" | *[Dans la barre de titre, le bouton d'agrandissement (le rectangle / carré à côté de la croix X) devient grisé, cliquable sans effet, ou disparaît.]* |
| `canFullscreen` | Empêche le passage en plein écran | *[La fenêtre reste strictement bloquée dans son cadre d'origine et ne peut pas prendre le contrôle exclusif de l'affichage du moniteur.]* |

---

## Analyse du code backend (Moteur)

Pour chaque écart constaté entre l'effet attendu et l'effet observé, voici la justification trouvée dans le code du backend :

### Écart constaté : *[movable]*
- **Raison dans le backend** : Le champ `movable` de `NkWindowConfig` n'est pas lu/vérifié lors de la création de la fenêtre sous le backend.
- **Fichier / Ligne du moteur** : `src/backend/...`
- **Explication** : Le code ne contient aucun test conditionnel vérifiant la valeur du booléen pour ce droit avant de transmettre la configuration à l'API système.