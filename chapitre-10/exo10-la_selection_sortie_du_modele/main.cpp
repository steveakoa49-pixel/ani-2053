#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <set>
#include <algorithm>

struct CanvasObject {
    std::string designation;
    bool is_selected = false;
};

struct ArchitectureContext {
    std::vector<std::string> layout;
    std::set<int> selected_indices;
    std::set<std::string> selected_ids;
};

void purge_by_indices(std::vector<std::string>& layout, 
                      const std::set<int>& target_indices) {
    for (int idx = static_cast<int>(layout.size()) - 1; idx >= 0; --idx) {
        if (target_indices.count(idx)) {
            layout.erase(layout.begin() + idx);
        }
    }
}

void print_collection(const std::vector<std::string>& collection) {
    if (collection.empty()) {
        std::cout << " AUCUN";
        return;
    }
    for (const auto& name : collection) {
        std::cout << " " << name;
    }
}

std::vector<std::string> extract_native_selection(
    const std::vector<CanvasObject>& items) {
    std::vector<std::string> results;
    for (const auto& item : items) {
        if (item.is_selected) {
            results.push_back(item.designation);
        }
    }
    return results;
}

std::vector<std::string> extract_index_selection(
    const ArchitectureContext& ctx) {
    std::vector<std::string> results;
    for (int i = 0; i < static_cast<int>(ctx.layout.size()); ++i) {
        if (ctx.selected_indices.count(i)) {
            results.push_back(ctx.layout[i]);
        }
    }
    return results;
}

std::vector<std::string> extract_id_selection(
    const ArchitectureContext& ctx) {
    std::vector<std::string> results;
    for (const auto& name : ctx.layout) {
        if (ctx.selected_ids.count(name)) {
            results.push_back(name);
        }
    }
    return results;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<CanvasObject> native_model;
    ArchitectureContext index_model;
    ArchitectureContext id_model;

    std::string stream_line;
    while (std::getline(std::cin, stream_line)) {
        std::istringstream tokenizer(stream_line);
        std::string command;
        if (!(tokenizer >> command)) {
            continue;
        }

        if (command == "AJOUTE") {
            std::string name;
            tokenizer >> name;
            native_model.push_back({name, false});
            index_model.layout.push_back(name);
            id_model.layout.push_back(name);
        }
        else if (command == "CLIC") {
            int pos;
            tokenizer >> pos;

            for (auto& item : native_model) {
                item.is_selected = false;
            }
            index_model.selected_indices.clear();
            id_model.selected_ids.clear();

            if (pos >= 0 && pos < static_cast<int>(native_model.size())) {
                native_model[pos].is_selected = true;
            }
            if (pos >= 0 && pos < static_cast<int>(index_model.layout.size())) {
                index_model.selected_indices.insert(pos);
            }
            if (pos >= 0 && pos < static_cast<int>(id_model.layout.size())) {
                id_model.selected_ids.insert(id_model.layout[pos]);
            }
        }
        else if (command == "AJOUTE_SEL") {
            int pos;
            tokenizer >> pos;

            if (pos >= 0 && pos < static_cast<int>(native_model.size())) {
                native_model[pos].is_selected = true;
            }
            if (pos >= 0 && pos < static_cast<int>(index_model.layout.size())) {
                index_model.selected_indices.insert(pos);
            }
            if (pos >= 0 && pos < static_cast<int>(id_model.layout.size())) {
                id_model.selected_ids.insert(id_model.layout[pos]);
            }
        }
        else if (command == "ECHANGE") {
            int p1, p2;
            tokenizer >> p1 >> p2;

            if (p1 >= 0 && p2 >= 0 && 
                p1 < static_cast<int>(native_model.size()) && 
                p2 < static_cast<int>(native_model.size())) {
                std::swap(native_model[p1], native_model[p2]);
            }
            if (p1 >= 0 && p2 >= 0 && 
                p1 < static_cast<int>(index_model.layout.size()) && 
                p2 < static_cast<int>(index_model.layout.size())) {
                std::swap(index_model.layout[p1], index_model.layout[p2]);
            }
            if (p1 >= 0 && p2 >= 0 && 
                p1 < static_cast<int>(id_model.layout.size()) && 
                p2 < static_cast<int>(id_model.layout.size())) {
                std::swap(id_model.layout[p1], id_model.layout[p2]);
            }
        }
        else if (command == "RETIRE") {
            int pos;
            tokenizer >> pos;

            if (pos >= 0 && pos < static_cast<int>(native_model.size())) {
                native_model.erase(native_model.begin() + pos);
            }
            if (pos >= 0 && pos < static_cast<int>(index_model.layout.size())) {
                index_model.layout.erase(index_model.layout.begin() + pos);
            }
            if (pos >= 0 && pos < static_cast<int>(id_model.layout.size())) {
                id_model.layout.erase(id_model.layout.begin() + pos);
            }
        }
        else if (command == "SUPPRIME") {
            native_model.erase(
                std::remove_if(native_model.begin(), native_model.end(), 
                               [](const CanvasObject& obj) {
                    return obj.is_selected;
                }),
                native_model.end()
            );

            purge_by_indices(index_model.layout, index_model.selected_indices);
            index_model.selected_indices.clear();

            id_model.layout.erase(
                std::remove_if(id_model.layout.begin(), id_model.layout.end(), 
                               [&id_model](const std::string& name) {
                    return id_model.selected_ids.count(name) > 0;
                }),
                id_model.layout.end()
            );
            id_model.selected_ids.clear();
        }
    }

    std::vector<std::string> native_board;
    for (const auto& item : native_model) {
        native_board.push_back(item.designation);
    }

    std::vector<std::string> sel_native = extract_native_selection(native_model);
    std::vector<std::string> sel_index = extract_index_selection(index_model);
    std::vector<std::string> sel_id = extract_id_selection(id_model);

    std::cout << "DANS_ITEM PLANCHE";
    print_collection(native_board);
    std::cout << "\n";

    std::cout << "DANS_ITEM SELECTION";
    print_collection(sel_native);
    std::cout << "\n";

    std::cout << "PAR_INDEX PLANCHE";
    print_collection(index_model.layout);
    std::cout << "\n";

    std::cout << "PAR_INDEX SELECTION";
    print_collection(sel_index);
    std::cout << "\n";

    std::cout << "PAR_ID PLANCHE";
    print_collection(id_model.layout);
    std::cout << "\n";

    std::cout << "PAR_ID SELECTION";
    print_collection(sel_id);
    std::cout << "\n";

    std::vector<std::string> divergences;
    if (index_model.layout != native_board || sel_index != sel_native) {
        divergences.push_back("PAR_INDEX");
    }
    if (id_model.layout != native_board || sel_id != sel_native) {
        divergences.push_back("PAR_ID");
    }

    std::cout << "FAUX";
    print_collection(divergences);
    std::cout << "\n";

    return 0;
}