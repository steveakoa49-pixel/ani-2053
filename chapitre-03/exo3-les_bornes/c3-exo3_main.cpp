#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"

using namespace nkentseu;

int nkmain(const NkEntryState &state) {
    NkWindowConfig cfg;
    cfg.title = "Ma fenetre";
    cfg.width = 800;
    cfg.height = 400;

    // Test des bornes minimales
    cfg.minWidth = 400;
    cfg.minHeight = 300;

    NkWindow window(cfg);
    if (!window.IsOpen()) {
        logger.Error("[app] creation fenetre echouee");
        return -1;
    }
    while (window.IsOpen()) { /* les evenements arrivent ici */ }
    return 0;
}