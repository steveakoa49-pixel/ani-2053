#include "NKWindow/NKMain.h"
#include "NKWindow/NKWindow.h"
#include "NKCanvas/App/NkCanvasApp.h"
#include "NKThreading/NkThreadPool.h"
#include "NKThreading/NkFuture.h"
#include "NKTime/NkChrono.h"

#include <cstdint>

// 0 = version Get (bloquante), 1 = version IsReady (non bloquante).
#define VERSION_ISREADY 1

// ---------------------------------------------------------------------------
// Aucun fichier image dans le depot : la tache du pool fabrique elle-meme
// une grande image en memoire (creation + remplissage de pixels). Cela
// simule un chargement lourd et permet de mesurer le gel de la boucle.
// ---------------------------------------------------------------------------
static nkentseu::NkImage BuildHeavyImage() {
    const int width  = 4096;
    const int height = 4096;

    nkentseu::NkImage img;
    img.Create(width, height);

    // Remplissage volontairement couteux (plusieurs dizaines de millions
    // d'ecritures) pour que la construction dure assez longtemps et que le
    // blocage de Get soit clairement visible.
    std::uint8_t* pixels = img.GetPixels();
    const std::size_t count = static_cast<std::size_t>(width) * height * 4u;
    for (std::size_t i = 0; i < count; ++i) {
        pixels[i] = static_cast<std::uint8_t>((i * 31u) & 0xFFu);
    }

    return img;
}

class FutureDemo : public nkentseu::renderer::NkCanvasApp {
private:
    nkentseu::math::NkVec2f squarePos  {300.f, 500.f};
    nkentseu::math::NkVec2f squareSize {100.f, 100.f};
    nkentseu::math::NkColor squareColor {103, 191, 177};

    int    frameCount;
    bool   loadLaunched;
    bool   loadFinished;

    double worstFrameMs;
    int    framesDuringLoad;

    nkentseu::threading::NkThreadPool pool;
    nkentseu::threading::NkPromise<nkentseu::NkImage> promesse;
    nkentseu::threading::NkFuture<nkentseu::NkImage>  futur = promesse.GetFuture();

    nkentseu::NkChrono frameChrono;
    nkentseu::NkChrono loadChrono;

public:
    FutureDemo() {
        Config().clearColor = {44, 80, 191};
        Config().width      = 1280;
        Config().height     = 720;

        frameCount       = 0;
        loadLaunched     = false;
        loadFinished     = false;
        worstFrameMs     = 0.0;
        framesDuringLoad = 0;
    }

    bool OnInit() override {
        // La premiere mesure paie des chargements : on la jette.
        (void)frameChrono.Reset().milliseconds;
        return true;
    }

    void OnUpdate(nkentseu::float32 deltaTime) override {
        (void)deltaTime;

        // Le carre avance d'un pixel par trame : tout gel se verra.
        squarePos.x += 1.f;
        frameCount++;

        // Mesure de la trame courante.
        double frameMs = frameChrono.Reset().milliseconds;
        if (frameMs > worstFrameMs)
            worstFrameMs = frameMs;

        // Tant que le chargement est en cours, on compte les trames dessinees.
        if (loadLaunched && !loadFinished)
            framesDuringLoad++;

        // Au bout de soixante trames, on lance le chargement dans le pool.
        if (frameCount == 60 && !loadLaunched) {
            loadLaunched = true;
            (void)loadChrono.Reset().milliseconds;

            // La tache tourne dans le pool : elle ne dessine pas, elle
            // fabrique l'image et remplit la promesse.
            pool.Enqueue([this]() {
                nkentseu::NkImage img = BuildHeavyImage();
                promesse.SetValue(nkentseu::traits::NkMove(img));
            });

#if VERSION_ISREADY
            logger.Info("[IsReady] chargement lance a la trame 60");
#else
            logger.Info("[Get] chargement lance a la trame 60");
            (void)futur.Get();
            double loadMs = loadChrono.Reset().milliseconds;
            loadFinished = true;
            logger.Info("[Get] pret en {0} ms -- trame la plus longue : {1} ms -- trames pendant chargement : {2}",
                        loadMs, worstFrameMs, framesDuringLoad);
#endif
        }

#if VERSION_ISREADY
        // Version IsReady : a chaque trame, on demande si c'est pret.
        if (loadLaunched && !loadFinished && futur.IsReady()) {
            (void)futur.Get();
            double loadMs = loadChrono.Reset().milliseconds;
            loadFinished = true;
            logger.Info("[IsReady] pret en {0} ms -- trame la plus longue : {1} ms -- trames pendant chargement : {2}",
                        loadMs, worstFrameMs, framesDuringLoad);
        }
#endif
    }

    void OnRender(nkentseu::renderer::NkRenderWindow& target) override {
        nkentseu::renderer::NkRenderer2D rd = target.GetRenderer2D();
        rd.DrawRect({squarePos, squareSize}, squareColor);
    }
};

int nkmain(const nkentseu::NkEntryState& state) {
    return nkentseu::renderer::NkCanvasApp::Run<FutureDemo>(state);
}