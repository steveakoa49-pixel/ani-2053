#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

struct Groupe {
    std::string police;
    int n;
    long long w;
    long long h;
    long long x1, y1;
    long long x2, y2;
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    long long P = 0, L = 0;
    if (!(std::cin >> P >> L)) {
        return 0;
    }

    int G = 0;
    if (!(std::cin >> G)) {
        return 0;
    }

    if (G == 0) {
        std::cout << "AUCUN\n";
        return 0;
    }

    std::vector<Groupe> groupes(G);
    long long occupe = 0;
    long long besoin = 0;

    for (int i = 0; i < G; ++i) {
        std::cin >> groupes[i].police >> groupes[i].n >> groupes[i].w >> groupes[i].h;
        occupe += (long long)groupes[i].n * groupes[i].w * groupes[i].h;
        besoin += (long long)groupes[i].n * (groupes[i].w + P) * (groupes[i].h + P);
    }

    long long W = L;
    if (L == 0) {
        W = 512;
        while (W * W < 2 * besoin && W < 4096) {
            W *= 2;
        }
    }
    long long H = W;

    for (int essai = 1; essai <= 8; ++essai) {
        long long x = P;
        long long y = P;
        long long e = 0;
        bool echec = false;

        for (int i = 0; i < G; ++i) {
            long long rw = groupes[i].w + P;
            long long rh = groupes[i].h + P;

            for (int k = 0; k < groupes[i].n; ++k) {
                if (x + rw > W - P) {
                    x = P;
                    y = y + e + P;
                    e = 0;
                    if (x + rw > W - P) {
                        echec = true;
                        break;
                    }
                }

                if (y + rh > H - P) {
                    echec = true;
                    break;
                }

                if (k == 0) {
                    groupes[i].x1 = x;
                    groupes[i].y1 = y;
                }
                if (k == groupes[i].n - 1) {
                    groupes[i].x2 = x;
                    groupes[i].y2 = y;
                }

                x += rw;
                e = std::max(e, rh);
            }

            if (echec) {
                break;
            }
        }

        if (!echec) {
            long long surfaceTotale = W * H;
            long long perdu = ((surfaceTotale - occupe) * 100) / surfaceTotale;

            std::cout << "ESSAIS " << essai << "\n";
            std::cout << "TEXTURE " << W << " " << H << "\n";
            for (int i = 0; i < G; ++i) {
                std::cout << groupes[i].police << " " << groupes[i].x1 << " " << groupes[i].y1 << " " << groupes[i].x2 << " " << groupes[i].y2 << "\n";
            }
            std::cout << "OCCUPE " << occupe << "\n";
            std::cout << "PERDU " << perdu << "\n";
            return 0;
        }

        if (W == H) {
            W *= 2;
        } else {
            H = W;
        }
    }

    std::cout << "ESSAIS 8\n";
    std::cout << "ECHEC\n";

    return 0;
}