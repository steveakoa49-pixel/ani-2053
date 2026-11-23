#include <iostream>
#include <string>
#include <cstdio>

static void ecrireTemps(char* dest, long long secondes)
{
    std::snprintf(dest, 32, "%lld:%02lld", secondes / 60, secondes % 60);
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string nomTache;
    long long minimum = 0;
    long long parJour = 0;
    long long debut = 0;
    long long nbGestes = 0;
    long long attente = 0;
    bool active = false;

    long long totalSecondes = 0;

    long long instant;
    std::string evt;

    char buf[32];

    while (std::cin >> instant >> evt)
    {
        char c = evt[0];

        if (c == 'D')
        {
            std::cin >> nomTache >> minimum >> parJour;
            debut = instant;
            nbGestes = 0;
            attente = 0;
            active = true;
        }
        else if (c == 'F')
        {
            std::string nomFin;
            std::cin >> nomFin;

            if (active)
            {
                long long duree = instant - debut;
                long long surplus = nbGestes - minimum;
                if (surplus < 0)
                {
                    surplus = 0;
                }

                long long secondesJour = (attente * parJour) / 1000;
                totalSecondes += secondesJour;

                ecrireTemps(buf, secondesJour);

                std::cout << nomTache
                          << " GESTES " << nbGestes
                          << " EN_TROP " << surplus
                          << " DUREE " << duree
                          << " ATTENTE " << attente
                          << " JOUR " << buf
                          << '\n';

                active = false;
            }
        }
        else if (!active)
        {
            // Hors de toute tâche : on ignore, mais il faut consommer
            // l'éventuel argument de ATTENTE.
            if (c == 'A')
            {
                long long ignoree;
                std::cin >> ignoree;
            }
            // TOUCHE x : consommer x
            else if (evt == "TOUCHE")
            {
                std::string touche;
                std::cin >> touche;
            }
        }
        else
        {
            if (c == 'A')
            {
                long long d;
                std::cin >> d;
                attente += d;
            }
            else
            {
                // CLIC, GLISSE, MOLETTE : aucun argument
                // TOUCHE : un argument à consommer
                if (evt == "TOUCHE")
                {
                    std::string touche;
                    std::cin >> touche;
                }
                ++nbGestes;
            }
        }
    }

    if (active)
    {
        std::cout << nomTache << " INACHEVEE\n";
    }

    ecrireTemps(buf, totalSecondes);
    std::cout << "TOTAL_JOUR " << buf << '\n';

    return 0;
}