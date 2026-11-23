#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>

using namespace std;

int main()
{
    int n, c, a;
    string entete;

    cin >> entete >> n;
    vector<string> avant(n);
    unordered_set<string> setAvant;
    setAvant.reserve(n * 2);
    for (int i = 0; i < n; i++)
    {
        cin >> avant[i];
        setAvant.insert(avant[i]);
    }

    cin >> entete >> c;
    unordered_set<string> corrige;
    corrige.reserve(c * 2);
    for (int i = 0; i < c; i++)
    {
        string cle;
        cin >> cle;
        corrige.insert(cle);
    }

    cin >> entete >> a;
    unordered_set<string> apres;
    apres.reserve(a * 2);
    vector<string> listeApres;
    listeApres.reserve(a);
    for (int i = 0; i < a; i++)
    {
        string cle;
        cin >> cle;
        apres.insert(cle);
        listeApres.push_back(cle);
    }

    int vraies = 0;
    int fausses = 0;
    int oubliees = 0;
    int nouvelles = 0;

    // NOUVELLES : clés de APRES absentes de AVANT
    for (const string& cle : listeApres)
    {
        if (setAvant.find(cle) == setAvant.end())
        {
            nouvelles++;
        }
    }

    // Classement des clés de AVANT, dans l'ordre, priorité corrige > apres > oubliee
    for (int i = 0; i < n; i++)
    {
        const string& cle = avant[i];

        if (corrige.find(cle) != corrige.end())
        {
            cout << i + 1 << " " << cle << " DEVENUE_FAUSSE\n";
            fausses++;
        }
        else if (apres.find(cle) != apres.end())
        {
            cout << i + 1 << " " << cle << " ENCORE_VRAIE\n";
            vraies++;
        }
        else
        {
            cout << i + 1 << " " << cle << " OUBLIEE\n";
            oubliees++;
        }
    }

    int partOubliee = 0;
    if (vraies + oubliees != 0)
    {
        partOubliee = (100 * oubliees) / (vraies + oubliees);
    }

    cout << "VRAIES " << vraies << "\n";
    cout << "FAUSSES " << fausses << "\n";
    cout << "OUBLIEES " << oubliees << "\n";
    cout << "NOUVELLES " << nouvelles << "\n";
    cout << "PART_OUBLIEE " << partOubliee << "\n";

    return 0;
}