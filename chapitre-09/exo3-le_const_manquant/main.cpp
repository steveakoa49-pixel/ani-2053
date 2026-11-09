#include <iostream>
#include <string>
#include <vector>

struct FuncNode {
    std::string label;
    bool already_const;
    bool modifies_state;
    std::vector<std::string> calls;
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int total_funcs;
    if (!(std::cin >> total_funcs)) return 0;

    std::vector<FuncNode> registry(total_funcs);
    for (int i = 0; i < total_funcs; ++i) {
        std::string const_token;
        int mod_flag, count_calls;
        std::cin >> registry[i].label >> const_token >> mod_flag >> count_calls;
        registry[i].already_const = (const_token == "const");
        registry[i].modifies_state = (mod_flag == 1);
        registry[i].calls.resize(count_calls);
        for (int j = 0; j < count_calls; ++j) {
            std::cin >> registry[i].calls[j];
        }
    }

    std::vector<bool> candidate(total_funcs, true);
    for (int i = 0; i < total_funcs; ++i) {
        if (registry[i].already_const || registry[i].modifies_state) {
            candidate[i] = false;
        }
    }

    bool updated = true;
    while (updated) {
        updated = false;
        for (int i = 0; i < total_funcs; ++i) {
            if (!candidate[i]) continue;
            for (const auto& target : registry[i].calls) {
                bool found_invalid = false;
                for (int j = 0; j < total_funcs; ++j) {
                    if (registry[j].label == target && !registry[j].already_const && !candidate[j]) {
                        found_invalid = true;
                        break;
                    }
                }
                if (found_invalid) {
                    candidate[i] = false;
                    updated = true;
                    break;
                }
            }
        }
    }

    // Affichage de POURRAIT
    std::cout << "POURRAIT";
    bool empty_candidates = true;
    for (int i = 0; i < total_funcs; ++i) {
        if (candidate[i]) {
            std::cout << " " << registry[i].label;
            empty_candidates = false;
        }
    }
    if (empty_candidates) {
        std::cout << " AUCUN";
    }
    std::cout << "\n";

    // Affichage de RACINES
    std::cout << "RACINES";
    bool empty_roots = true;
    for (int i = 0; i < total_funcs; ++i) {
        if (!candidate[i]) continue;
        bool is_root = true;
        for (const auto& target : registry[i].calls) {
            for (int j = 0; j < total_funcs; ++j) {
                if (registry[j].label == target && !registry[j].already_const) {
                    is_root = false;
                    break;
                }
            }
            if (!is_root) break;
        }
        if (is_root) {
            std::cout << " " << registry[i].label;
            empty_roots = false;
        }
    }
    if (empty_roots) {
        std::cout << " AUCUN";
    }
    std::cout << "\n";

    // Calcul des PASSES
    std::vector<bool> state_const(total_funcs);
    for (int i = 0; i < total_funcs; ++i) {
        state_const[i] = registry[i].already_const;
    }

    int pass_counter = 0;
    int remaining_candidates = 0;
    for (int i = 0; i < total_funcs; ++i) {
        if (candidate[i]) remaining_candidates++;
    }

    while (remaining_candidates > 0) {
        std::vector<int> batch;
        for (int i = 0; i < total_funcs; ++i) {
            if (!candidate[i] || state_const[i]) continue;
            bool ready = true;
            for (const auto& target : registry[i].calls) {
                for (int j = 0; j < total_funcs; ++j) {
                    if (registry[j].label == target && !state_const[j]) {
                        ready = false;
                        break;
                    }
                }
                if (!ready) break;
            }
            if (ready) {
                batch.push_back(i);
            }
        }

        for (int idx : batch) {
            state_const[idx] = true;
            remaining_candidates--;
        }
        pass_counter++;
    }

    std::cout << "PASSES " << pass_counter << "\n";

    return 0;
}