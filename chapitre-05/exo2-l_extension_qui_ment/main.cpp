#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cctype>

enum Format {
    PNG,
    JPEG,
    BMP,
    QOI,
    GIF,
    ICO,
    HDR,
    EXR,
    PBM,
    PGM,
    PPM,
    TGA,
    SVG,
    NONE
};

enum FileState {
    ACCEPTED,
    REFUSED,
    LIE,
    UNKNOW
};

struct File {
    std::string name = "";
    std::string octets = "";
    std::string extention = "";
    Format fr = Format::NONE;
    Format frExt = Format::NONE;
    FileState state = FileState::UNKNOW;
    std::string b[20] = {}; // Tableau élargi pour stocker les octets en toute sécurité
    int taille = 0;

    // Convertit une chaîne en majuscules pour uniformiser la lecture hexadécimale
    std::string ToUpper(const std::string& str) {
        std::string res = str;
        for (char& c : res) {
            c = std::toupper(c);
        }
        return res;
    }

    friend std::istream& operator>> (std::istream& is, File& f) {
        return is >> f.name >> f.taille >> f.octets;
    }

    friend std::ostream& operator<< (std::ostream& os, const File& f) {
        std::string r = "";
        switch (f.state) {
            case FileState::ACCEPTED :
                r = " OK";
                break;
            case FileState::LIE :
                r = " MENT";
                break;
            case FileState::REFUSED :
                r = " REFUSE";
                break;
            default:
                break;
        }
        return os << f.name << " " << const_cast<File*>(std::addressof(f))->FormatToString() << r;
    }

    void InitialiseFile() {
        if (octets.empty() || octets[0] == '-')
            return;
        std::string hex = ToUpper(octets);
        for (size_t i = 0; i < hex.size() && (i / 2) < 20; i += 2) {
            if (i + 2 <= hex.size()) {
                b[i / 2] = hex.substr(i, 2);
            }
        }
    }

    void FindExtension() {
        if (name.empty())
            return;
        int counter = -1;
        for (size_t i = 0; i < name.size(); i++) {
            if (name[i] == '.') {
                counter = i;
            }
        }
        if (counter != -1) {
            for (size_t i = counter + 1; i < name.size(); i++)
                extention += std::tolower(name[i]);
        } else {
            extention = "";
        }
    }

    void ExtensionToFormat() {
        if (extention == "png")
            frExt = Format::PNG;
        else if (extention == "jpg" || extention == "jpeg")
            frExt = Format::JPEG;
        else if (extention == "bmp")
            frExt = Format::BMP;
        else if (extention == "qoi")
            frExt = Format::QOI;
        else if (extention == "gif")
            frExt = Format::GIF;
        else if (extention == "ico" || extention == "cur")
            frExt = Format::ICO;
        else if (extention == "hdr")
            frExt = Format::HDR;
        else if (extention == "exr")
            frExt = Format::EXR;
        else if (extention == "pbm")
            frExt = Format::PBM;
        else if (extention == "pgm")
            frExt = Format::PGM;
        else if (extention == "ppm")
            frExt = Format::PPM;
        else if (extention == "tga")
            frExt = Format::TGA;
        else if (extention == "svg")
            frExt = Format::SVG;
        else {
            frExt = Format::NONE;
            // On ne met pas state = REFUSED ici, car un fichier avec une extension inconnue 
            // peut quand même être reconnu par ses octets (ce qui constituera un MENT).
        }
    }

    std::string FormatToString() {
        switch (fr) {
            case Format::PNG: return "PNG";
            case Format::JPEG: return "JPEG";
            case Format::BMP: return "BMP";
            case Format::QOI: return "QOI";
            case Format::GIF: return "GIF";
            case Format::ICO: return "ICO";
            case Format::HDR: return "HDR";
            case Format::EXR: return "EXR";
            case Format::PBM: return "PBM";
            case Format::PGM: return "PGM";
            case Format::PPM: return "PPM";
            case Format::TGA: return "TGA";
            case Format::SVG: return "SVG";
            case Format::NONE: return "";
            default: break;
        }
        return "";
    }

    void OctetsToFormat() {
        if (octets.empty() || octets[0] == '-') {
            fr = Format::NONE;
            state = FileState::REFUSED;
            return;
        }
            
        // Règle 1 : Si taille < 4 : REFUSE
        if (taille < 4) {
            fr = Format::NONE;
            state = FileState::REFUSED;
            return;
        }
        // Règle 2 : PNG
        else if (taille >= 8 && b[0] == "89" && b[1] == "50" && b[2] == "4E" && b[3] == "47") {
            fr = Format::PNG;
            state = FileState::ACCEPTED;
        }
        // Règle 3 : JPEG
        else if (b[0] == "FF" && b[1] == "D8" && b[2] == "FF") {
            fr = Format::JPEG;
            state = FileState::ACCEPTED;
        }
        // Règle 4 : BMP
        else if (b[0] == "42" && b[1] == "4D") {
            fr = Format::BMP;
            state = FileState::ACCEPTED;
        }
        // Règle 5 : QOI
        else if (b[0] == "71" && b[1] == "6F" && b[2] == "69" && b[3] == "66") {
            fr = Format::QOI;
            state = FileState::ACCEPTED;
        }
        // Règle 6 : GIF
        else if (b[0] == "47" && b[1] == "49" && b[2] == "46" && b[3] == "38") {
            fr = Format::GIF;
            state = FileState::ACCEPTED;
        }
        // Règle 7 : ICO
        else if (b[0] == "00" && b[1] == "00" && (b[2] == "01" || b[2] == "02") && b[3] == "00") {
            fr = Format::ICO;
            state = FileState::ACCEPTED;
        }
        // Règle 8 : HDR
        else if (taille >= 10 && b[0] == "23" && b[1] == "3F") {
            fr = Format::HDR;
            state = FileState::ACCEPTED;
        }
        // Règle 9 : EXR
        else if (b[0] == "76" && b[1] == "2F" && b[2] == "31" && b[3] == "01") {
            fr = Format::EXR;
            state = FileState::ACCEPTED;
        }
        // Règle 10 : PBM, PGM, PPM
        else if (b[0] == "50" && b[1] >= "31" && b[1] <= "36") {
            if (b[1] == "31" || b[1] == "34") fr = Format::PBM;
            else if (b[1] == "32" || b[1] == "35") fr = Format::PGM;
            else fr = Format::PPM;
            state = FileState::ACCEPTED;
        }
        // Règle 11 : TGA (supposition basée sur taille >= 18 et b2 spécifique)
        else if (taille >= 18 && (b[2] == "00" || b[2] == "01" || b[2] == "02" || b[2] == "03" || b[2] == "09" || b[2] == "0A" || b[2] == "0B")) {
            fr = Format::TGA;
            state = FileState::ACCEPTED;
        }
        // Règle 12 : SVG (sauter EF BB BF et espaces/retours chariot, puis chercher <?xml ou <svg)
        else {
            int idx = 0;
            if (b[0] == "EF" && b[1] == "BB" && b[2] == "BF") {
                idx = 3;
            }
            while (idx < 20 && !b[idx].empty() && (b[idx] == "20" || b[idx] == "09" || b[idx] == "0A" || b[idx] == "0D")) {
                idx++;
            }
            bool isXml = (b[idx] == "3C" && b[idx+1] == "3F" && b[idx+2] == "78" && b[idx+3] == "6D" && b[idx+4] == "6C");
            bool isSvg = (b[idx] == "3C" && b[idx+1] == "73" && b[idx+2] == "76" && b[idx+3] == "67");

            if (isXml || isSvg) {
                fr = Format::SVG;
                state = FileState::ACCEPTED;
            } else {
                fr = Format::NONE;
                state = FileState::REFUSED;
            }
        }
    }

    bool IsLiying() {
        if (octets.empty() || octets[0] == '-')
            return false;
        if (state == FileState::ACCEPTED) {
            if (frExt != fr) {
                state = FileState::LIE;
                return true;
            }
        }
        return false;
    }
};

int main() {
    int n = 0;
    if (!(std::cin >> n)) return 0;
    int LU = 0, MENSONGES = 0, REFUSE = 0;
    std::string content = "";
    std::getline(std::cin, content); // Consommer la fin de ligne du nombre n

    std::vector<File> allFile(n);

    for (int i = 0; i < n; i++) {
        std::getline(std::cin, content);
        std::istringstream iss(content);
        iss >> allFile[i];
        
        allFile[i].InitialiseFile();
        allFile[i].FindExtension();
        allFile[i].ExtensionToFormat();
        allFile[i].OctetsToFormat();
        
        if (allFile[i].IsLiying()) {
            LU++;
            MENSONGES++;
        }
        else if (allFile[i].state == FileState::ACCEPTED) {
            LU++;
        }
        else if (allFile[i].state == FileState::REFUSED) {
            REFUSE++;
        }
    }

    for (int i = 0; i < n; i++) {
        std::cout << allFile[i] << "\n";
    }
    std::cout << "LUS " << LU << "\n";
    std::cout << "MENSONGES " << MENSONGES << "\n";
    std::cout << "REFUSES " << REFUSE << std::endl;

    return 0;
}