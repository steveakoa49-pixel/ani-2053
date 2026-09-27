# Exercice 6 : Les 7 Curseurs 

##1. Description du travail et du code

L'objectif était de découper la fenêtre en sept zones virtuelles pour adapter la forme du curseur selon la position `x` de la souris.
                                                                                                                                 Le code implémenté contient la logique de découpage suivante :
```cpp
NkCursorType GetCursorForPosition(int32 x, uint32 windowWidth) {
    if (windowWidth == 0 || x < 0) return NkCursorType::Arrow;
    uint32 section = (static_cast<uint32>(x) * 7) / windowWidth;
    switch (section) {
        case 0:  return NkCursorType::Arrow;
        case 1:  return NkCursorType::IBeam;
        case 2:  return NkCursorType::Hand;
        case 3:  return NkCursorType::Crosshair;
        case 4:  return NkCursorType::SizeWE;
        case 5:  return NkCursorType::SizeNS;
        case 6:  return NkCursorType::NotAllowed;
        default: return NkCursorType::Arrow;
    }
}                                                                                                                                                          
---

## 2. Compte rendu d'exécution

Phase de compilation (Jenga build)
Résultat : Succès de la compilation.
Constat : La structure du code, les namespaces et la définition de NkCursorType sont valides.

Phase d'exécution (Jenga run)
Résultat dans la console : L'affichage Initialisation de la fenetre... apparaît.
Comportement de la fenêtre : La fenêtre graphique s'ouvre mais passe immédiatement en état "(Ne répond pas)" avec le curseur d'attente du système.

Cause : La boucle principale while (window.IsOpen()) {} ne contient aucun appel pour vider la file de messages du système d'exploitation Windows.
---

---

## 3. Tableau des observations visuelles

En raison du blocage de la fenêtre au lancement, il a été impossible de tester le survol de la souris et les changements de formes de curseur en temps réel : 

| Zone | Forme demandée (`NkCursorType`) | Forme obtenue | Constat réel |
| :--- | :--- | :--- | :--- |
| **Zone 0** (0/7) | `NkCursorType::Arrow` | Curseur de chargement OS / Bloqué | Fenêtre figée "(Ne répond pas)" |
| **Zone 1** (1/7) | `NkCursorType::IBeam` | Curseur de chargement OS / Bloqué | Fenêtre figée "(Ne répond pas)" |
| **Zone 2** (2/7) | `NkCursorType::Hand` | Curseur de chargement OS / Bloqué | Fenêtre figée "(Ne répond pas)" |
| **Zone 3** (3/7) | `NkCursorType::Crosshair` | Curseur de chargement OS / Bloqué | Fenêtre figée "(Ne répond pas)" |
| **Zone 4** (4/7) | `NkCursorType::SizeWE` | Curseur de chargement OS / Bloqué | Fenêtre figée "(Ne répond pas)" |
| **Zone 5** (5/7) | `NkCursorType::SizeNS` | Curseur de chargement OS / Bloqué | Fenêtre figée "(Ne répond pas)" |
| **Zone 6** (6/7) | `NkCursorType::NotAllowed` | Curseur de chargement OS / Bloqué | Fenêtre figée "(Ne répond pas)" |

---

## 4. Bilan technique et backend

*Calcul des zones : La fonction GetCursorForPosition calcule correctement la section ((x * 7) / width), mais n'est pas encore connectée à un gestionnaire d'événements de mouvement de souris (NkMouseMoveEvent).

*Gestion de la boucle Windows : Pour débloquer la fenêtre et permettre le changement dynamique du curseur, le backend nécessite un traitement actif des événements (via le gestionnaire d'événements approprié de NKWindow) à chaque tour de boucle while (window.IsOpen()).