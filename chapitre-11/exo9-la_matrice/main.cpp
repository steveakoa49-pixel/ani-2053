#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <tuple>

struct Fiche
{
    std::string nom;
    int force;
    int poids;
    std::string source;
    std::string nature;
    std::string cible;
    int rang;
    bool retenue;
    std::string motif;
};

static int rangSource(const std::string& s)
{
    if (s == "MESUREE") return 0;
    if (s == "OBSERVEE") return 1;
    return 2;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<Fiche> fiches;
    fiches.reserve(static_cast<std::size_t>(n));
    std::unordered_map<std::string, std::size_t> position;
    position.reserve(static_cast<std::size_t>(n) * 2 + 1);

    for (int i = 0; i < n; ++i)
    {
        Fiche f;
        std::cin >> f.nom >> f.force >> f.poids >> f.source >> f.nature;
        f.cible.clear();
        if (f.nature == "SOCLE")
        {
            std::cin >> f.cible;
        }
        f.rang = i;
        f.retenue = true;
        f.motif.clear();

        if (f.nature == "REECRITURE")
        {
            f.retenue = false;
            f.motif = "reecriture";
        }
        else if (f.nature == "CHOIX")
        {
            f.retenue = false;
            f.motif = "choix";
        }
        else if (f.source == "-")
        {
            f.retenue = false;
            f.motif = "sans_etiquette";
        }

        position[f.nom] = fiches.size();
        fiches.push_back(f);
    }

    for (Fiche& f : fiches)
    {
        if (!f.retenue || f.nature != "SOCLE")
        {
            continue;
        }
        auto it = position.find(f.cible);
        if (it == position.end())
        {
            continue;
        }
        const Fiche& c = fiches[it->second];
        if (c.nature == "MANQUE" && c.retenue)
        {
            if (c.force > f.force)
            {
                f.force = c.force;
            }
        }
    }

    static const char* etiquettesCase[4] = {
        "EN_PASSANT", "DECOUPER", "MAINTENANT", "ON_NE_LE_FAIT_PAS"
    };

    // index = (valeur>=3)<<1 | (cout>=3)
    // 00 -> EN_PASSANT, 01 -> DECOUPER, 10 -> MAINTENANT, 11 -> ON_NE_LE_FAIT_PAS
    static const int indexCase[4] = { 0, 2, 1, 3 };

    std::vector<const Fiche*> retenues;
    retenues.reserve(fiches.size());

    for (const Fiche& f : fiches)
    {
        if (f.retenue)
        {
            retenues.push_back(&f);
        }
    }

    auto cleTri = [](const Fiche* f) -> std::tuple<int, int, int, int, int>
    {
        int idx = ((f->force >= 3) ? 2 : 0) | ((f->poids >= 3) ? 1 : 0);
        int ordreCase = indexCase[idx];
        return std::make_tuple(ordreCase, rangSource(f->source),
                               -f->force, f->poids, f->rang);
    };

    std::sort(retenues.begin(), retenues.end(),
        [&](const Fiche* a, const Fiche* b)
        {
            return cleTri(a) < cleTri(b);
        });

    bool refus = false;

    for (const Fiche* f : retenues)
    {
        int idx = ((f->force >= 3) ? 2 : 0) | ((f->poids >= 3) ? 1 : 0);
        const char* nomCase = etiquettesCase[indexCase[idx]];

        std::cout << nomCase << ' ' << f->nom << ' ' << f->source << '\n';

        if (std::string(nomCase) == "ON_NE_LE_FAIT_PAS")
        {
            refus = true;
        }
    }

    for (const Fiche& f : fiches)
    {
        if (!f.retenue)
        {
            std::cout << "HORS_LISTE " << f.nom << ' ' << f.motif << '\n';
        }
    }

    std::cout << "VERDICT " << (refus ? "HONNETE" : "COMPLAISANT") << '\n';

    return 0;
}