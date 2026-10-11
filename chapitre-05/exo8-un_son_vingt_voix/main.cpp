#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

struct PlaybackEvent {
    long long time = 0;
    long long activeVoices = 0;
    long long delay = 0;
    bool isCut = false;
};

int main() {
    // Optimisation des flux d'entrées/sorties
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    long long duration = 0, loadTime = 0;
    if (!(std::cin >> duration >> loadTime)) {
        return 0;
    }

    int n = 0;
    if (!(std::cin >> n)) {
        return 0;
    }

    std::vector<long long> instants(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> instants[i];
    }

    // Règle : S'il n'y a aucune lecture
    if (n == 0) {
        std::cout << "VOIX_MAX 0\n";
        std::cout << "RETARD_MAX 0\n";
        std::cout << "COUPES 0\n";
        return 0;
    }

    std::vector<PlaybackEvent> events(n);
    long long maxVoices = 0;
    long long maxDelay = 0;
    long long cutCount = 0;
    long long previousLoadEnd = 0;

    for (int i = 0; i < n; ++i) {
        events[i].time = instants[i];

        // 1. Comptage des voix actives (fin exclue : t_j + D > t_i)
        long long voices = 0;
        for (int j = 0; j <= i; ++j) {
            if (instants[j] + duration > instants[i]) {
                voices++;
            }
        }
        events[i].activeVoices = voices;
        maxVoices = std::max(maxVoices, voices);

        // 2 & 3. Gestion séquentielle du chargement du fichier et calcul du retard
        long long loadStart = (i == 0) ? instants[i] : std::max(instants[i], previousLoadEnd);
        long long loadEnd = loadStart + loadTime;
        events[i].delay = loadEnd - instants[i];
        previousLoadEnd = loadEnd;
        maxDelay = std::max(maxDelay, events[i].delay);

        // 4. Détermination de l'état (COUPE si la lecture suivante existe et commence avant la fin de celle-ci)
        if (i + 1 < n && instants[i + 1] < instants[i] + duration) {
            events[i].isCut = true;
            cutCount++;
        } else {
            events[i].isCut = false;
        }
    }

    // Affichage des résultats par ligne
    for (int i = 0; i < n; ++i) {
        std::cout << events[i].time << " "
                  << events[i].activeVoices << " "
                  << events[i].delay << " "
                  << (events[i].isCut ? "COUPE" : "ENTIER") << "\n";
    }

    // Affichage des bilans finaux stricts
    std::cout << "VOIX_MAX " << maxVoices << "\n";
    std::cout << "RETARD_MAX " << maxDelay << "\n";
    std::cout << "COUPES " << cutCount << std::endl;

    return 0;
}