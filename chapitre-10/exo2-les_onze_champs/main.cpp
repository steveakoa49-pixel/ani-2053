#include <iostream>
#include <string>

struct ImgRecord {
    int identifier;
    double pos_x;
    double pos_y;
    double scale;
    double angle;
    double alpha;
    int flip_x;
    int flip_y;
    int width;
    int height;
    int is_picked;
    std::string source_uri;
    unsigned long long byte_size;
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int count;
    if (!(std::cin >> count)) {
        return 0;
    }

    int reloaded_total = 0;
    int modified_fields_total = 0;

    for (int idx = 1; idx <= count; ++idx) {
        ImgRecord item;
        std::cin >> item.identifier
                 >> item.pos_x >> item.pos_y
                 >> item.scale
                 >> item.angle
                 >> item.alpha
                 >> item.flip_x >> item.flip_y
                 >> item.width >> item.height
                 >> item.is_picked
                 >> item.source_uri
                 >> item.byte_size;

        if (item.byte_size == 0) {
            std::cout << "ITEM " << idx << " SAUTE\n";
            continue;
        }

        reloaded_total++;
        std::cout << "ITEM " << idx << " " << reloaded_total;

        int local_changes = 0;

        if (item.identifier != 0) {
            std::cout << " id";
            local_changes++;
        }

        if (item.is_picked == 1) {
            std::cout << " selected";
            local_changes++;
        }

        if (item.source_uri != "-") {
            std::cout << " sourcePath";
            local_changes++;
        }

        if (local_changes == 0) {
            std::cout << " AUCUN";
        }

        std::cout << "\n";
        modified_fields_total += local_changes;
    }

    std::cout << "RESTENT " << reloaded_total << "\n";
    std::cout << "CHANGES " << modified_fields_total << "\n";

    return 0;
}