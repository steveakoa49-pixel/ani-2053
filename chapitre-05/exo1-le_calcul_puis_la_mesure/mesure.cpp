#include "NKWindow/NKMain.h"
#include "NKWindow/NKWindow.h"
#include "NKCanvas/App/NkCanvasApp.h"

class App : public nkentseu::renderer::NkCanvasApp {
    private:
    nkentseu::NkImage icone;
    nkentseu::NkImage aplat;
    nkentseu::NkImage phototel;
    nkentseu::NkImage JpegPc;
    nkentseu::NkImage capture;

    public:
    App() {
        Config().title      =   "exercice 1";
        Config().width      =   1280;
        Config().height     =   720;
        Config().clearColor =   {65, 171, 204};
    }

    bool OnKeyPress(const nkentseu::NkKeyPressEvent &event) override {
        if (event.GetKey() == nkentseu::NkKey::NK_C) {
            if (!capture.Load("exo1-le_calcul_puis_la_mesure/capture.jpg", 4))
                logger.Error("[APP] : erreur de chargement de capture.jpg");
            else
                logger.Info("[APP] : capture.jpg  - Largeur {0} - Hauteur {1} - BytesPP() : {2} Poids : {3}", capture.Width(), capture.Height(), capture.BytesPP(), capture.Width() * capture.Height() * capture.BytesPP());
        }
        if (event.GetKey() == nkentseu::NkKey::NK_A) {
            if (!aplat.Load("exo1-le_calcul_puis_la_mesure/aplat.png"))
                logger.Error("[APP] : erreur de chargement de aplat.png");
            else
                logger.Info("[APP] : aplat.png - Largeur {0} - Hauteur {1} - BytesPP() : {2} Poids : {3}", aplat.Width(), aplat.Height(), aplat.BytesPP(), aplat.Width() * aplat.Height() * aplat.BytesPP());
        }
        if (event.GetKey() == nkentseu::NkKey::NK_I) {
            if (!icone.Load("exo1-le_calcul_puis_la_mesure/icone.png"))
                logger.Error("[APP] : erreur de chargement de icone.png");
            else
                logger.Info("[APP] : icone.png - Largeur {0} - Hauteur {1} - BytesPP() : {2} Poids : {3}", icone.Width(), icone.Height(), icone.BytesPP(), icone.Width() * icone.Height() * icone.BytesPP());
        }
        if (event.GetKey() == nkentseu::NkKey::NK_J) {
            if (!JpegPc.Load("exo1-le_calcul_puis_la_mesure/photo_pc.jpg"))
                logger.Error("[APP] : erreur de chargement de photo_pc.jpg");
            else
                logger.Info("[APP] : photo_pc.jpg - Largeur {0} - Hauteur {1} - BytesPP() : {2} Poids : {3}", JpegPc.Width(), JpegPc.Height(), JpegPc.BytesPP(), JpegPc.Width() * JpegPc.Height() * JpegPc.BytesPP());
        }
        if (event.GetKey() == nkentseu::NkKey::NK_P) {
            if (!phototel.Load("exo1-le_calcul_puis_la_mesure/photo_tel.jpg"))
                logger.Error("[APP] : erreur de chargement de photo_tel.jpg");
            else
                logger.Info("[APP] : photo_tel.jpg - Largeur {0} - Hauteur {1} - BytesPP() : {2} Poids : {3}", phototel.Width(), phototel.Height(), phototel.BytesPP(), phototel.Width() * phototel.Height() * phototel.BytesPP());
        }
        return true;
    }
};

int nkmain(const nkentseu::NkEntryState& state) {
    return nkentseu::renderer::NkCanvasApp::Run<App>(state);
}