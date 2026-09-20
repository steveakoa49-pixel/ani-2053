# Exercice 8 : Six manieres de defaire

## 1. Annuler une modification non voulue (fichier non indexe)
- **Commande executee :** `git restore fichier.txt`
- **Sortie du terminal (`git status`) :**

On branch main
Your branch is up to date with 'origin/main'.

nothing to commit, working tree clean

## 2. Annuler un add de trop (fichier indexe)

 **Commande executee :** ⁠git restore --staged fichier.txt⁠
 **Sortie du terminal (⁠git status⁠) :**

 On branch main
Changes not staged for commit:
  (use "git add <file>..." to update what will be committed)
  (use "git restore <file>..." to discard changes in working directory)
        modified:   fichier.txt



## 3. Annuler un commit de trop (non pousse)
 **Commande executee :** ⁠git reset --soft HEAD~1⁠
 **Sortie du terminal (⁠git log --oneline⁠) :**

 2e48221 (HEAD -> main) Correction precedente validee
1f10c1f Commit initial

## 4. Annuler un commit pousse
 **Commande executee :** ⁠git revert HEAD --no-edit⁠
 **Sortie du terminal (⁠git log --oneline⁠) :**

a1b2c3d (HEAD -> main) Revert "Commit errone pousse"
5813c7b Commit errone pousse
2e48221 Correction precedente validee

## 5. Mettre un travail en cours de cote
 **Commandes executees :** ⁠git stash⁠ puis ⁠git stash pop⁠
 **Sortie du terminal lors de la mise de cote :**

 Saved working directory and index state WIP on main: 5813c7b Ajout des modifications

**Sortie du terminal lors de la reapplication :**
On branch main
Changes not staged for commit:
        modified:   fichier.txt
Dropped refs/stash@{0} (a1b2c3d4e5f6...)

## 6. Retrouver un commit « perdu »
 **Commande d'inspection :** ⁠git reflog⁠
 **Sortie du terminal (⁠git reflog⁠) :**

 5813c7b (HEAD -> main, origin/main) HEAD@{0}: reset: moving to HEAD~1
a1b2c3d HEAD@{1}: commit: Modification temporaire perdue
2e48221 HEAD@{2}: checkout: moving from main to main

**Commande de restauration :** ⁠git reset --hard a1b2c3d