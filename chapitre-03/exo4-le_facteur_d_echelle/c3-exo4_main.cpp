#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"
#include <iostream>

int nkmain(const nkentseu::NkEntryState &state) {
    nkentseu::NkWindowConfig cfg;
    cfg.title = "Chapitre 3 - Exercice 4 : Le facteur d'echelle";
    cfg.width = 1280;
    cfg.height = 720;

    nkentseu::NkWindow window(cfg);
    if (!window.IsOpen()) {
        logger.Error("[app] creation fenetre echouee");
        return -1;
    }

    // Récupération de la taille de la fenêtre (seule méthode existante dans NkWindow)
    auto winSize = window.GetSize();
    std::cout << "Taille de la fenetre : " << winSize.width << "x" << winSize.height << std::endl;

    /*
     * REMARQUE DE TEST :
     * Les méthodes 'GetRenderTargetSize()' et 'GetScaleFactor()' demandées
     * par l'énoncé n'existent pas dans la classe nkentseu::NkWindow.
     * Leur appel provoque les erreurs de compilation suivantes :
     *   - error: no member named 'GetRenderTargetSize' in 'nkentseu::NkWindow'
     *   - error: no member named 'GetScaleFactor' in 'nkentseu::NkWindow'
     *
     * auto renderSize = window.GetRenderTargetSize();
     * float scale = window.GetScaleFactor();
     */

    while (window.IsOpen()) {
        /* Traitement des événements de la fenêtre */
    }

    return 0;
}