#include <iostream>
#include <string>
#include <vector>

struct EntityRecord {
    std::string label;
    bool is_disposed;
    std::vector<int> links;
};

struct ScopeFrame {
    std::vector<int> members;
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<EntityRecord> registry;
    std::vector<ScopeFrame> scopes;
    scopes.push_back({}); // Bloc principal de la fonction

    auto release_entity = [&](int index, bool explicit_close) -> bool {
        if (registry[index].is_disposed) {
            return true;
        }

        // Vérification des dépendances dans l'ordre exact de lecture
        for (int dep_idx : registry[index].links) {
            if (registry[dep_idx].is_disposed) {
                std::cout << "PLANTAGE " << registry[index].label << " " << registry[dep_idx].label << "\n";
                return false;
            }
        }

        registry[index].is_disposed = true;
        if (explicit_close) {
            std::cout << "FERME " << registry[index].label << "\n";
        } else {
            std::cout << "DETRUIT " << registry[index].label << "\n";
        }
        return true;
    };

    std::string token;
    while (std::cin >> token) {
        if (token == "DECL") {
            std::string name;
            std::cin >> name;
            registry.push_back({name, false, {}});
            scopes.back().members.push_back(registry.size() - 1);
        } 
        else if (token == "DEPEND") {
            std::string name_a, name_b;
            std::cin >> name_a >> name_b;
            int idx_a = -1, idx_b = -1;
            for (int i = (int)registry.size() - 1; i >= 0; --i) {
                if (registry[i].label == name_a && idx_a == -1) idx_a = i;
                if (registry[i].label == name_b && idx_b == -1) idx_b = i;
                if (idx_a != -1 && idx_b != -1) break;
            }
            if (idx_a != -1) {
                registry[idx_a].links.push_back(idx_b);
            }
        } 
        else if (token == "FERME") {
            std::string name;
            std::cin >> name;
            int idx = -1;
            for (int i = (int)registry.size() - 1; i >= 0; --i) {
                if (registry[i].label == name) {
                    idx = i;
                    break;
                }
            }
            if (idx != -1 && !registry[idx].is_disposed) {
                if (!release_entity(idx, true)) {
                    return 0;
                }
            }
        } 
        else if (token == "{") {
            scopes.push_back({});
        } 
        else if (token == "}") {
            if (!scopes.empty()) {
                ScopeFrame current_frame = scopes.back();
                scopes.pop_back();
                for (int i = (int)current_frame.members.size() - 1; i >= 0; --i) {
                    int idx = current_frame.members[i];
                    if (!registry[idx].is_disposed) {
                        if (!release_entity(idx, false)) {
                            return 0;
                        }
                    }
                }
            }
        }
    }

    // Fermeture automatique des blocs restants à la fin de l'entrée
    while (!scopes.empty()) {
        ScopeFrame current_frame = scopes.back();
        scopes.pop_back();
        for (int i = (int)current_frame.members.size() - 1; i >= 0; --i) {
            int idx = current_frame.members[i];
            if (!registry[idx].is_disposed) {
                if (!release_entity(idx, false)) {
                    return 0;
                }
            }
        }
    }

    std::cout << "PROPRE\n";
    return 0;
}