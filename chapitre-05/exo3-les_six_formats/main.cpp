#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cstdint>

enum FormatType {
    GRAY8,
    GRAY_A16,
    RGB24,
    RGBA32,
    RGB96F,
    RGBA128F,
    UNKNOW
};

struct PixelFormat {
    FormatType type = FormatType::UNKNOW;
    bool color = false;
    bool opacity = false;
    bool floats = false;

    void Init(FormatType t) {
        type = t;
        switch (t) {
            case FormatType::GRAY8:
                color = false; opacity = false; floats = false; break;
            case FormatType::GRAY_A16:
                color = false; opacity = true; floats = false; break;
            case FormatType::RGB24:
                color = true; opacity = false; floats = false; break;
            case FormatType::RGBA32:
                color = true; opacity = true; floats = false; break;
            case FormatType::RGB96F:
                color = true; opacity = false; floats = true; break;
            case FormatType::RGBA128F:
                color = true; opacity = true; floats = true; break;
            default:
                color = false; opacity = false; floats = false; break;
        }
    }

    int BytesPerPixel() const {
        switch (type) {
            case FormatType::GRAY8: return 1;
            case FormatType::GRAY_A16: return 2;
            case FormatType::RGB24: return 3;
            case FormatType::RGBA32: return 4;
            case FormatType::RGB96F: return 12;
            case FormatType::RGBA128F: return 16;
            default: return 0;
        }
    }
};

struct Conversion {
    std::string sourceStr;
    std::string targetStr;
    long long w = 1;
    long long h = 1;
    PixelFormat src;
    PixelFormat tgt;
    bool isRefused = false;

    std::string GetLosses() const {
        std::string res = "";
        if (src.opacity && !tgt.opacity)
            res += "TRANSPARENCE";
        if (src.color && !tgt.color) {
            if (!res.empty()) res += "+";
            res += "COULEUR";
        }
        if (src.floats && !tgt.floats) {
            if (!res.empty()) res += "+";
            res += "ETENDUE";
        }
        if (res.empty())
            res = "AUCUNE";
        return res;
    }

    uint64_t GetSourceBytes() const {
        return static_cast<uint64_t>(w) * h * src.BytesPerPixel();
    }

    uint64_t GetTargetBytes() const {
        return static_cast<uint64_t>(w) * h * tgt.BytesPerPixel();
    }
};

FormatType ParseFormat(const std::string& s) {
    if (s == "GRAY8") return FormatType::GRAY8;
    if (s == "GRAY_A16") return FormatType::GRAY_A16;
    if (s == "RGB24") return FormatType::RGB24;
    if (s == "RGBA32") return FormatType::RGBA32;
    if (s == "RGB96F") return FormatType::RGB96F;
    if (s == "RGBA128F") return FormatType::RGBA128F;
    return FormatType::UNKNOW;
}

int main() {
    long long w = 0, h = 0;
    int n = 0;
    if (!(std::cin >> w >> h >> n)) return 0;

    std::vector<Conversion> convs(n);
    std::string line;
    std::getline(std::cin, line); // Consommer la fin de ligne

    uint64_t totalBytes = 0;
    long long sansPerteCount = 0;
    long long refuseCount = 0;

    for (int i = 0; i < n; i++) {
        std::getline(std::cin, line);
        std::istringstream iss(line);
        std::string sSrc, sTgt;
        if (!(iss >> sSrc >> sTgt)) continue;

        convs[i].sourceStr = sSrc;
        convs[i].targetStr = sTgt;
        convs[i].w = w;
        convs[i].h = h;

        FormatType ftSrc = ParseFormat(sSrc);
        FormatType ftTgt = ParseFormat(sTgt);

        if (ftSrc == FormatType::UNKNOW || ftTgt == FormatType::UNKNOW) {
            convs[i].isRefused = true;
            refuseCount++;
        } else {
            convs[i].src.Init(ftSrc);
            convs[i].tgt.Init(ftTgt);
            
            std::string losses = convs[i].GetLosses();
            if (losses == "AUCUNE") {
                sansPerteCount++;
            }
            totalBytes += convs[i].GetTargetBytes();
        }
    }

    for (int i = 0; i < n; i++) {
        if (convs[i].isRefused) {
            std::cout << convs[i].sourceStr << " " << convs[i].targetStr << " REFUSE\n";
        } else {
            std::cout << convs[i].sourceStr << " " << convs[i].targetStr << " "
                      << convs[i].GetSourceBytes() << " "
                      << convs[i].GetTargetBytes() << " "
                      << convs[i].GetLosses() << "\n";
        }
    }

    std::cout << "TOTAL " << totalBytes << "\n";
    std::cout << "SANS_PERTE " << sansPerteCount << "\n";
    std::cout << "REFUSES " << refuseCount << std::endl;

    return 0;
}