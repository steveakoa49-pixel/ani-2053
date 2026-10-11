#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

struct Glyphe {
    long long avance = 0;
    long long x0 = 0, y0 = 0, x1 = 0, y1 = 0;
    bool existe = false;
};

int main() {
    // Optimisation des flux d'entrées/sorties pour la rapidité
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int G = 0;
    if (!(std::cin >> G)) {
        return 0;
    }

    // Utilisation d'un tableau direct basé sur le code ASCII pour un accès O(1) instantané
    std::vector<Glyphe> tableGlyphes(256);
    for (int i = 0; i < G; ++i) {
        char c;
        long long avance, x0, y0, x1, y1;
        std::cin >> c >> avance >> x0 >> y0 >> x1 >> y1;
        tableGlyphes[static_cast<unsigned char>(c)] = {avance, x0, y0, x1, y1, true};
    }

    int K = 0;
    if (!(std::cin >> K)) {
        return 0;
    }

    // Table de hachage pour stocker les crénages avec une clé combinée (c1, c2) en O(1)
    std::unordered_map<int, long long> tableCrenages;
    for (int i = 0; i < K; ++i) {
        std::string couple;
        long long k;
        std::cin >> couple >> k;
        if (couple.length() >= 2) {
            int cle = (static_cast<unsigned char>(couple[0]) << 8) | static_cast<unsigned char>(couple[1]);
            tableCrenages[cle] = k;
        }
    }

    std::string texte;
    long long ox = 0, oy = 0;
    if (!(std::cin >> texte >> ox >> oy)) {
        return 0;
    }

    long long x = ox;
    long long minx = 2e18, miny = 2e18;
    long long maxx = -2e18, maxy = -2e18;
    bool dessineAuMoinsUn = false;
    int absents = 0;

    for (size_t i = 0; i < texte.length(); ++i) {
        char courant = texte[i];
        unsigned char uc = static_cast<unsigned char>(courant);

        // Si le glyphe est absent de la table
        if (!tableGlyphes[uc].existe) {
            std::cout << courant << " ABSENT\n";
            absents++;
            continue;
        }

        // Affichage de la position du curseur pour ce caractère
        std::cout << courant << " " << x << "\n";

        const Glyphe& g = tableGlyphes[uc];
        // Si le rectangle dessine une surface valide
        if (g.x1 > g.x0 && g.y1 > g.y0) {
            long long rx0 = x + g.x0;
            long long ry0 = oy + g.y0;
            long long rx1 = x + g.x1;
            long long ry1 = oy + g.y1;

            if (!dessineAuMoinsUn) {
                minx = rx0;
                miny = ry0;
                maxx = rx1;
                maxy = ry1;
                dessineAuMoinsUn = true;
            } else {
                minx = std::min(minx, rx0);
                miny = std::min(miny, ry0);
                maxx = std::max(maxx, rx1);
                maxy = std::max(maxy, ry1);
            }
        }

        // Avancement du curseur
        x += g.avance;

        // Recherche du crénage avec le caractère suivant
        if (i + 1 < texte.length()) {
            char suivant = texte[i + 1];
            int cle = (uc << 8) | static_cast<unsigned char>(suivant);
            auto it = tableCrenages.find(cle);
            if (it != tableCrenages.end()) {
                x += it->second;
            }
        }
    }

    // Affichage des bilans finaux
    std::cout << "CURSEUR " << x << "\n";

    if (!dessineAuMoinsUn) {
        std::cout << "BOITE AUCUNE\n";
        std::cout << "MONTE 0\n";
        std::cout << "DESCEND 0\n";
        std::cout << "ECRAN RIEN\n";
    } else {
        std::cout << "BOITE " << minx << " " << miny << " " << maxx << " " << maxy << "\n";

        long long monte = (miny < oy) ? (oy - miny) : 0;
        long long descend = (maxy > oy) ? (maxy - oy) : 0;

        std::cout << "MONTE " << monte << "\n";
        std::cout << "DESCEND " << descend << "\n";

        std::string ecran = "VISIBLE";
        if (maxy <= 0) {
            ecran = "HORS";
        } else if (miny < 0) {
            ecran = "COUPE";
        }
        std::cout << "ECRAN " << ecran << "\n";
    }

    std::cout << "ABSENTS " << absents << std::endl;

    return 0;
}