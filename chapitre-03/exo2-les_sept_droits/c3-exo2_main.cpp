#include <NKentseu/NKentseu.h>

int main() {
    nkentseu::NkWindowConfig cfg;
    cfg.title = "Chapitre 3 - Exercice 2 : Les sept droits";
    cfg.width = 1280;
    cfg.height = 720;

    cfg.frame = true;
    cfg.resizable = true;
    cfg.minimizable = true;
    cfg.movable = false; // Test de désactivation du droit movable
    cfg.closable = true;
    cfg.maximizable = true;
    cfg.canFullscreen = true;

    nkentseu::NkWindow window;
    if (!window.Create(cfg)) {
        return -1;
    }

    while (window.IsRunning()) {
        window.PollEvents();
    }

    return 0;
}