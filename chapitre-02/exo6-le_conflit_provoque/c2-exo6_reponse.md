# Exercice 6 : Le conflit provoqué

## 1. Message lors du refus de push (non-fast-forward)

To [https://github.com/steveakoa49-pixel/ani-2053.git](https://github.com/steveakoa49-pixel/ani-2053.git)
 ! [rejected]        main -> main (fetch first)
error: failed to push some refs to '[https://github.com/steveakoa49-pixel/ani-2053.git](https://github.com/steveakoa49-pixel/ani-2053.git)'
hint: Updates were rejected because the remote contains work that you do not
hint: have locally. This is usually caused by another repository pushing to
hint: the same ref. If you want to integrate the remote changes, use
hint: 'git pull' before pushing again.
hint: See the 'Note about fast-forwards' in 'git push --help' for details.

## 2. Message lors du conflit de fusion (git pull)

Auto-merging chapitre-02/exo6-le_conflit_provoque/conflit.txt
CONFLICT (content): Merge conflict in chapitre-02/exo6-le_conflit_provoque/conflit.txt
Automatic merge failed; fix conflicts and then commit the result.

## 3. Explication de la résolution

Le conflit est survenu car la même ligne du fichier ⁠conflit.txt⁠ a été modifiée différemment sur le dépôt distant (clone B) et en local (dépôt A).
Après le refus du push, l'exécution de ⁠git pull⁠ a généré un conflit de fusion. Le fichier a été ouvert dans VS Code pour choisir la version finale à conserver et retirer les marqueurs de conflit (⁠<<<<<<<⁠, ⁠=======⁠, ⁠>>>>>>>⁠).
La résolution a été validée à l'aide de ⁠git add⁠ puis ⁠git commit⁠.
