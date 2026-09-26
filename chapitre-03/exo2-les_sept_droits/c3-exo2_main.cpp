#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"

int nkmain(const NkEntryState &state) {
    NkWindowConfig cfg;
    cfg.title = "Fenetre Test - Droit desactive";
    cfg.width = 1280;
    cfg.height = 720;

    // === DESACTIVATION DES DROITS ===
    // Vous pouvez passer ces booleens a false pour tester :
    cfg.frame         = true; // Fenetre sans bordure / cadre
    cfg.resizable     = true; // Redimensionnement interdit
    cfg.minimizable   = true; // Bouton reduire desactive
    cfg.movable       = true; // Deplacement interdit
    cfg.closable      = true; // Bouton fermer desactive
    cfg.maximizable   = true; // Bouton agrandir desactive
    cfg.canFullscreen = true; // Plein ecran interdit

    // Creation de la fenetre avec la configuration
    NkWindow window(cfg);

    if (!window.IsOpen()) {
        return -1;
    }

    while (window.IsOpen()) {
        /* Gestion des evenements */
    }

    return 0;
}