#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int total_usages;
    if (!(std::cin >> total_usages)) {
        return 0;
    }

    std::unordered_map<std::string, bool> registry;
    std::vector<std::string> sequence_tracker;

    for (int idx = 0; idx < total_usages; ++idx) {
        std::string entity_name, usage_mode;
        std::cin >> entity_name >> usage_mode;

        if (registry.find(entity_name) == registry.end()) {
            registry[entity_name] = false;
            sequence_tracker.push_back(entity_name);
        }

        if (usage_mode == "VALEUR" || 
            usage_mode == "BASE" || 
            usage_mode == "CORPS" || 
            usage_mode == "TAILLE") {
            registry[entity_name] = true;
        }
    }

    int current_includes_count;
    if (!(std::cin >> current_includes_count)) {
        return 0;
    }

    std::unordered_set<std::string> active_inclusions;
    for (int idx = 0; idx < current_includes_count; ++idx) {
        std::string inc_name;
        std::cin >> inc_name;
        active_inclusions.insert(inc_name);
    }

    int total_include_req = 0;
    int total_anticipate_req = 0;
    int removable_count = 0;

    for (const auto& name : sequence_tracker) {
        bool requires_def = registry[name];
        if (requires_def) {
            std::cout << name << " INCLURE\n";
            total_include_req++;
        } else {
            std::cout << name << " ANTICIPER\n";
            total_anticipate_req++;
            if (active_inclusions.find(name) != active_inclusions.end()) {
                removable_count++;
            }
        }
    }

    std::cout << "INCLURE " << total_include_req << "\n";
    std::cout << "ANTICIPER " << total_anticipate_req << "\n";
    std::cout << "INCLUSIONS_RETIREES " << removable_count << "\n";

    return 0;
}