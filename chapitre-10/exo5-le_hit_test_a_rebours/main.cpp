#include <iostream>
#include <vector>
#include <string>
#include <cmath>

struct VisualNode {
    std::string identifier;
    double center_x;
    double center_y;
    double half_width;
    double half_height;
};

bool evaluate_intersection(const VisualNode& node, double coord_x, double coord_y) {
    return std::abs(coord_x - node.center_x) <= node.half_width &&
           std::abs(coord_y - node.center_y) <= node.half_height;
}

std::string locate_element(const std::vector<VisualNode>& collection, double coord_x, double coord_y, bool reverse_mode) {
    if (reverse_mode) {
        for (int idx = static_cast<int>(collection.size()) - 1; idx >= 0; --idx) {
            if (evaluate_intersection(collection[idx], coord_x, coord_y)) {
                return collection[idx].identifier;
            }
        }
    } else {
        for (std::size_t idx = 0; idx < collection.size(); ++idx) {
            if (evaluate_intersection(collection[idx], coord_x, coord_y)) {
                return collection[idx].identifier;
            }
        }
    }
    return "AUCUN";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int total_elements;
    if (!(std::cin >> total_elements)) {
        return 0;
    }

    std::vector<VisualNode> layout_elements;
    for (int idx = 0; idx < total_elements; ++idx) {
        VisualNode element;
        double native_w, native_h, scale_factor;

        std::cin >> element.identifier
                 >> element.center_x
                 >> element.center_y
                 >> native_w
                 >> native_h
                 >> scale_factor;

        element.half_width = native_w * scale_factor * 0.5;
        element.half_height = native_h * scale_factor * 0.5;

        layout_elements.push_back(element);
    }

    int click_events_count;
    if (!(std::cin >> click_events_count)) {
        return 0;
    }

    int discrepancy_counter = 0;

    for (int step = 1; step <= click_events_count; ++step) {
        double query_x, query_y;
        std::cin >> query_x >> query_y;

        std::string top_match = locate_element(layout_elements, query_x, query_y, true);
        std::string base_match = locate_element(layout_elements, query_x, query_y, false);

        std::cout << "CLIC " << step << " " << top_match << " " << base_match << "\n";

        if (top_match != base_match) {
            discrepancy_counter++;
        }
    }

    std::cout << "ERREURS " << discrepancy_counter << "\n";

    return 0;
}