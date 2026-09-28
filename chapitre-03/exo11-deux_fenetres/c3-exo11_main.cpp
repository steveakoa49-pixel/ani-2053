#include <iostream>
#include "NKWindow/Core/NkWindow.h"

int main() {
    std::cout << "--- Exercice 11 : Deux fenetres ---" << std::endl;

    // Configuration et création de la Première Fenêtre
    nkentseu::NkWindow window1;
    nkentseu::NkWindowConfig config1;
    config1.title = "Fenetre 1 - Principale";
    config1.width = 600;
    config1.height = 400;

    if (!window1.Create(config1)) {
        std::cerr << "Erreur lors de la creation de la Fenetre 1 !" << std::endl;
        return -1;
    }

    // Configuration et création de la Seconde Fenêtre
    nkentseu::NkWindow window2;
    nkentseu::NkWindowConfig config2;
    config2.title = "Fenetre 2 - Secondaire";
    config2.width = 600;
    config2.height = 400;

    if (!window2.Create(config2)) {
        std::cerr << "Erreur lors de la creation de la Fenetre 2 !" << std::endl;
        return -1;
    }

    std::cout << "Les deux fenetres ont ete creees avec succes." << std::endl;
    std::cout << "Ecoute des clics sur chaque fenetre..." << std::endl;

    // Boucle d'attente / maintien
    while (window1.IsOpen() || window2.IsOpen()) {
        // Traitement / Dépilage des événements pour détecter la fenêtre cliquée
        // Exemple de logique de détection :
        // if (clic detecte sur window1) std::cout << "Clic recu sur : Fenetre 1" << std::endl;
        // if (clic detecte sur window2) std::cout << "Clic recu sur : Fenetre 2" << std::endl;
    }

    std::cout << "Fermeture des fenetres et fin du programme." << std::endl;

    return 0;
}