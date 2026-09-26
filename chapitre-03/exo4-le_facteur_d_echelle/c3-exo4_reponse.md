# Exercice 4 : Le facteur d'échelle

##1. Observations et mesures
Lors de l'exécution du programme `c3-exo4_main.cpp` configuré pour une taille initiale de $1280 \times 720$, la console renvoie la mesure suivante :

```text
Taille de la fenetre : 1278x712

La taille finale de la zone cliente de la fenêtre retournée par window.GetSize() est de 1278 par 712 pixels, légèrement différente de la configuration initiale de $1280 \times 720$ en raison de la gestion des bordures sous l'OS (Windows x86_64).



## 2. Analyse de l'échelle et de la cible de rendu
En inspectant l'interface de `nkentseu::NkWindow` et lors des tests de compilation :
- **Taille de la fenêtre (`GetSize()`)** : $1278 \times 712$ pixels.
- **Taille de la cible de rendu (`GetRenderTargetSize()`)** : Non disponible dans la classe `nkentseu::NkWindow` (provoque une erreur de compilation `no member named 'GetRenderTargetSize'`).
- **Facteur d'échelle (`GetScaleFactor()`)** : Non disponible dans la classe `nkentseu::NkWindow` (provoque une erreur de compilation `no member named 'GetScaleFactor'`).