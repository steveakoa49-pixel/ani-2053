#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

#include "NKWindow/Core/NkWindow.h"

int main() {
    std::cout << "--- Exercice 8 : Le presse-papiers dans les deux sens ---" << std::endl;

    nkentseu::NkWindow window;
    nkentseu::NkWindowConfig config;
    config.title = "Exo 8 - Presse-papiers";
    config.width = 400;
    config.height = 300;

    if (!window.Create(config)) {
        std::cerr << "Erreur lors de la creation de la fenetre !" << std::endl;
        return -1;
    }

    // -------------------------------------------------------------
    // 1. TRAITEMENT DU TEXTE DU PRESSE-PAPIERS
    // -------------------------------------------------------------
    std::cout << "\n--- Lecture du texte ---" << std::endl;
    // Remarque : Si window/NKWindow n'a pas de methodes GetClipboardText/SetClipboardText,
    // ces appels serviront a identifier les methodes exactes de l'en-tete.
    
    /* 
    std::string text = window.GetClipboardText();
    std::cout << "Texte lu : " << text << std::endl;

    // Conversion en majuscules
    std::transform(text.begin(), text.end(), text.begin(), [](unsigned char c) {
        return std::toupper(c);
    });

    window.SetClipboardText(text);
    std::cout << "Texte modifie remis dans le presse-papiers : " << text << std::endl;
    */

    // -------------------------------------------------------------
    // 2. TRAITEMENT DE L'IMAGE DU PRESSE-PAPIERS
    // -------------------------------------------------------------
    std::cout << "\n--- Traitement de l'image ---" << std::endl;
    /*
    NkImage image = window.GetClipboardImage();
    if (image.IsValid()) {
        std::cout << "Dimensions image : " << image.GetWidth() << "x" << image.GetHeight() << std::endl;
        std::cout << "Bits par pixel : " << image.GetBitsPerPixel() << std::endl;

        // Inversion des couleurs (RVB uniquement, alpha conserve)
        uint8_t* pixels = image.GetPixels();
        size_t totalBytes = image.GetWidth() * image.GetHeight() * (image.GetBitsPerPixel() / 8);
        
        for (size_t i = 0; i < totalBytes; i += 4) {
            pixels[i]     = 255 - pixels[i];     // Rouge / Bleu
            pixels[i + 1] = 255 - pixels[i + 1]; // Vert
            pixels[i + 2] = 255 - pixels[i + 2]; // Bleu / Rouge
            // pixels[i + 3] conserve sa valeur d'origine (Alpha non inverse)
        }

        window.SetClipboardImage(image);
        std::cout << "Image inversee remise dans le presse-papiers." << std::endl;
    } else {
        std::cout << "Aucune image trouvee dans le presse-papiers." << std::endl;
    }
    */

    std::cout << "\nExecution terminee." << std::endl;
    return 0;
}