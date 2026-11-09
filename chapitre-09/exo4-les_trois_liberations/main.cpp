#include <iostream>
#include <string>
#include <vector>

struct AssetItem {
    int id;
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int free_s, free_v, free_f;
    if (!(std::cin >> free_s >> free_v >> free_f)) return 0;

    int op_count;
    if (!(std::cin >> op_count)) return 0;

    std::vector<AssetItem> active_pool;
    std::vector<bool> released_state;
    int total_created = 0;

    auto purge_item = [&](int target_id, int times) -> bool {
        for (int k = 0; k < times; ++k) {
            if (released_state[target_id - 1]) {
                return false;
            }
            released_state[target_id - 1] = true;
        }
        return true;
    };

    for (int step = 1; step <= op_count; ++step) {
        std::string command;
        std::cin >> command;

        if (command == "AJOUTE") {
            total_created++;
            active_pool.push_back({total_created});
            released_state.push_back(false);
        } 
        else if (command == "SUPPRIME") {
            int idx;
            std::cin >> idx;
            int target_id = active_pool[idx].id;
            if (!purge_item(target_id, free_s)) {
                std::cout << "PLANTAGE " << step << " TEXTURE " << target_id << "\n";
                return 0;
            }
            active_pool.erase(active_pool.begin() + idx);
        } 
        else if (command == "VIDE") {
            for (const auto& item : active_pool) {
                if (!purge_item(item.id, free_v)) {
                    std::cout << "PLANTAGE " << step << " TEXTURE " << item.id << "\n";
                    return 0;
                }
            }
            active_pool.clear();
        }
    }

    for (const auto& item : active_pool) {
        if (!purge_item(item.id, free_f)) {
            std::cout << "PLANTAGE FIN TEXTURE " << item.id << "\n";
            return 0;
        }
    }

    std::cout << "CREEES " << total_created << "\n";

    int leak_count = 0;
    for (int i = 0; i < total_created; ++i) {
        if (!released_state[i]) {
            leak_count++;
        }
    }

    std::cout << "FUITES " << leak_count << "\n";
    std::cout << "PERDUES";

    bool none_lost = true;
    for (int i = 0; i < total_created; ++i) {
        if (!released_state[i]) {
            std::cout << " " << (i + 1);
            none_lost = false;
        }
    }

    if (none_lost) {
        std::cout << " AUCUN";
    }
    std::cout << "\n";

    return 0;
}