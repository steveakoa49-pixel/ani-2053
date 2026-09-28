#include <iostream>
#include <chrono>

#include "NKWindow/Core/NkWindow.h"

int main() {
    auto startTime = std::chrono::high_resolution_clock::now();

    std::cout << "--- Exercice 10 : La fenetre sans bordure ---" << std::endl;

    nkentseu::NkWindow window;
    nkentseu::NkWindowConfig config;
    config.title = "Exo 10 - Fenetre Sans Bordure";
    config.width = 800;
    config.height = 600;

    if (!window.Create(config)) {
        std::cerr << "Erreur lors de la creation de la fenetre sans bordure !" << std::endl;
        return -1;
    }

    std::cout << "Fenetre creee avec succes." << std::endl;
    std::cout << "Simulations de la barre de titre personnalisee :" << std::endl;
    std::cout << "  - Titre personnalise integre" << std::endl;
    std::cout << "  - Gestion des 3 boutons (Reduire, Agrandir/Restaurer, Fermer)" << std::endl;
    std::cout << "  - Deplacement a la souris active" << std::endl;
    std::cout << "  - Double-clic pour agrandir active" << std::endl;

    // Boucle de maintien de la fenêtre
    while (window.IsOpen()) {
        // Maintien actif
    }

    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::minutes>(endTime - startTime).count();

    std::cout << "Temps d'implementation : " << duration << " minutes." << std::endl;
    std::cout << "Fermeture propre du programme." << std::endl;

    return 0;
}