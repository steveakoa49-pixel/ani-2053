#include <iostream>
#include <string>

enum class Status {
    Absent,
    Writ,
    Default,
    Deleted
};

std::string statusToString(Status s) {
    switch (s) {
        case Status::Absent:  return "ABSENT";
        case Status::Writ:    return "ECRIT";
        case Status::Default: return "DEFAUT";
        case Status::Deleted: return "SUPPRIME";
    }
    return "";
}

std::string removeSpaces(const std::string& str) {
    std::string result;
    for (char c : str) {
        if (c != ' ') {
            result += c;
        }
    }
    return result;
}

Status parseStatus(const std::string& line) {
    if (line.size() >= 8 && line.compare(line.size() - 8, 8, "=delete;") == 0) {
        return Status::Deleted;
    }
    if (line.size() >= 9 && line.compare(line.size() - 9, 9, "=default;") == 0) {
        return Status::Default;
    }
    return Status::Writ;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string className;
    if (!std::getline(std::cin, className)) return 0;
    className = removeSpaces(className);

    Status destructor = Status::Absent;
    Status copyCtor = Status::Absent;
    Status copyAssign = Status::Absent;
    Status moveCtor = Status::Absent;
    Status moveAssign = Status::Absent;

    std::string rawLine;
    while (std::getline(std::cin, rawLine)) {
        auto commentPos = rawLine.find("//");
        if (commentPos != std::string::npos) {
            rawLine = rawLine.substr(0, commentPos);
        }

        std::string line = removeSpaces(rawLine);
        if (line.empty()) continue;

        // Destructeur
        if (line.find("~" + className + "(") != std::string::npos) {
            destructor = parseStatus(line);
        }
        // Constructeur de copie
        else if (line.rfind(className + "(const" + className + "&", 0) == 0) {
            std::string prefix = className + "(const" + className + "&";
            if (line.size() == prefix.size() || line[prefix.size()] != '&') {
                copyCtor = parseStatus(line);
            }
        }
        // Opérateur d'affectation par copie
        else if (line.rfind(className + "&operator=(const" + className + "&", 0) == 0) {
            std::string prefix = className + "&operator=(const" + className + "&";
            if (line.size() == prefix.size() || line[prefix.size()] != '&') {
                copyAssign = parseStatus(line);
            }
        }
        // Constructeur de déplacement
        else if (line.rfind(className + "(" + className + "&&", 0) == 0) {
            moveCtor = parseStatus(line);
        }
        // Opérateur d'affectation par déplacement
        else if (line.rfind(className + "&operator=(" + className + "&&", 0) == 0) {
            moveAssign = parseStatus(line);
        }
    }

    bool hasD = (destructor != Status::Absent);
    bool hasC = (copyCtor != Status::Absent);
    bool hasAC = (copyAssign != Status::Absent);
    bool hasM = (moveCtor != Status::Absent);
    bool hasAM = (moveAssign != Status::Absent);

    std::string rule;
    if (!hasD && !hasC && !hasAC && !hasM && !hasAM) {
        rule = "ZERO";
    } else if (hasD && hasC && hasAC && hasM && hasAM) {
        rule = "CINQ";
    } else if (hasD && hasC && hasAC && !hasM && !hasAM) {
        rule = "TROIS";
    } else {
        rule = "INCOMPLETE";
    }

    std::cout << "DESTRUCTEUR " << statusToString(destructor) << "\n";
    std::cout << "COPIE " << statusToString(copyCtor) << "\n";
    std::cout << "AFFECTATION_COPIE " << statusToString(copyAssign) << "\n";
    std::cout << "DEPLACEMENT " << statusToString(moveCtor) << "\n";
    std::cout << "AFFECTATION_DEPLACEMENT " << statusToString(moveAssign) << "\n";

    std::cout << "REGLE " << rule << "\n";

    if (rule == "INCOMPLETE") {
        if (hasM || hasAM) {
            if (!hasD)  std::cout << "MANQUE DESTRUCTEUR\n";
            if (!hasC)  std::cout << "MANQUE COPIE\n";
            if (!hasAC) std::cout << "MANQUE AFFECTATION_COPIE\n";
            if (!hasM)  std::cout << "MANQUE DEPLACEMENT\n";
            if (!hasAM) std::cout << "MANQUE AFFECTATION_DEPLACEMENT\n";
        } else {
            if (!hasD)  std::cout << "MANQUE DESTRUCTEUR\n";
            if (!hasC)  std::cout << "MANQUE COPIE\n";
            if (!hasAC) std::cout << "MANQUE AFFECTATION_COPIE\n";
        }
    }

    bool ownsResource = (destructor == Status::Writ);
    std::cout << "POSSEDE " << (ownsResource ? "OUI" : "NON") << "\n";

    bool isUnique = (copyCtor == Status::Deleted) && (moveCtor == Status::Writ || moveCtor == Status::Default);
    std::cout << "UNIQUE " << (isUnique ? "OUI" : "NON") << "\n";

    return 0;
}