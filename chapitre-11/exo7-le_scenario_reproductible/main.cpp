#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <cstdlib>

struct Evenement
{
    int tour;
    int priorite;
    int ordre;
    std::string texte;
};

static bool estEntier(const std::string& s, long long& v)
{
    if (s.empty())
    {
        return false;
    }
    std::size_t i = 0;
    if (s[0] == '-' || s[0] == '+')
    {
        i = 1;
    }
    if (i >= s.size())
    {
        return false;
    }
    for (std::size_t j = i; j < s.size(); ++j)
    {
        if (s[j] < '0' || s[j] > '9')
        {
            return false;
        }
    }
    v = std::atoll(s.c_str());
    return true;
}

static std::vector<std::string> couper(const std::string& s, char sep)
{
    std::vector<std::string> out;
    std::size_t debut = 0;
    while (true)
    {
        std::size_t p = s.find(sep, debut);
        if (p == std::string::npos)
        {
            out.push_back(s.substr(debut));
            break;
        }
        out.push_back(s.substr(debut, p - debut));
        debut = p + 1;
    }
    return out;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<Evenement> evenements;
    std::vector<int> captures;
    int ignores = 0;
    long long sortie = 0;
    bool aSortie = false;
    int ordreGlobal = 0;

    std::string ligne;
    while (std::getline(std::cin, ligne))
    {
        std::size_t eq = ligne.find('=');
        if (eq == std::string::npos)
        {
            ++ignores;
            continue;
        }
        std::string nom = ligne.substr(0, eq);
        std::string val = ligne.substr(eq + 1);

        if (nom == "NK_AGENT_SHOT")
        {
            for (const auto& item : couper(val, ','))
            {
                long long n;
                if (!estEntier(item, n) || captures.size() >= 8)
                {
                    ++ignores;
                }
                else
                {
                    captures.push_back(static_cast<int>(n));
                }
            }
        }
        else if (nom == "NK_AGENT_EXIT")
        {
            long long v;
            if (!estEntier(val, v))
            {
                ++ignores;
            }
            else
            {
                sortie = v;
                aSortie = true;
            }
        }
        else if (nom == "NK_AGENT_PAN" || nom == "NK_AGENT_MOVE"
              || nom == "NK_AGENT_ZOOM" || nom == "NK_AGENT_GRID")
        {
            auto champs = couper(val, ':');
            std::size_t mini = 3;
            if (nom == "NK_AGENT_ZOOM")
            {
                mini = 4;
            }
            if (nom == "NK_AGENT_GRID")
            {
                mini = 2;
            }
            long long n;
            if (champs.size() < mini || !estEntier(champs[0], n))
            {
                ++ignores;
                continue;
            }

            std::string corps;
            int prio = 0;
            std::string etiquette;

            if (nom == "NK_AGENT_PAN")
            {
                etiquette = "PAN";
                prio = 1;
                corps = " " + champs[1] + " " + champs[2];
            }
            else if (nom == "NK_AGENT_ZOOM")
            {
                etiquette = "ZOOM";
                prio = 2;
                corps = " " + champs[1] + " " + champs[2] + " " + champs[3];
            }
            else if (nom == "NK_AGENT_MOVE")
            {
                etiquette = "MOVE";
                prio = 5;
                corps = " " + champs[1] + " " + champs[2];
            }
            else
            {
                etiquette = "GRILLE";
                prio = 7;
                corps = " " + champs[1];
            }

            evenements.push_back({static_cast<int>(n), prio, ordreGlobal++,
                                  etiquette + corps});
        }
        else if (nom == "NK_AGENT_PACK")
        {
            long long n;
            if (!estEntier(val, n))
            {
                ++ignores;
                continue;
            }
            evenements.push_back({static_cast<int>(n), 6, ordreGlobal++, "RANGE"});
        }
        else if (nom == "NK_AGENT_DROP" || nom == "NK_AGENT_CLICK")
        {
            int gardes = 0;
            for (const auto& item : couper(val, ';'))
            {
                if (gardes >= 8)
                {
                    ++ignores;
                    continue;
                }

                if (nom == "NK_AGENT_DROP")
                {
                    std::size_t p1 = item.find(':');
                    if (p1 == std::string::npos)
                    {
                        ++ignores;
                        continue;
                    }
                    std::size_t p2 = item.find(':', p1 + 1);
                    if (p2 == std::string::npos)
                    {
                        ++ignores;
                        continue;
                    }
                    std::size_t p3 = item.find(':', p2 + 1);
                    if (p3 == std::string::npos)
                    {
                        ++ignores;
                        continue;
                    }

                    long long n;
                    if (!estEntier(item.substr(0, p1), n))
                    {
                        ++ignores;
                        continue;
                    }

                    std::string chemin = item.substr(p3 + 1);
                    if (chemin.empty())
                    {
                        ++ignores;
                        continue;
                    }

                    std::string px = item.substr(p1 + 1, p2 - p1 - 1);
                    std::string py = item.substr(p2 + 1, p3 - p2 - 1);

                    evenements.push_back({static_cast<int>(n), 3, ordreGlobal++,
                                          "DEPOT " + chemin + " " + px + " " + py});
                    ++gardes;
                }
                else
                {
                    auto champs = couper(item, ':');
                    long long n;
                    if (champs.size() < 3 || !estEntier(champs[0], n))
                    {
                        ++ignores;
                        continue;
                    }

                    evenements.push_back({static_cast<int>(n), 4, ordreGlobal++,
                                          "CLIC " + champs[1] + " " + champs[2]});
                    ++gardes;
                }
            }
        }
        else
        {
            ++ignores;
        }
    }

    std::stable_sort(evenements.begin(), evenements.end(),
        [](const Evenement& a, const Evenement& b)
        {
            if (a.tour != b.tour) return a.tour < b.tour;
            if (a.priorite != b.priorite) return a.priorite < b.priorite;
            return a.ordre < b.ordre;
        });

    std::vector<char> fait(evenements.size(), 0);
    std::vector<char> captureFaite(captures.size(), 0);

    int tourMax = 0;
    for (const auto& e : evenements)
    {
        if (e.tour > tourMax) tourMax = e.tour;
    }
    for (int n : captures)
    {
        if (n > 0 && n - 1 > tourMax) tourMax = n - 1;
    }

    bool arret = aSortie && sortie > 0;
    if (arret && static_cast<long long>(tourMax) < sortie - 1)
    {
        tourMax = static_cast<int>(sortie - 1);
    }
    if (arret)
    {
        tourMax = std::min(tourMax, static_cast<int>(sortie - 1));
    }

    int dernier = 0;

    for (int t = 0; t <= tourMax; ++t)
    {
        dernier = t;

        std::size_t i = 0;
        while (i < evenements.size())
        {
            if (evenements[i].tour == t && evenements[i].tour > 0)
            {
                std::size_t j = i;
                while (j < evenements.size()
                    && evenements[j].tour == t
                    && evenements[j].priorite == evenements[i].priorite)
                {
                    fait[j] = 1;
                    std::cout << "TOUR " << t << " " << evenements[j].texte << '\n';
                    ++j;
                }
                i = j;
            }
            else
            {
                ++i;
            }
        }

        for (std::size_t c = 0; c < captures.size(); ++c)
        {
            if (!captureFaite[c] && captures[c] == t + 1 && captures[c] > 0)
            {
                captureFaite[c] = 1;
                std::cout << "TOUR " << t << " CAPTURE\n";
            }
        }

        if (arret && t + 1 >= sortie)
        {
            break;
        }
    }

    int jamais = 0;
    for (std::size_t k = 0; k < evenements.size(); ++k)
    {
        if (!fait[k]) ++jamais;
    }
    for (std::size_t c = 0; c < captures.size(); ++c)
    {
        if (!captureFaite[c]) ++jamais;
    }

    if (arret)
    {
        std::cout << "ARRET " << dernier << '\n';
    }
    else
    {
        std::cout << "SANS_ARRET\n";
    }
    std::cout << "JAMAIS " << jamais << '\n';
    std::cout << "IGNORES " << ignores << '\n';

    return 0;
}