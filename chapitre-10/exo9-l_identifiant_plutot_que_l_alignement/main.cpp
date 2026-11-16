#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<int> active_sequence;
    int next_unique_id = 1;

    int sync_opportunities = 0;
    int propagation_cost = 0;
    int query_lookups = 0;

    int total_ops;
    if (!(std::cin >> total_ops)) {
        return 0;
    }

    for (int step = 0; step < total_ops; ++step) {
        std::string action;
        std::cin >> action;

        if (action == "AJOUTE") {
            active_sequence.push_back(next_unique_id++);
        } 
        else if (action == "SUPPRIME") {
            int count;
            std::cin >> count;
            std::vector<int> target_indices(count);
            for (int i = 0; i < count; ++i) {
                std::cin >> target_indices[i];
            }

            for (int i = count - 1; i >= 0; --i) {
                int pos = target_indices[i];
                if (pos >= 0 && pos < static_cast<int>(active_sequence.size())) {
                    active_sequence.erase(active_sequence.begin() + pos);
                }
            }

            sync_opportunities++;
            propagation_cost += 2 * count;
        } 
        else if (action == "MONTE") {
            int idx;
            std::cin >> idx;
            if (idx >= 0 && idx + 1 < static_cast<int>(active_sequence.size())) {
                std::swap(active_sequence[idx], active_sequence[idx + 1]);
                sync_opportunities++;
                propagation_cost += 2;
            }
        } 
        else if (action == "DESCEND") {
            int idx;
            std::cin >> idx;
            if (idx > 0 && idx < static_cast<int>(active_sequence.size())) {
                std::swap(active_sequence[idx], active_sequence[idx - 1]);
                sync_opportunities++;
                propagation_cost += 2;
            }
        } 
        else if (action == "DESSINE") {
            query_lookups += static_cast<int>(active_sequence.size());
        }
    }

    std::cout << "ORDRE";
    if (active_sequence.empty()) {
        std::cout << " AUCUN\n";
    } else {
        for (int val : active_sequence) {
            std::cout << " " << val;
        }
        std::cout << "\n";
    }

    std::cout << "OCCASIONS " << sync_opportunities << "\n";
    std::cout << "REPERCUTES " << propagation_cost << "\n";
    std::cout << "RECHERCHES " << query_lookups << "\n";

    return 0;
}