#include <iostream>
#include <string>
#include <vector>
#include <cstdint>

struct AudioTrack {
    std::string name;
    long long frequency = 0;
    long long channels = 0;
    long long bits = 0;
    long long duration = 0;
    long long fileSize = 0;
    
    long long rawSize = 0;
    long long percentage = 0;
    bool isRefused = false;
    bool isMemory = false;

    // Vérifie si la profondeur en bits est acceptée (8, 16, 24 ou 32)
    bool IsValidBits() const {
        return bits == 8 || bits == 16 || bits == 24 || bits == 32;
    }

    // Calcule la taille brute, le pourcentage et détermine le mode de chargement
    void Process(long long threshold) {
        if (!IsValidBits()) {
            isRefused = true;
            return;
        }

        // Règle 2 : frequency * canaux * (bits / 8) * duree / 1000
        // Multiplication d'abord, division par 1000 à la fin (arrondi vers le bas par défaut en entiers)
        rawSize = (frequency * channels * (bits / 8) * duration) / 1000;

        // Règle 3 : pourcent = fichier * 100 / brut
        if (rawSize > 0) {
            percentage = (fileSize * 100) / rawSize;
        } else {
            percentage = 0;
        }

        // Règle 4 : Strictement supérieur au seuil -> FLUX, sinon MEMOIRE
        if (rawSize > threshold) {
            isMemory = false; // FLUX
        } else {
            isMemory = true;  // MEMOIRE
        }
    }
};

int main() {
    // Optimisation des flux d'entrées/sorties
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    long long threshold = 0;
    if (!(std::cin >> threshold)) {
        return 0;
    }

    int n = 0;
    if (!(std::cin >> n)) {
        return 0;
    }

    std::vector<AudioTrack> tracks(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> tracks[i].name 
                 >> tracks[i].frequency 
                 >> tracks[i].channels 
                 >> tracks[i].bits 
                 >> tracks[i].duration 
                 >> tracks[i].fileSize;
    }

    long long totalMemoryBytes = 0;
    long long fluxCount = 0;
    long long refuseCount = 0;

    // Traitement de chaque piste
    for (int i = 0; i < n; ++i) {
        tracks[i].Process(threshold);

        if (tracks[i].isRefused) {
            refuseCount++;
        } else {
            if (tracks[i].isMemory) {
                totalMemoryBytes += tracks[i].rawSize;
            } else {
                fluxCount++;
            }
        }
    }

    // Affichage des résultats ligne par ligne
    for (int i = 0; i < n; ++i) {
        if (tracks[i].isRefused) {
            std::cout << tracks[i].name << " REFUSE\n";
        } else {
            std::string modeStr = tracks[i].isMemory ? "MEMOIRE" : "FLUX";
            std::cout << tracks[i].name << " " 
                      << tracks[i].rawSize << " " 
                      << tracks[i].percentage << " " 
                      << modeStr << "\n";
        }
    }

    // Affichage du bilan final strict
    std::cout << "MEMOIRE " << totalMemoryBytes << "\n";
    std::cout << "FLUX " << fluxCount << "\n";
    std::cout << "REFUSES " << refuseCount << std::endl;

    return 0;
}