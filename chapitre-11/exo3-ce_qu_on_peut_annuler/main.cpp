#include <iostream>
#include <vector>
#include <string>
#include <cstdio>

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<std::string> attentes;
    attentes.reserve(1024);
    std::size_t sommetAttentes = 0;

    std::vector<int> traits;
    traits.reserve(1024);
    std::size_t sommetTraits = 0;

    int prochainTrait = 1;
    int totalOperations = 0;
    int totalTraits = 0;

    int nbJustes = 0;
    int nbRiens = 0;
    int nbTrahis = 0;
    int nbAnnules = 0;

    char buffer[64];

    std::string op;
    while (std::cin >> op)
    {
        char c = op[0];

        if (c == 'A')
        {
            ++nbAnnules;

            std::string attendu;
            if (sommetAttentes == 0)
            {
                attendu = "AUCUNE";
            }
            else
            {
                --sommetAttentes;
                attendu = attentes[sommetAttentes];
            }

            std::string obtenu;
            if (sommetTraits == 0)
            {
                obtenu = "RIEN";
            }
            else
            {
                --sommetTraits;
                std::snprintf(buffer, sizeof(buffer), "TRAIT %d", traits[sommetTraits]);
                obtenu = buffer;
            }

            const char* verdict;
            if (obtenu == attendu || (attendu == "AUCUNE" && obtenu == "RIEN"))
            {
                verdict = "JUSTE";
                ++nbJustes;
            }
            else if (obtenu == "RIEN")
            {
                verdict = "RIEN";
                ++nbRiens;
            }
            else
            {
                verdict = "TRAHI";
                ++nbTrahis;
            }

            std::cout << "ANNULE " << nbAnnules
                      << " ATTENDU " << attendu
                      << " OBTENU " << obtenu
                      << ' ' << verdict << '\n';
        }
        else if (c == 'T')
        {
            ++totalOperations;
            ++totalTraits;

            std::snprintf(buffer, sizeof(buffer), "TRAIT %d", prochainTrait);
            if (sommetAttentes < attentes.size())
            {
                attentes[sommetAttentes] = buffer;
            }
            else
            {
                attentes.push_back(buffer);
            }
            ++sommetAttentes;

            if (sommetTraits < traits.size())
            {
                traits[sommetTraits] = prochainTrait;
            }
            else
            {
                traits.push_back(prochainTrait);
            }
            ++sommetTraits;

            ++prochainTrait;
        }
        else if (c == 'E')
        {
            ++totalOperations;

            if (sommetAttentes < attentes.size())
            {
                attentes[sommetAttentes] = "EFFACE";
            }
            else
            {
                attentes.push_back("EFFACE");
            }
            ++sommetAttentes;

            sommetTraits = 0;
        }
        else if (c == 'R')
        {
            ++totalOperations;

            if (sommetAttentes < attentes.size())
            {
                attentes[sommetAttentes] = "RANGE";
            }
            else
            {
                attentes.push_back("RANGE");
            }
            ++sommetAttentes;
        }
        else
        {
            std::string nom;
            std::cin >> nom;

            ++totalOperations;

            std::string cle = op + ' ' + nom;
            if (sommetAttentes < attentes.size())
            {
                attentes[sommetAttentes] = cle;
            }
            else
            {
                attentes.push_back(cle);
            }
            ++sommetAttentes;
        }
    }

    std::cout << "JUSTES " << nbJustes << '\n';
    std::cout << "RIENS " << nbRiens << '\n';
    std::cout << "TRAHIS " << nbTrahis << '\n';
    std::cout << "ANNULABLES " << totalTraits << " SUR " << totalOperations << '\n';

    return 0;
}