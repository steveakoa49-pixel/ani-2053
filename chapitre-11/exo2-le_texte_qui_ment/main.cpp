#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int nbCommits;
    std::cin >> nbCommits;

    std::vector<std::string> commits(nbCommits);
    std::unordered_map<std::string, int> posCommit;
    posCommit.reserve(nbCommits * 2);

    std::unordered_map<std::string, std::vector<char>> presence;
    presence.reserve(64);

    std::unordered_map<std::string, char> courant;

    for (int i = 0; i < nbCommits; ++i)
    {
        std::string h, act;
        int k;
        std::cin >> h >> act >> k;
        commits[i] = h;
        posCommit[h] = i;

        bool ajout = (act[0] == 'A');

        for (int j = 0; j < k; ++j)
        {
            std::string f;
            std::cin >> f;
            if (ajout)
            {
                courant[f] = 1;
            }
            else
            {
                courant.erase(f);
            }
        }

        for (auto& kv : courant)
        {
            auto& vec = presence[kv.first];
            if (vec.empty())
            {
                vec.assign(nbCommits, 0);
            }
            vec[i] = 1;
        }
    }

    int nbAnnonces;
    std::cin >> nbAnnonces;

    int mensonges = 0;

    for (int idx = 1; idx <= nbAnnonces; ++idx)
    {
        std::string h, etat, f;
        std::cin >> h >> etat >> f;

        int depart = posCommit[h];
        bool veutPresent = (etat[0] == 'D');

        auto it = presence.find(f);
        const std::vector<char>* vec = nullptr;
        if (it != presence.end())
        {
            vec = &it->second;
        }

        auto existeA = [&](int c) -> bool
        {
            return vec != nullptr && (*vec)[c] != 0;
        };

        auto mentA = [&](int c) -> bool
        {
            if (veutPresent)
            {
                return !existeA(c);
            }
            return existeA(c);
        };

        if (!mentA(nbCommits - 1))
        {
            std::cout << "ANNONCE " << idx << " VRAI\n";
            continue;
        }

        int depuis = nbCommits - 1;
        while (depuis > depart && mentA(depuis - 1))
        {
            --depuis;
        }

        std::cout << "ANNONCE " << idx << " MENT " << commits[depuis] << "\n";
        ++mensonges;
    }

    std::cout << "MENSONGES " << mensonges << "\n";
    return 0;
}