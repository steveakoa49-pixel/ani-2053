#include <iostream>
#include <cstdint>

#include "NKWindow/Core/NkWindow.h"

int main() {
    std::cout << "--- Exercice 7 : Le glisser qui sort ---" << std::endl;

    nkentseu::NkWindow window;
    nkentseu::NkWindowConfig config;
    config.title = "Exo 7 - Le glisser qui sort";
    config.width = 800;
    config.height = 600;

    if (!window.Create(config)) {
        std::cerr << "Erreur lors de la creation de la fenetre !" << std::endl;
        return -1;
    }

    std::cout << "Fenetre creee avec succes." << std::endl;

    // Boucle principale sans include inexistant
    while (window.IsOpen()) {
        // La boucle tourne pour maintenir la fenêtre
    }

    return 0;
}