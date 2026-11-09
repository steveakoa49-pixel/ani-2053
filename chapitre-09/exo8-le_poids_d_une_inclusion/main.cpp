#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>

struct SourceEntity {
    std::string designation;
    std::vector<std::string> dependencies;
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int count_elements;
    if (!(std::cin >> count_elements)) {
        return 0;
    }

    std::unordered_map<std::string, int> position_map;
    std::vector<SourceEntity> entity_list(count_elements);
    std::vector<std::vector<int>> reverse_graph(count_elements);

    for (int i = 0; i < count_elements; ++i) {
        std::cin >> entity_list[i].designation;
        position_map[entity_list[i].designation] = i;
        int dep_count;
        std::cin >> dep_count;
        entity_list[i].dependencies.resize(dep_count);
        for (int j = 0; j < dep_count; ++j) {
            std::cin >> entity_list[i].dependencies[j];
        }
    }

    for (int i = 0; i < count_elements; ++i) {
        for (const auto& inc : entity_list[i].dependencies) {
            auto it = position_map.find(inc);
            if (it != position_map.end()) {
                reverse_graph[it->second].push_back(i);
            }
        }
    }

    auto compute_impact = [&](int start_idx) -> int {
        std::vector<bool> seen(count_elements, false);
        std::queue<int> processing_queue;

        processing_queue.push(start_idx);
        seen[start_idx] = true;

        int affected_cpp_total = 0;

        while (!processing_queue.empty()) {
            int current = processing_queue.front();
            processing_queue.pop();

            const std::string& name = entity_list[current].designation;
            if (name.size() >= 4 && name.compare(name.size() - 4, 4, ".cpp") == 0) {
                affected_cpp_total++;
            }

            for (int next_node : reverse_graph[current]) {
                if (!seen[next_node]) {
                    seen[next_node] = true;
                    processing_queue.push(next_node);
                }
            }
        }
        return affected_cpp_total;
    };

    int query_count;
    if (!(std::cin >> query_count)) {
        return 0;
    }

    for (int q = 0; q < query_count; ++q) {
        std::string query_name;
        std::cin >> query_name;
        auto it = position_map.find(query_name);
        if (it != position_map.end()) {
            int score = compute_impact(it->second);
            std::cout << query_name << " " << score << "\n";
        }
    }

    std::string heaviest_header = "AUCUN";
    int max_impact = -1;

    for (int i = 0; i < count_elements; ++i) {
        const std::string& name = entity_list[i].designation;
        if (name.size() >= 2 && name.compare(name.size() - 2, 2, ".h") == 0) {
            int score = compute_impact(i);
            if (score > max_impact) {
                max_impact = score;
                heaviest_header = name;
            }
        }
    }

    if (heaviest_header == "AUCUN") {
        std::cout << "PLUS_LOURD AUCUN\n";
    } else {
        std::cout << "PLUS_LOURD " << heaviest_header << " " << max_impact << "\n";
    }

    return 0;
}