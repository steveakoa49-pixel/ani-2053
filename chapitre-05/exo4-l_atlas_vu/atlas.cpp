#include "NkWindow/NKWindow.h"
#include "NKWindow/nkmain.h"
#include "NkFont/NkFont.h"
#include "NkCanvas/Renderer/Resources/NkTexture.h"
#include "NkImage/NkImage.h"
#include <iostream>
#include <fstream>

int nkmain(const nkentseu::NkEntryState& state) {
    // --- Taille 18 ---
    {
        nkentseu::NkFontAtlas atlas;
        nkentseu::NkFont* font = atlas.AddFontFromFile("exo4-l_atlas_vu/Where-is-my-Frog.ttf", 18.f);
        if (!atlas.Build() || font == nullptr) {
            logger.Error("Echec de construction de l'atlas pour la taille 18");
            return -1;
        }

        nkentseu::uint8* pixels = nullptr;
        nkentseu::int32 largeur = 0, hauteur = 0;
        atlas.GetTexDataAsRGBA32(&pixels, &largeur, &hauteur);
        
        if (pixels != nullptr) {
            nkentseu::NkImage img = nkentseu::NkImage::Wrap(pixels, largeur, hauteur, nkentseu::NkImagePixelFormat::NK_RGBA32);
            if (!img.SavePNG("exo4-l_atlas_vu/atlas.png")) {
                logger.Error("Impossible de sauvegarder atlas.png");
            }
        }
        logger.Info("Taille 18 -> Glyphes: {0}, Texture: {1}x{2}", font->glyphCount, largeur, hauteur);
    }

    // --- Taille 48 ---
    {
        nkentseu::NkFontAtlas atlas;
        nkentseu::NkFont* font = atlas.AddFontFromFile("exo4-l_atlas_vu/Where-is-my-Frog.ttf", 48.f);
        if (!atlas.Build() || font == nullptr) {
            logger.Error("Echec de construction de l'atlas pour la taille 48");
            return -1;
        }

        nkentseu::uint8* pixels = nullptr;
        nkentseu::int32 largeur = 0, hauteur = 0;
        atlas.GetTexDataAsRGBA32(&pixels, &largeur, &hauteur);
        
        logger.Info("Taille 48 -> Glyphes: {0}, Texture: {1}x{2}", font->glyphCount, largeur, hauteur);
    }

    return 0;
}