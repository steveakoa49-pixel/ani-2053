#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

struct SlotNode {
    std::string tag;
    int held_ref;
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int line_total;
    if (!(std::cin >> line_total)) {
        return 0;
    }

    std::vector<SlotNode> slots;
    std::vector<std::string> appearance_order;

    auto locate_slot = [&](const std::string& name) -> int {
        for (size_t i = 0; i < slots.size(); ++i) {
            if (slots[i].tag == name) {
                return static_cast<int>(i);
            }
        }
        return -1;
    };

    auto register_usage = [&](const std::string& name) {
        if (locate_slot(name) == -1) {
            slots.push_back({name, -1});
            appearance_order.push_back(name);
        }
    };

    int object_counter = 0;
    int destruction_counter = 0;
    int null_usage_counter = 0;

    std::vector<int> termination_sequence;
    std::vector<int> refusal_lines;

    struct InstructionRecord {
        int index;
        std::string op;
        std::string arg1;
        std::string arg2;
    };

    std::vector<InstructionRecord> stream(line_total);
    for (int idx = 0; idx < line_total; ++idx) {
        stream[idx].index = idx + 1;
        std::cin >> stream[idx].op;
        if (stream[idx].op == "NEW" || stream[idx].op == "RESET" || stream[idx].op == "USE") {
            std::cin >> stream[idx].arg1;
            register_usage(stream[idx].arg1);
        } else if (stream[idx].op == "MOVE" || stream[idx].op == "COPY") {
            std::cin >> stream[idx].arg1 >> stream[idx].arg2;
            register_usage(stream[idx].arg1);
            register_usage(stream[idx].arg2);
        }
    }

    for (const auto& inst : stream) {
        if (inst.op == "COPY") {
            refusal_lines.push_back(inst.index);
        }
    }

    if (!refusal_lines.empty()) {
        for (int line_num : refusal_lines) {
            std::cout << "REFUSE " << line_num << "\n";
        }
        return 0;
    }

    slots.clear();

    auto get_or_create_slot = [&](const std::string& name) -> int {
        for (size_t i = 0; i < slots.size(); ++i) {
            if (slots[i].tag == name) {
                return static_cast<int>(i);
            }
        }
        slots.push_back({name, -1});
        return static_cast<int>(slots.size() - 1);
    };

    for (const auto& inst : stream) {
        if (inst.op == "NEW") {
            int s_idx = get_or_create_slot(inst.arg1);
            object_counter++;
            if (slots[s_idx].held_ref != -1) {
                termination_sequence.push_back(slots[s_idx].held_ref);
                destruction_counter++;
            }
            slots[s_idx].held_ref = object_counter;
        } 
        else if (inst.op == "MOVE") {
            int src_idx = get_or_create_slot(inst.arg1);
            int dst_idx = get_or_create_slot(inst.arg2);

            int transferred = slots[src_idx].held_ref;
            slots[src_idx].held_ref = -1;

            if (slots[dst_idx].held_ref != -1) {
                termination_sequence.push_back(slots[dst_idx].held_ref);
                destruction_counter++;
            }
            slots[dst_idx].held_ref = transferred;
        } 
        else if (inst.op == "RESET") {
            int s_idx = get_or_create_slot(inst.arg1);
            if (slots[s_idx].held_ref != -1) {
                termination_sequence.push_back(slots[s_idx].held_ref);
                destruction_counter++;
                slots[s_idx].held_ref = -1;
            }
        } 
        else if (inst.op == "USE") {
            int s_idx = get_or_create_slot(inst.arg1);
            if (slots[s_idx].held_ref == -1) {
                null_usage_counter++;
                std::cout << "NUL " << inst.index << " " << inst.arg1 << "\n";
            }
        }
    }

    for (auto it = appearance_order.rbegin(); it != appearance_order.rend(); ++it) {
        int s_idx = locate_slot(*it);
        if (s_idx != -1 && slots[s_idx].held_ref != -1) {
            termination_sequence.push_back(slots[s_idx].held_ref);
            destruction_counter++;
            slots[s_idx].held_ref = -1;
        }
    }

    for (int target_obj : termination_sequence) {
        std::cout << "DETRUIT " << target_obj << "\n";
    }

    std::cout << "CREES " << object_counter << "\n";
    std::cout << "DETRUITS " << destruction_counter << "\n";
    std::cout << "NULS " << null_usage_counter << "\n";

    return 0;
}