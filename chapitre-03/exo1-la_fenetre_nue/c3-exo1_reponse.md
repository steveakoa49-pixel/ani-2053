Le programme contient 17 lignes de code.

Explication ligne par ligne :
 Ligne 1 : Inclus le module de gestion de la fenêtre `NKWindow`.
 Ligne 2 : Inclus le wrapper `NKMain` qui gère le point d'entrée natif selon la plateforme (ex: WinMain, android_main).
 Ligne 3 : Ligne vide.
 Ligne 4 : Déclaratif de la fonction principale `nkmain` recevant l'état d'entrée `state`.
 Ligne 5 : Déclaratif d'une structure de configuration de fenêtre `cfg`.
 Ligne 6 : Définit le titre de la fenêtre ("Ma fenetre").
 Ligne 7 : Définit la largeur de la fenêtre à 1280 pixels.
 Ligne 8 : Définit la hauteur de la fenêtre à 720 pixels.
 Ligne 9 : Ligne vide.
 Ligne 10 : Instancie et crée la fenêtre `window` en lui passant la configuration `cfg`.
 Ligne 11 : Vérifie si l'ouverture de la fenêtre a échoué via `!window.IsOpen()`.
 Ligne 12 : Enregistre un message d'erreur dans les logs en cas d'échec.
 Ligne 13 : Quitte le programme avec un code d'erreur `-1`.
 Ligne 14 : Fermeture de la condition `if`.
 Ligne 15 : Boucle principale `while(window.IsOpen())` qui maintient la fenêtre ouverte tant qu'elle n'est pas fermée.
 Ligne 16 : Retourne `0` pour indiquer que le programme s'est terminé correctement.
 Ligne 17 : Fermeture de la fonction `nkmain`.