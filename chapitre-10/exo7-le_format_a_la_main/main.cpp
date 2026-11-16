#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include <cstring>
#include <iomanip>
#include <cmath>

class BinaryStreamParser {
private:
    std::vector<uint8_t> buffer;
    std::size_t offset = 0;

public:
    explicit BinaryStreamParser(std::vector<uint8_t> data) : buffer(std::move(data)) {}

    bool read_byte(uint8_t& out) {
        if (offset + 1 > buffer.size()) return false;
        out = buffer[offset++];
        return true;
    }

    bool read_word32(uint32_t& out) {
        if (offset + 4 > buffer.size()) return false;
        out = static_cast<uint32_t>(buffer[offset]) |
              (static_cast<uint32_t>(buffer[offset + 1]) << 8) |
              (static_cast<uint32_t>(buffer[offset + 2]) << 16) |
              (static_cast<uint32_t>(buffer[offset + 3]) << 24);
        offset += 4;
        return true;
    }

    bool read_float32(float& out) {
        uint32_t raw_bits;
        if (!read_word32(raw_bits)) return false;
        std::memcpy(&out, &raw_bits, sizeof(float));
        return true;
    }

    bool skip_bytes(std::size_t count) {
        if (count > buffer.size() - offset) return false;
        offset += count;
        return true;
    }
};

void print_formatted_float(float val) {
    double rounded = std::round(static_cast<double>(val) * 100.0) / 100.0;
    if (std::abs(rounded) < 0.005) {
        rounded = 0.0;
    }
    std::cout << std::fixed << std::setprecision(2) << rounded;
}

struct CanvasItem {
    float pos_x, pos_y, sc_factor, rot_angle, alpha_val;
    uint8_t mirror_h, mirror_v;
    uint32_t px_width, px_height, payload_bytes;
};

struct VectorPoint {
    float x_coord, y_coord;
};

struct VectorPath {
    uint8_t red, green, blue, alpha;
    float stroke_width;
    std::vector<VectorPoint> pts;
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::size_t total_size;
    if (!(std::cin >> total_size)) return 0;

    std::vector<uint8_t> raw_stream;
    raw_stream.reserve(total_size);

    for (std::size_t i = 0; i < total_size; ++i) {
        std::string hex_token;
        if (!(std::cin >> hex_token)) {
            std::cout << "TRONQUE\n";
            return 0;
        }
        try {
            unsigned int parsed_val = std::stoul(hex_token, nullptr, 16);
            raw_stream.push_back(static_cast<uint8_t>(parsed_val));
        } catch (...) {
            std::cout << "TRONQUE\n";
            return 0;
        }
    }

    if (raw_stream.size() < 4) {
        std::cout << "TRONQUE\n";
        return 0;
    }

    if (raw_stream[0] != 0x4E || raw_stream[1] != 0x4B ||
        raw_stream[2] != 0x52 || raw_stream[3] != 0x46) {
        std::cout << "PAS_UNE_PLANCHE\n";
        return 0;
    }

    BinaryStreamParser engine(raw_stream);
    uint8_t dummy_byte;
    for (int i = 0; i < 4; ++i) engine.read_byte(dummy_byte);

    uint32_t file_version;
    if (!engine.read_word32(file_version)) {
        std::cout << "TRONQUE\n";
        return 0;
    }

    if (file_version != 1) {
        std::cout << "VERSION_INCONNUE " << file_version << "\n";
        return 0;
    }

    float cam_cx, cam_cy, cam_zoom;
    if (!engine.read_float32(cam_cx) || !engine.read_float32(cam_cy) || !engine.read_float32(cam_zoom)) {
        std::cout << "TRONQUE\n";
        return 0;
    }

    uint8_t theme_mode, grid_mode;
    if (!engine.read_byte(theme_mode) || !engine.read_byte(grid_mode) ||
        !engine.read_byte(dummy_byte) || !engine.read_byte(dummy_byte)) {
        std::cout << "TRONQUE\n";
        return 0;
    }

    uint32_t image_count;
    if (!engine.read_word32(image_count)) {
        std::cout << "TRONQUE\n";
        return 0;
    }

    std::vector<CanvasItem> items_collection;
    for (uint32_t i = 0; i < image_count; ++i) {
        CanvasItem item;
        if (!engine.read_float32(item.pos_x) || !engine.read_float32(item.pos_y) ||
            !engine.read_float32(item.sc_factor) || !engine.read_float32(item.rot_angle) ||
            !engine.read_float32(item.alpha_val) || !engine.read_byte(item.mirror_h) ||
            !engine.read_byte(item.mirror_v) || !engine.read_byte(dummy_byte) ||
            !engine.read_byte(dummy_byte) || !engine.read_word32(item.px_width) ||
            !engine.read_word32(item.px_height) || !engine.read_word32(item.payload_bytes)) {
            std::cout << "TRONQUE\n";
            return 0;
        }

        if (!engine.skip_bytes(item.payload_bytes)) {
            std::cout << "TRONQUE\n";
            return 0;
        }
        items_collection.push_back(item);
    }

    uint32_t path_count;
    if (!engine.read_word32(path_count)) {
        std::cout << "TRONQUE\n";
        return 0;
    }

    std::vector<VectorPath> paths_collection;
    for (uint32_t i = 0; i < path_count; ++i) {
        VectorPath path_obj;
        uint32_t pt_total;
        if (!engine.read_byte(path_obj.red) || !engine.read_byte(path_obj.green) ||
            !engine.read_byte(path_obj.blue) || !engine.read_byte(path_obj.alpha) ||
            !engine.read_float32(path_obj.stroke_width) || !engine.read_word32(pt_total)) {
            std::cout << "TRONQUE\n";
            return 0;
        }

        for (uint32_t p = 0; p < pt_total; ++p) {
            VectorPoint pt;
            if (!engine.read_float32(pt.x_coord) || !engine.read_float32(pt.y_coord)) {
                std::cout << "TRONQUE\n";
                return 0;
            }
            path_obj.pts.push_back(pt);
        }
        paths_collection.push_back(path_obj);
    }

    std::cout << "VUE ";
    print_formatted_float(cam_cx);
    std::cout << " ";
    print_formatted_float(cam_cy);
    std::cout << " ";
    print_formatted_float(cam_zoom);
    std::cout << "\n";

    std::cout << "THEME " << (theme_mode != 0 ? "SOMBRE" : "CLAIR") << "\n";
    std::cout << "GRILLE " << (grid_mode == 0 ? "AFFICHEE" : "CACHEE") << "\n";
    std::cout << "IMAGES " << image_count << "\n";

    for (std::size_t i = 0; i < items_collection.size(); ++i) {
        const auto& it = items_collection[i];
        std::cout << "IMAGE " << (i + 1) << " ";
        print_formatted_float(it.pos_x);
        std::cout << " ";
        print_formatted_float(it.pos_y);
        std::cout << " ";
        print_formatted_float(it.sc_factor);
        std::cout << " ";
        print_formatted_float(it.rot_angle);
        std::cout << " ";
        print_formatted_float(it.alpha_val);
        std::cout << " " << (it.mirror_h != 0 ? 1 : 0)
                  << " " << (it.mirror_v != 0 ? 1 : 0)
                  << " " << it.px_width
                  << " " << it.px_height
                  << " " << it.payload_bytes << "\n";
    }

    std::cout << "TRAITS " << path_count << "\n";

    for (std::size_t i = 0; i < paths_collection.size(); ++i) {
        const auto& path = paths_collection[i];
        std::cout << "TRAIT " << (i + 1)
                  << " " << static_cast<int>(path.red)
                  << " " << static_cast<int>(path.green)
                  << " " << static_cast<int>(path.blue)
                  << " " << static_cast<int>(path.alpha)
                  << " ";
        print_formatted_float(path.stroke_width);
        std::cout << " " << path.pts.size() << "\n";

        for (const auto& pt : path.pts) {
            std::cout << "POINT ";
            print_formatted_float(pt.x_coord);
            std::cout << " ";
            print_formatted_float(pt.y_coord);
            std::cout << "\n";
        }
    }

    return 0;
}