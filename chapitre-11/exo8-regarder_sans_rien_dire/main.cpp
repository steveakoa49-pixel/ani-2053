#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

struct Stats
{
    int occurrences = 0;
    int premiere = 0;
    int ordreEntree = 0;
    bool cite = false;
};

static int lireTemps(const std::string& t)
{
    int mm = (t[0] - '0') * 10 + (t[1] - '0');
    int ss = (t[3] - '0') * 10 + (t[4] - '0');
    return mm * 60 + ss;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::string motCle;
    std::cin >> motCle >> n;

    std::unordered_map<std::string, Stats> parNom;
    parNom.reserve(static_cast<std::size_t>(n) * 2 + 1);

    int horsSeance = 0;

    for (int i = 0; i < n; ++i)
    {
        std::string temps, nom;
        std::cin >> temps >> nom;

        int sec = lireTemps(temps);

        if (sec > 1200)
        {
            ++horsSeance;
            continue;
        }

        auto it = parNom.find(nom);
        if (it == parNom.end())
        {
            Stats s;
            s.occurrences = 1;
            s.premiere = sec;
            s.ordreEntree = i;
            parNom.emplace(nom, s);
        }
        else
        {
            ++it->second.occurrences;
            if (sec < it->second.premiere)
            {
                it->second.premiere = sec;
            }
        }
    }

    int m;
    std::cin >> motCle >> m;

    std::vector<std::string> cites;
    cites.reserve(static_cast<std::size_t>(m));
    std::unordered_set<std::string> setCites;
    setCites.reserve(static_cast<std::size_t>(m) * 2 + 1);

    for (int i = 0; i < m; ++i)
    {
        std::string nom;
        std::cin >> nom;
        cites.push_back(nom);
        setCites.insert(nom);
    }

    for (auto& kv : parNom)
    {
        if (setCites.find(kv.first) != setCites.end())
        {
            kv.second.cite = true;
        }
    }

    std::vector<std::pair<std::string, Stats>> liste;
    liste.reserve(parNom.size());
    for (auto& kv : parNom)
    {
        liste.push_back(kv);
    }

    std::sort(liste.begin(), liste.end(),
        [](const std::pair<std::string, Stats>& a,
           const std::pair<std::string, Stats>& b)
        {
            if (a.second.occurrences != b.second.occurrences)
            {
                return a.second.occurrences > b.second.occurrences;
            }
            if (a.second.premiere != b.second.premiere)
            {
                return a.second.premiere < b.second.premiere;
            }
            return a.second.ordreEntree < b.second.ordreEntree;
        });

    int nonDits = 0;
    int totalOccurrences = 0;
    int totalNonDit = 0;

    for (const auto& item : liste)
    {
        const std::string& nom = item.first;
        const Stats& s = item.second;

        std::cout << nom << ' ' << s.occurrences << ' '
                  << (s.cite ? "DIT" : "NON_DIT") << '\n';

        totalOccurrences += s.occurrences;
        if (!s.cite)
        {
            ++nonDits;
            totalNonDit += s.occurrences;
        }
    }

    int partNonDite = 0;
    if (totalOccurrences > 0)
    {
        partNonDite = (100 * totalNonDit) / totalOccurrences;
    }

    std::cout << "NON_DITS " << nonDits << '\n';
    std::cout << "PART_NON_DITE " << partNonDite << '\n';

    std::vector<std::string> ditSansVu;
    for (const std::string& nom : cites)
    {
        if (parNom.find(nom) == parNom.end())
        {
            ditSansVu.push_back(nom);
        }
    }

    std::cout << "DIT_SANS_VU";
    if (ditSansVu.empty())
    {
        std::cout << " AUCUN";
    }
    else
    {
        for (const std::string& nom : ditSansVu)
        {
            std::cout << ' ' << nom;
        }
    }
    std::cout << '\n';
    std::cout << "HORS_SEANCE " << horsSeance << '\n';

    return 0;
}