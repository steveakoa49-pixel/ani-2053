#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>

struct CanvasViewport {
    double pos_x;
    double pos_y;
    double scale_factor;
};

double sanitize_zero(double val) {
    if (std::abs(val) < 0.005) {
        return 0.0;
    }
    return val;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    double screen_w, screen_h;
    if (!(std::cin >> screen_w >> screen_h)) {
        return 0;
    }

    CanvasViewport cam{0.0, 0.0, 1.0};
    std::string token;

    while (std::cin >> token) {
        if (token == "VERS_MONDE") {
            double px, py;
            std::cin >> px >> py;

            double world_x = cam.pos_x + (px - screen_w * 0.5) / cam.scale_factor;
            double world_y = cam.pos_y + (py - screen_h * 0.5) / cam.scale_factor;

            std::cout << std::fixed << std::setprecision(2);
            std::cout << "MONDE " << sanitize_zero(world_x) << " " << sanitize_zero(world_y) << "\n";
        }
        else if (token == "VERS_PIXEL") {
            double mx, my;
            std::cin >> mx >> my;

            double screen_px = (mx - cam.pos_x) * cam.scale_factor + screen_w * 0.5;
            double screen_py = (my - cam.pos_y) * cam.scale_factor + screen_h * 0.5;

            std::cout << std::fixed << std::setprecision(2);
            std::cout << "PIXEL " << sanitize_zero(screen_px) << " " << sanitize_zero(screen_py) << "\n";
        }
        else if (token == "DEPLACE") {
            double delta_x, delta_y;
            std::cin >> delta_x >> delta_y;

            cam.pos_x -= delta_x / cam.scale_factor;
            cam.pos_y -= delta_y / cam.scale_factor;
        }
        else if (token == "ZOOM") {
            double multiplier, px, py;
            std::cin >> multiplier >> px >> py;

            double anchor_x = cam.pos_x + (px - screen_w * 0.5) / cam.scale_factor;
            double anchor_y = cam.pos_y + (py - screen_h * 0.5) / cam.scale_factor;

            cam.scale_factor *= multiplier;

            if (cam.scale_factor < 0.02) {
                cam.scale_factor = 0.02;
            }
            if (cam.scale_factor > 64.0) {
                cam.scale_factor = 64.0;
            }

            cam.pos_x = anchor_x - (px - screen_w * 0.5) / cam.scale_factor;
            cam.pos_y = anchor_y - (py - screen_h * 0.5) / cam.scale_factor;
        }
        else if (token == "GRILLE") {
            double threshold;
            std::cin >> threshold;

            double step = 1.0;
            while (step * cam.scale_factor < threshold) {
                step *= 2.0;
            }
            while (step * 0.5 * cam.scale_factor >= threshold) {
                step *= 0.5;
            }

            std::cout << std::fixed << std::setprecision(6);
            std::cout << "GRILLE " << step << "\n";
        }
        else if (token == "ORIGINE") {
            cam.pos_x = 0.0;
            cam.pos_y = 0.0;
            cam.scale_factor = 1.0;
        }
    }

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "CENTRE " << sanitize_zero(cam.pos_x) << " " << sanitize_zero(cam.pos_y) << "\n";
    std::cout << "ZOOM " << cam.scale_factor << "\n";

    return 0;
}