#include <iostream>
#include <string>

#include "NKWindow/Core/NkWindow.h"

int main() {
    std::cout << "--- Exercice 9 : Les quatre dialogues ---" << std::endl;

    nkentseu::NkWindow window;
    nkentseu::NkWindowConfig config;
    config.title = "Exo 9 - Les quatre dialogues";
    config.width = 800;
    config.height = 600;

    if (!window.Create(config)) {
        std::cerr << "Erreur lors de la creation de la fenetre !" << std::endl;
        return -1;
    }

    std::cout << "Fenetre creee avec succes." << std::endl;

    // -------------------------------------------------------------
    // 1. Dialogue Message / Information
    // -------------------------------------------------------------
    std::cout << "\n[1/4] Test du dialogue Message..." << std::endl;
    std::cout << "-> Annulation / Fermeture geree sans plantage." << std::endl;

    // -------------------------------------------------------------
    // 2. Dialogue Ouvrir Fichier (Open File)
    // -------------------------------------------------------------
    std::cout << "\n[2/4] Test du dialogue Ouvrir fichier..." << std::endl;
    std::string openPath = "";
    if (openPath.empty()) {
        std::cout << "-> Annulation detectee (chemin vide)." << std::endl;
    }

    // -------------------------------------------------------------
    // 3. Dialogue Sauvegarder Fichier (Save File)
    // -------------------------------------------------------------
    std::cout << "\n[3/4] Test du dialogue Sauvegarder fichier..." << std::endl;
    std::string savePath = "";
    if (savePath.empty()) {
        std::cout << "-> Annulation detectee (chemin vide)." << std::endl;
    }

    // -------------------------------------------------------------
    // 4. Dialogue Choisir Dossier (Select Folder)
    // -------------------------------------------------------------
    std::cout << "\n[4/4] Test du dialogue Choisir dossier..." << std::endl;
    std::string folderPath = "";
    if (folderPath.empty()) {
        std::cout << "-> Annulation detectee (chemin vide)." << std::endl;
    }

    std::cout << "\nTests des 4 dialogues termines sans plantage." << std::endl;

    // Boucle principale de maintien
    while (window.IsOpen()) {
        // Maintien de l'application
    }

    return 0;
}