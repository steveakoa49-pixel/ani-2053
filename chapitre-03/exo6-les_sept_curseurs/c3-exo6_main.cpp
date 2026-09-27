#include <iostream>
#include <cstdint>

#include "NKWindow/Core/NkWindow.h"

namespace nkentseu {

using int32 = std::int32_t;
using uint32 = std::uint32_t;

enum class NkCursorType : uint32 {
    Arrow, IBeam, Hand, Crosshair, SizeWE, SizeNS, NotAllowed
};

NkCursorType GetCursorForPosition(int32 x, uint32 windowWidth) {
    if (windowWidth == 0 || x < 0) return NkCursorType::Arrow;
    uint32 section = (static_cast<uint32>(x) * 7) / windowWidth;
    switch (section) {
        case 0:  return NkCursorType::Arrow;
        case 1:  return NkCursorType::IBeam;
        case 2:  return NkCursorType::Hand;
        case 3:  return NkCursorType::Crosshair;
        case 4:  return NkCursorType::SizeWE;
        case 5:  return NkCursorType::SizeNS;
        case 6:  return NkCursorType::NotAllowed;
        default: return NkCursorType::Arrow;
    }
}

} // namespace nkentseu

int main() {
    std::cout << "Initialisation de la fenetre..." << std::endl;

    nkentseu::NkWindow window;

    nkentseu::NkWindowConfig config;
    config.title = "Ma Premiere Fenetre";
    config.width = 800;
    config.height = 600;

    if (!window.Create(config)) {
        std::cerr << "Erreur lors de la creation de la fenetre !" << std::endl;
        return -1;
    }

    // Boucle principale
    while (window.IsOpen()) {
        // Maintient la fenêtre active en traitant la boucle système interne
    }

    return 0;
}