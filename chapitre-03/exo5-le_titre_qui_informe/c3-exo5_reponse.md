# Exercice 5 : Le titre qui informe

## 1. Structure du titre de la fenêtre

Le titre de la fenêtre est généré dynamiquement selon la convention demandée :
`[Nom du document] [* si modifié] - [Largeur]x[Hauteur]`

Exemples de configurations prises en charge :
- Document non modifié : `MonDocument.txt - 1280x720`
- Document modifié : `MonDocument.txt * - 1280x720`

Lors de l'exécution, le titre initial appliqué et vérifié dans la barre de titre est :
`MonDocument.txt - 1280x720`

---

## 2. Optimisation des mises à jour (Hors boucle de rendu)

Afin de respecter la contrainte de performance imposant de ne pas mettre à jour le titre à chaque frame dans la boucle `while (window.IsOpen())` :
- La fonction `UpdateWindowTitle()` est appelée **uniquement** sur événement (à l'initialisation, lors de la modification de l'état du document ou lors d'un redimensionnement).
- La sortie console confirme que le titre n'est construit et envoyé au système d'exploitation qu'une seule fois au démarrage :
  ```text
  [INFO] Titre mis a jour : MonDocument.txt - 1280x720

Cela évite toute allocation de mémoire inutile (std::string / NkString) et réduit les appels système répétés au niveau du Window Manager.