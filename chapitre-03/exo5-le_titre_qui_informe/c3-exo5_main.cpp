#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"
#include <iostream>
#include <string>

// Structure simulant l'état du document et de l'application
struct DocumentState {
    std::string name = "MonDocument.txt";
    bool isModified = false;
    nkentseu::uint32 width = 1280;
    nkentseu::uint32 height = 720;
};

// Fonction pour mettre à jour le titre uniquement lorsque nécessaire
void UpdateWindowTitle(nkentseu::NkWindow &window, const DocumentState &doc) {
    std::string title = doc.name;
    
    if (doc.isModified) {
        title += " *";
    }

    title += " - " + std::to_string(doc.width) + "x" + std::to_string(doc.height);

    // .c_str() permet de passer un std::string à SetTitle
    window.SetTitle(title.c_str());
    std::cout << "[INFO] Titre mis a jour : " << title << std::endl;
}

int nkmain(const nkentseu::NkEntryState &state) {
    DocumentState doc;

    std::string initialTitle = doc.name + " - " + std::to_string(doc.width) + "x" + std::to_string(doc.height);

    nkentseu::NkWindowConfig cfg;
    cfg.title = initialTitle.c_str();
    cfg.width = doc.width;
    cfg.height = doc.height;

    nkentseu::NkWindow window(cfg);
    if (!window.IsOpen()) {
        logger.Error("[app] creation fenetre echouee");
        return -1;
    }

    // Mise à jour initiale
    UpdateWindowTitle(window, doc);

    while (window.IsOpen()) {
        // Traitement événementiel :
        // La mise à jour du titre n'est exécutée qu'en cas de modification explicite
        // de l'état (ex: redimensionnement, édition du document), et NON à chaque frame.
    }

    return 0;
}