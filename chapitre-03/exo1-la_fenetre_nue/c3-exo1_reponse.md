# Exercice 1 : La fenêtre nue


** 1. Code source**

Le code complet du programme permettant d'ouvrir la fenêtre :
```cpp
#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"

using namespace nkentseu;

int nkmain(const NkEntryState &state) {
    NkWindowConfig cfg;
    cfg.title = "Ma fenetre";
    cfg.width = 1280;
    cfg.height = 720;

    NkWindow window(cfg);
    if (!window.IsOpen()) {
        logger.Error("[app] creation fenetre echouee");
        return -1;
    }
    while (window.IsOpen()) { /* les evenements arrivent ici */ }
    return 0;
}

**2. Relevé ligne par ligne et justificatif**


Ligne 1 (#include "NKWindow/NKWindow.h") : Inclus le module principal de gestion des fenêtres présenté dans la section "Le plus petit programme".

Ligne 2 (#include "NKWindow/NKMain.h") : Indispensable selon la section "Le plus petit programme". Le cours indique que ce fichier fournit le point d'entrée natif propre à chaque système (WinMain sur Windows, android_main sur Android, etc.). Son oubli provoque l'erreur classique d'édition de liens undefined reference to WinMain.

Ligne 4 (int nkmain(const NkEntryState &state)) : Définit le point d'entrée de l'application. La section "Le plus petit programme" précise bien : "Vous n'écrivez pas de main. Vous écrivez nkmain".

Lignes 5 à 8 (NkWindowConfig cfg; ...) : Préparent la structure de configuration. Le cours explique que "La configuration se donne au constructeur" et détaille dans la partie "Configurer et piloter la fenêtre" les paramètres de la famille Identité et taille (titre, largeur, hauteur).

Ligne 10 (NkWindow window(cfg);) : Instancie la fenêtre. Comme le note le texte, la fenêtre est réellement créée à cet instant précis en mémoire.

Lignes 11 à 14 (if (!window.IsOpen()) { ... }) : Traitent l'échec de création. Le cours insiste sur le fait qu me "Une création peut échouer — pilote absent, serveur graphique inaccessible, permissions. Un programme qui continue après cela travaille dans le vide".

Note sur le critère du "plus petit programme" : Ces 4 lignes constituent la garde d'erreur préconisée par le chapitre. Si l'on cherchait le programme le plus court au sens strict sans aucune gestion d'erreur, le code tiendrait sur 13 lignes, mais il ne respecterait pas cette bonne pratique énoncée.

Ligne 15 (while (window.IsOpen()) { ... }) : Maintient la boucle principale tant que la fenêtre reste active, là où "les événements arrivent".

Ligne 16 (return 0;) : Marque la fin normale de l'exécution du programme.


** 3. Analyse du comportement de la boucle while (window.IsOpen())**
En testant le programme et en observant le fonctionnement de la boucle while (window.IsOpen()) { }, on remarque un problème central :

Ce qui se passe : La boucle est vide. L'application n'interroge pas et ne vide pas la file d'événements envoyés par le système d'exploitation.

Conséquence lors de l'essai : Si l'on clique sur la croix de fermeture de la fenêtre, le système envoie bien un événement WINDOW de fermeture. Cependant, comme le programme ne dépile jamais cet événement, la méthode IsOpen() ne repasse jamais à false.

Résultat observé : La fenêtre reste bloquée à l'écran, gèle et finit par afficher le message du système "Ne répond pas".

Conclusion : Pour qu'une fenêtre puisse se fermer proprement suite à une action utilisateur, il ne suffit pas de vérifier IsOpen(), il faut impérativement lire la file d'événements à chaque tour de boucle (ce qui fait l'objet du chapitre 4).