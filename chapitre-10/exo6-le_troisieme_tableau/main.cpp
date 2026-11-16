#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

struct SyncPolicy {
    bool sync_textures = false;
    bool sync_sources = false;
};

SyncPolicy parse_sync_rule(const std::string& line) {
    SyncPolicy policy;
    std::istringstream stream(line);
    std::string command, target;
    stream >> command;
    while (stream >> target) {
        if (target == "textures") {
            policy.sync_textures = true;
        } else if (target == "sources") {
            policy.sync_sources = true;
        }
    }
    return policy;
}

void push_element(std::vector<std::string>& list, const std::string& val) {
    list.push_back(val);
}

void purge_elements(std::vector<std::string>& list, const std::vector<int>& indices) {
    for (int i = static_cast<int>(indices.size()) - 1; i >= 0; --i) {
        int pos = indices[i];
        if (pos >= 0 && pos < static_cast<int>(list.size())) {
            list.erase(list.begin() + pos);
        }
    }
}

void swap_elements(std::vector<std::string>& list, int idx1, int idx2) {
    if (idx1 >= 0 && idx2 >= 0 && idx1 < static_cast<int>(list.size()) && idx2 < static_cast<int>(list.size())) {
        std::swap(list[idx1], list[idx2]);
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<std::string> ref_model;
    std::vector<std::string> gfx_textures;
    std::vector<std::string> src_bytes;

    std::string line;
    if (!std::getline(std::cin, line)) return 0;
    SyncPolicy policy_add = parse_sync_rule(line);

    if (!std::getline(std::cin, line)) return 0;
    SyncPolicy policy_del = parse_sync_rule(line);

    if (!std::getline(std::cin, line)) return 0;
    SyncPolicy policy_swap = parse_sync_rule(line);

    int op_count;
    if (!(std::cin >> op_count)) return 0;

    for (int k = 0; k < op_count; ++k) {
        std::string op_name;
        std::cin >> op_name;

        if (op_name == "AJOUTE") {
            std::string name;
            std::cin >> name;
            push_element(ref_model, name);
            if (policy_add.sync_textures) push_element(gfx_textures, name);
            if (policy_add.sync_sources) push_element(src_bytes, name);
        } 
        else if (op_name == "SUPPRIME") {
            int count;
            std::cin >> count;
            std::vector<int> target_indices(count);
            for (int j = 0; j < count; ++j) {
                std::cin >> target_indices[j];
            }
            purge_elements(ref_model, target_indices);
            if (policy_del.sync_textures) purge_elements(gfx_textures, target_indices);
            if (policy_del.sync_sources) purge_elements(src_bytes, target_indices);
        } 
        else if (op_name == "MONTE") {
            int idx;
            std::cin >> idx;
            if (idx + 1 < static_cast<int>(ref_model.size())) {
                swap_elements(ref_model, idx, idx + 1);
                if (policy_swap.sync_textures) swap_elements(gfx_textures, idx, idx + 1);
                if (policy_swap.sync_sources) swap_elements(src_bytes, idx, idx + 1);
            }
        } 
        else if (op_name == "DESCEND") {
            int idx;
            std::cin >> idx;
            if (idx > 0) {
                swap_elements(ref_model, idx, idx - 1);
                if (policy_swap.sync_textures) swap_elements(gfx_textures, idx, idx - 1);
                if (policy_swap.sync_sources) swap_elements(src_bytes, idx, idx - 1);
            }
        }
    }

    std::size_t max_len = std::max({ref_model.size(), gfx_textures.size(), src_bytes.size()});
    int mismatch_count = 0;

    for (std::size_t i = 0; i < max_len; ++i) {
        std::string m = i < ref_model.size() ? ref_model[i] : "-";
        std::string t = i < gfx_textures.size() ? gfx_textures[i] : "-";
        std::string s = i < src_bytes.size() ? src_bytes[i] : "-";

        std::cout << i << " " << m << " " << t << " " << s << "\n";

        if (m != t || m != s) {
            mismatch_count++;
        }
    }

    std::cout << "DECALES " << mismatch_count << "\n";

    return 0;
}