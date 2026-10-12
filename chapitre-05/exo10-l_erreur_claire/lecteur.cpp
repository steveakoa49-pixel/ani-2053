#include "NKLogger/NkLog.h"
#include "NKMedia/Video/NkVideoReader.h"
#include "NKMedia/NkMediaProbe.h"

using namespace nkentseu;
using namespace nkentseu::media;

void TesterFichier(const char* chemin) {
    logger.Info("=== Test du fichier : {0} ===", chemin);

    NkVideoReader reader;
    int frameCount = 0;
    bool opened = false;

    if (reader.Open(chemin)) {
        opened = true;
        // Comptage réel des images lues par ReadFrame pour gérer les fichiers coupés
        while (reader.ReadFrame()) {
            frameCount++;
        }
        logger.Info("Ouvert : oui, Images lues : {0}", frameCount);
    } else {
        logger.Info("Ouvert : non, Images lues : 0");
    }

    NkMediaInfo probeInfo;
    if (NkMediaProbe::ProbeFile(chemin, probeInfo)) {
        logger.Info("Sonde - Conteneur détecté : {0}", probeInfo.ContainerName());
    } else {
        logger.Info("Sonde - Échec de l'analyse");
    }
}

int main() {
    TesterFichier("chapitre-05/exo10-l_erreur_claire/film.mp4");
    TesterFichier("chapitre-05/exo10-l_erreur_claire/film_coupe.mp4");
    TesterFichier("chapitre-05/exo10-l_erreur_claire/faux.mp4");

    return 0;
}