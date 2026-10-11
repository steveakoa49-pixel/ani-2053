#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

struct Track {
    std::string type; // "vide" ou "soun"
    std::string code;
};

struct MediaFile {
    std::string name;
    std::string hex;
    int trackCount = 0;
    std::vector<Track> tracks;
    std::string container = "INCONNU";

    void DetectContainer() {
        if (hex == "-") {
            container = "INCONNU";
            return;
        }
        size_t nBytes = hex.length() / 2;

        // 1. MP4 : n >= 12, octets 4 à 7 valent "ftyp" (66747970)
        if (nBytes >= 12 && hex.length() >= 16 && hex.substr(8, 8) == "66747970") {
            container = "MP4";
        }
        // 2. WEBM : n >= 4, octets 0 à 3 valent 1A45DFA3
        else if (nBytes >= 4 && hex.length() >= 8 && hex.substr(0, 8) == "1A45DFA3") {
            container = "WEBM";
        }
        // 3. WAV : n >= 12, octets 0-3 = "RIFF" (52494646), octets 8-11 = "WAVE" (57415645)
        else if (nBytes >= 12 && hex.length() >= 24 && hex.substr(0, 8) == "52494646" && hex.substr(16, 8) == "57415645") {
            container = "WAV";
        }
        // 4. OGG : "OggS" (4F676753), n >= 4
        else if (nBytes >= 4 && hex.length() >= 8 && hex.substr(0, 8) == "4F676753") {
            container = "OGG";
        }
        // 5. FLAC : "fLaC" (664C6143), n >= 4
        else if (nBytes >= 4 && hex.length() >= 8 && hex.substr(0, 8) == "664C6143") {
            container = "FLAC";
        }
        // 6. MP3 : "ID3" (494433), n >= 3
        else if (nBytes >= 3 && hex.length() >= 6 && hex.substr(0, 6) == "494433") {
            container = "MP3";
        }
        // 7. MP3 (sync word) : n >= 2, b0 = FF, b1 >= E0
        else if (nBytes >= 2 && hex.length() >= 4 && hex.substr(0, 2) == "FF") {
            int b1 = std::stoi(hex.substr(2, 2), nullptr, 16);
            if (b1 >= 0xE0) {
                container = "MP3";
            } else {
                container = "INCONNU";
            }
        }
        else {
            container = "INCONNU";
        }
    }

    std::string MapCodec(const std::string& c) const {
        if (c == "mp4a") return "aac";
        if (c == "opus") return "opus";
        if (c == "avc1" || c == "avc3") return "h264";
        if (c == "hvc1" || c == "hev1") return "h265";
        if (c == "vp08") return "vp8";
        if (c == "vp09") return "vp9";
        if (c == "mp4v") return "mpeg4";
        if (c == "mp3") return "mp3";
        if (c == "twos" || c == "sowt" || c == "lpcm") return "pcm";
        return c; // Garder tel quel si absent de la table
    }

    std::string GetPlayerVerdict() const {
        for (const auto& t : tracks) {
            if (t.type == "vide") {
                const std::string& c = t.code;
                if (c == "mjpa" || c == "jpeg" || c == "MJPG" || 
                    c == "avc1" || c == "avc3" || c == "hvc1" || c == "hev1" || c == "av01") {
                    return "LISIBLE";
                } else {
                    return "ECHEC";
                }
            }
        }
        return "SANS_IMAGE";
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n = 0;
    if (!(std::cin >> n)) return 0;

    std::vector<MediaFile> files(n);
    int mp4Count = 0;
    int lisiblesCount = 0;
    int inconnusCount = 0;

    for (int i = 0; i < n; ++i) {
        std::cin >> files[i].name >> files[i].hex >> files[i].trackCount;
        files[i].tracks.resize(files[i].trackCount);
        for (int j = 0; j < files[i].trackCount; ++j) {
            std::cin >> files[i].tracks[j].type >> files[i].tracks[j].code;
        }

        files[i].DetectContainer();

        if (files[i].container == "MP4") {
            mp4Count++;
            if (files[i].GetPlayerVerdict() == "LISIBLE") {
                lisiblesCount++;
            }
        } else if (files[i].container == "INCONNU") {
            inconnusCount++;
        }
    }

    // Affichage formaté strict
    for (int i = 0; i < n; ++i) {
        std::cout << files[i].name << " " << files[i].container << "\n";

        if (files[i].container == "MP4") {
            for (int j = 0; j < files[i].trackCount; ++j) {
                std::string trackType = (files[i].tracks[j].type == "vide") ? "VIDEO" : "AUDIO";
                std::string mappedCodec = files[i].MapCodec(files[i].tracks[j].code);
                std::cout << files[i].name << " PISTE " << (j + 1) << " " << trackType << " " << mappedCodec << "\n";
            }
            std::cout << files[i].name << " LECTEUR " << files[i].GetPlayerVerdict() << "\n";
        }
    }

    std::cout << "MP4 " << mp4Count << "\n";
    std::cout << "LISIBLES " << lisiblesCount << "\n";
    std::cout << "INCONNUS " << inconnusCount << std::endl;

    return 0;
}