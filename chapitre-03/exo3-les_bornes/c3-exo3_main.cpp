#include <NKentseu/NKentseu.h>

int main() {
    nkentseu::NkWindowConfig cfg;
    cfg.title = "Chapitre 3 - Exercice 3 : Les Bornes";
    cfg.width = 800;
    cfg.height = 600;

    // Définition de la taille minimale (ex: 400x300)
    cfg.minWidth = 140;
    cfg.minHeight = 120;

    nkentseu::NkWindow window;
    if (!window.Create(cfg)) {
        return -1;
    }

    while (window.IsRunning()) {
        window.PollEvents();
        // Logique et rendu ici
    }

    return 0;
}