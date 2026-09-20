# Exercice 8 : Six manières de défaire

## 1. Une modification non voulue (fichier non indexé)
### État avant
```text
[On branch main
Your branch is up to date with 'origin/main'.

nothing to commit, working tree clean]


**Commande executee :** echo "test" >> test_exo8.txt
**Sortie du terminal (git status) :**
```text
On branch main
Your branch is ahead of 'origin/main' by 1 commit.
  (use "git push" to publish your local commits)

Changes not staged for commit:
  (use "git add <file>..." to update what will be committed)
  (use "git restore <file>..." to discard changes in working directory)
        modified:   test_exo8.txt

no changes added to commit (use "git add" and/or "git commit -a")

## État après
**Commande executee :**  "Ligne initiale" > test_exo8.txt
git add test_exo8.txt
git commit -m "Ajout fichier de base exo 8"
**Sortie du terminal (git status) :**
```text
On branch main
Your branch is ahead of 'origin/main' by 1 commit.
  (use "git push" to publish your local commits)

nothing to commit, working tree clean

## 2. Un add de trop (fichier indexé)
## État avant
On branch main
Your branch is up to date with 'origin/main'.

nothing to commit, working tree clean

**Commande executee :**  git restore --staged test_exo8.txt
**Sortie du terminal (git status) :**
```text
On branch main
Your branch is up to date with 'origin/main'.

nothing to commit, working tree clean

## 3. Un commit de trop (non poussé)
## État avant

**Commande executee :** git log -n 2 --oneline
**Sortie du terminal :**
3aa673d (HEAD -> main, origin/main) Ajout du fichier de reponse exo 7
44efe0e Ajout fichier de base exo 8

**Commande executee :** git reset --soft HEAD~1
**Sortie du terminal (git log -n 2 --oneline ) :**
```text
44efe0e (HEAD -> main) Ajout fichier de base exo 8
e121650 Ajout du compte rendu exo 8 avec les sorties de terminal

## 4. Un commit poussé qu'il faut annuler
## État avant
**Commande executee :** git log -n 2 --oneline
**Sortie du terminal :**
44efe0e (HEAD -> main) Ajout fichier de base exo 8
e121650 Ajout du compte rendu exo 8 avec les sorties de terminal

**Commande executee :** git revert HEAD --no-edit
**Sortie du terminal :**
hint: commit your changes or stash them to proceed.
fatal: revert failed


**Sortie du terminal (git log -n 2 --oneline ) :**
```text
44efe0e (HEAD -> main) Ajout fichier de base exo 8
e121650 Ajout du compte rendu exo 8 avec les sorties de terminal

## 5. Un travail en cours à mettre de côté
## État avant
**Commande executee :** git status
**Sortie du terminal :**
Your branch is behind 'origin/main' by 1 commit, and can be fast-forwarded.
  (use "git pull" to update your local branch)

Changes to be committed:
  (use "git restore --staged <file>..." to unstage)
        modified:   ../exo7-le_conflit_qui_n_en_est_pas_un/c2-exo7_reponse.md

**Commande executee :** git stash et git stash pop 
**Sortie du terminal :**  
git stash : Saved working directory and index state WIP on main: 44efe0e Ajout fichier de base exo 8
git stash pop : (use "git pull" to update your local branch)

Changes not staged for commit:
  (use "git add <file>..." to update what will be committed)
  (use "git restore <file>..." to discard changes in working directory)
        modified:   ../exo7-le_conflit_qui_n_en_est_pas_un/c2-exo7_reponse.md

no changes added to commit (use "git add" and/or "git commit -a")

## État après
**Commande executee :** git status 
**Sortie du terminal :** 
Your branch is behind 'origin/main' by 1 commit, and can be fast-forwarded.
  (use "git pull" to update your local branch)

Changes not staged for commit:
  (use "git add <file>..." to update what will be committed)
  (use "git restore <file>..." to discard changes in working directory)
        modified:   ../exo7-le_conflit_qui_n_en_est_pas_un/c2-exo7_reponse.md

no changes added to commit (use "git add" and/or "git commit -a")

## 6. Preuve globale et historique des actions (git reflog)

**Commande executee :** git reflog
**Sortie du terminal :** 
```text
44efe0e (HEAD -> main) HEAD@{0}: reset: moving to HEAD
44efe0e (HEAD -> main) HEAD@{1}: reset: moving to HEAD~1
3aa673d (origin/main) HEAD@{2}: commit: Ajout du fichier de reponse exo 7
44efe0e (HEAD -> main) HEAD@{3}: commit: Ajout fichier de base exo 8
e121650 HEAD@{4}: commit: Ajout du compte rendu exo 8 avec les sorties de terminal
5813c7b HEAD@{5}: commit: Correction exo 7 : ajout des sorties de terminal
2e48221 HEAD@{6}: commit: Ajout du fichier de reponse exo 7
679bdfc HEAD@{7}: pull origin main: Merge made by the 'ort' strategy.
9bac9fa HEAD@{8}: commit: Modification du bas du fichier par depot A
a1553e2 HEAD@{9}: commit: Initialisation de fichier.txt avec plusieurs lignes
:
44efe0e (HEAD -> main) HEAD@{0}: reset: moving to HEAD
44efe0e (HEAD -> main) HEAD@{1}: reset: moving to HEAD~1
3aa673d (origin/main) HEAD@{2}: commit: Ajout du fichier de reponse exo 7
44efe0e (HEAD -> main) HEAD@{3}: commit: Ajout fichier de base exo 8
e121650 HEAD@{4}: commit: Ajout du compte rendu exo 8 avec les sorties de terminal
5813c7b HEAD@{5}: commit: Correction exo 7 : ajout des sorties de terminal
2e48221 HEAD@{6}: commit: Ajout du fichier de reponse exo 7
679bdfc HEAD@{7}: pull origin main: Merge made by the 'ort' strategy.
9bac9fa HEAD@{8}: commit: Modification du bas du fichier par depot A
a1553e2 HEAD@{9}: commit: Initialisation de fichier.txt avec plusieurs lignes
f10c1f4 HEAD@{10}: commit: Initialisation de fichier.txt avec plusieurs lignes
dc91b6f HEAD@{11}: commit: Ajout du fichier de reponse exo 6
:
44efe0e (HEAD -> main) HEAD@{0}: reset: moving to HEAD
44efe0e (HEAD -> main) HEAD@{1}: reset: moving to HEAD~1
3aa673d (origin/main) HEAD@{2}: commit: Ajout du fichier de reponse exo 7
44efe0e (HEAD -> main) HEAD@{3}: commit: Ajout fichier de base exo 8
e121650 HEAD@{4}: commit: Ajout du compte rendu exo 8 avec les sorties de terminal
5813c7b HEAD@{5}: commit: Correction exo 7 : ajout des sorties de terminal
2e48221 HEAD@{6}: commit: Ajout du fichier de reponse exo 7
679bdfc HEAD@{7}: pull origin main: Merge made by the 'ort' strategy.
9bac9fa HEAD@{8}: commit: Modification du bas du fichier par depot A
a1553e2 HEAD@{9}: commit: Initialisation de fichier.txt avec plusieurs lignes
f10c1f4 HEAD@{10}: commit: Initialisation de fichier.txt avec plusieurs lignes
dc91b6f HEAD@{11}: commit: Ajout du fichier de reponse exo 6
f7a7306 HEAD@{12}: commit (merge): Resolution du conflit de fusion
aa4b8c5 HEAD@{13}: commit: Modification depuis le depot A
34c2708 HEAD@{14}: commit: Ajout initial du fichier pour le conflit
:
44efe0e (HEAD -> main) HEAD@{0}: reset: moving to HEAD
44efe0e (HEAD -> main) HEAD@{1}: reset: moving to HEAD~1
3aa673d (origin/main) HEAD@{2}: commit: Ajout du fichier de reponse exo 7
44efe0e (HEAD -> main) HEAD@{3}: commit: Ajout fichier de base exo 8
e121650 HEAD@{4}: commit: Ajout du compte rendu exo 8 avec les sorties de terminal
5813c7b HEAD@{5}: commit: Correction exo 7 : ajout des sorties de terminal
2e48221 HEAD@{6}: commit: Ajout du fichier de reponse exo 7
679bdfc HEAD@{7}: pull origin main: Merge made by the 'ort' strategy.
9bac9fa HEAD@{8}: commit: Modification du bas du fichier par depot A
a1553e2 HEAD@{9}: commit: Initialisation de fichier.txt avec plusieurs lignes
f10c1f4 HEAD@{10}: commit: Initialisation de fichier.txt avec plusieurs lignes
dc91b6f HEAD@{11}: commit: Ajout du fichier de reponse exo 6
f7a7306 HEAD@{12}: commit (merge): Resolution du conflit de fusion
aa4b8c5 HEAD@{13}: commit: Modification depuis le depot A
34c2708 HEAD@{14}: commit: Ajout initial du fichier pour le conflit
a08a5ee HEAD@{15}: checkout: moving from main to main
a08a5ee HEAD@{16}: commit: Ajout initial du fichier pour le conflit
bc8fbc1 HEAD@{17}: checkout: moving from main to main
:
44efe0e (HEAD -> main) HEAD@{0}: reset: moving to HEAD
44efe0e (HEAD -> main) HEAD@{1}: reset: moving to HEAD~1
3aa673d (origin/main) HEAD@{2}: commit: Ajout du fichier de reponse exo 7
44efe0e (HEAD -> main) HEAD@{3}: commit: Ajout fichier de base exo 8
e121650 HEAD@{4}: commit: Ajout du compte rendu exo 8 avec les sorties de terminal
5813c7b HEAD@{5}: commit: Correction exo 7 : ajout des sorties de terminal
2e48221 HEAD@{6}: commit: Ajout du fichier de reponse exo 7
679bdfc HEAD@{7}: pull origin main: Merge made by the 'ort' strategy.
9bac9fa HEAD@{8}: commit: Modification du bas du fichier par depot A
a1553e2 HEAD@{9}: commit: Initialisation de fichier.txt avec plusieurs lignes
f10c1f4 HEAD@{10}: commit: Initialisation de fichier.txt avec plusieurs lignes
dc91b6f HEAD@{11}: commit: Ajout du fichier de reponse exo 6
f7a7306 HEAD@{12}: commit (merge): Resolution du conflit de fusion
aa4b8c5 HEAD@{13}: commit: Modification depuis le depot A
34c2708 HEAD@{14}: commit: Ajout initial du fichier pour le conflit
a08a5ee HEAD@{15}: checkout: moving from main to main
a08a5ee HEAD@{16}: commit: Ajout initial du fichier pour le conflit
bc8fbc1 HEAD@{17}: checkout: moving from main to main
bc8fbc1 HEAD@{18}: checkout: moving from main to main
bc8fbc1 HEAD@{19}: commit: Ajout du fichier de reponse exo 5
31a6e0a HEAD@{20}: checkout: moving from test-mesure to main
feee3c1 (test-mesure) HEAD@{21}: commit: Troisieme commit sur la branche
477731d HEAD@{22}: commit: Deuxieme commit sur la branche
6d17937 HEAD@{23}: commit: Premier commit sur la branche
:
44efe0e (HEAD -> main) HEAD@{0}: reset: moving to HEAD
44efe0e (HEAD -> main) HEAD@{1}: reset: moving to HEAD~1
3aa673d (origin/main) HEAD@{2}: commit: Ajout du fichier de reponse exo 7
44efe0e (HEAD -> main) HEAD@{3}: commit: Ajout fichier de base exo 8
e121650 HEAD@{4}: commit: Ajout du compte rendu exo 8 avec les sorties de terminal
5813c7b HEAD@{5}: commit: Correction exo 7 : ajout des sorties de terminal
2e48221 HEAD@{6}: commit: Ajout du fichier de reponse exo 7
679bdfc HEAD@{7}: pull origin main: Merge made by the 'ort' strategy.
9bac9fa HEAD@{8}: commit: Modification du bas du fichier par depot A
a1553e2 HEAD@{9}: commit: Initialisation de fichier.txt avec plusieurs lignes
f10c1f4 HEAD@{10}: commit: Initialisation de fichier.txt avec plusieurs lignes
dc91b6f HEAD@{11}: commit: Ajout du fichier de reponse exo 6
f7a7306 HEAD@{12}: commit (merge): Resolution du conflit de fusion
aa4b8c5 HEAD@{13}: commit: Modification depuis le depot A
34c2708 HEAD@{14}: commit: Ajout initial du fichier pour le conflit
a08a5ee HEAD@{15}: checkout: moving from main to main
a08a5ee HEAD@{16}: commit: Ajout initial du fichier pour le conflit
bc8fbc1 HEAD@{17}: checkout: moving from main to main
bc8fbc1 HEAD@{18}: checkout: moving from main to main
bc8fbc1 HEAD@{19}: commit: Ajout du fichier de reponse exo 5
31a6e0a HEAD@{20}: checkout: moving from test-mesure to main
feee3c1 (test-mesure) HEAD@{21}: commit: Troisieme commit sur la branche
477731d HEAD@{22}: commit: Deuxieme commit sur la branche
6d17937 HEAD@{23}: commit: Premier commit sur la branche
31a6e0a HEAD@{24}: checkout: moving from main to test-mesure
31a6e0a HEAD@{25}: pull origin main --rebase (finish): returning to refs/heads/main
:
44efe0e (HEAD -> main) HEAD@{0}: reset: moving to HEAD
44efe0e (HEAD -> main) HEAD@{1}: reset: moving to HEAD~1
3aa673d (origin/main) HEAD@{2}: commit: Ajout du fichier de reponse exo 7
44efe0e (HEAD -> main) HEAD@{3}: commit: Ajout fichier de base exo 8
e121650 HEAD@{4}: commit: Ajout du compte rendu exo 8 avec les sorties de terminal
5813c7b HEAD@{5}: commit: Correction exo 7 : ajout des sorties de terminal
2e48221 HEAD@{6}: commit: Ajout du fichier de reponse exo 7
679bdfc HEAD@{7}: pull origin main: Merge made by the 'ort' strategy.
9bac9fa HEAD@{8}: commit: Modification du bas du fichier par depot A
a1553e2 HEAD@{9}: commit: Initialisation de fichier.txt avec plusieurs lignes
f10c1f4 HEAD@{10}: commit: Initialisation de fichier.txt avec plusieurs lignes
dc91b6f HEAD@{11}: commit: Ajout du fichier de reponse exo 6
f7a7306 HEAD@{12}: commit (merge): Resolution du conflit de fusion
aa4b8c5 HEAD@{13}: commit: Modification depuis le depot A
34c2708 HEAD@{14}: commit: Ajout initial du fichier pour le conflit
a08a5ee HEAD@{15}: checkout: moving from main to main
a08a5ee HEAD@{16}: commit: Ajout initial du fichier pour le conflit
bc8fbc1 HEAD@{17}: checkout: moving from main to main
bc8fbc1 HEAD@{18}: checkout: moving from main to main
bc8fbc1 HEAD@{19}: commit: Ajout du fichier de reponse exo 5
31a6e0a HEAD@{20}: checkout: moving from test-mesure to main
feee3c1 (test-mesure) HEAD@{21}: commit: Troisieme commit sur la branche
477731d HEAD@{22}: commit: Deuxieme commit sur la branche
6d17937 HEAD@{23}: commit: Premier commit sur la branche
31a6e0a HEAD@{24}: checkout: moving from main to test-mesure
31a6e0a HEAD@{25}: pull origin main --rebase (finish): returning to refs/heads/main
31a6e0a HEAD@{26}: pull origin main --rebase (pick): Ajout du fichier de reponse exo4
:
44efe0e (HEAD -> main) HEAD@{0}: reset: moving to HEAD
44efe0e (HEAD -> main) HEAD@{1}: reset: moving to HEAD~1
3aa673d (origin/main) HEAD@{2}: commit: Ajout du fichier de reponse exo 7
44efe0e (HEAD -> main) HEAD@{3}: commit: Ajout fichier de base exo 8
e121650 HEAD@{4}: commit: Ajout du compte rendu exo 8 avec les sorties de terminal
5813c7b HEAD@{5}: commit: Correction exo 7 : ajout des sorties de terminal
2e48221 HEAD@{6}: commit: Ajout du fichier de reponse exo 7
679bdfc HEAD@{7}: pull origin main: Merge made by the 'ort' strategy.
9bac9fa HEAD@{8}: commit: Modification du bas du fichier par depot A
a1553e2 HEAD@{9}: commit: Initialisation de fichier.txt avec plusieurs lignes
f10c1f4 HEAD@{10}: commit: Initialisation de fichier.txt avec plusieurs lignes
dc91b6f HEAD@{11}: commit: Ajout du fichier de reponse exo 6
f7a7306 HEAD@{12}: commit (merge): Resolution du conflit de fusion
aa4b8c5 HEAD@{13}: commit: Modification depuis le depot A
34c2708 HEAD@{14}: commit: Ajout initial du fichier pour le conflit
a08a5ee HEAD@{15}: checkout: moving from main to main
a08a5ee HEAD@{16}: commit: Ajout initial du fichier pour le conflit
bc8fbc1 HEAD@{17}: checkout: moving from main to main
bc8fbc1 HEAD@{18}: checkout: moving from main to main
bc8fbc1 HEAD@{19}: commit: Ajout du fichier de reponse exo 5
31a6e0a HEAD@{20}: checkout: moving from test-mesure to main
feee3c1 (test-mesure) HEAD@{21}: commit: Troisieme commit sur la branche
477731d HEAD@{22}: commit: Deuxieme commit sur la branche
6d17937 HEAD@{23}: commit: Premier commit sur la branche
31a6e0a HEAD@{24}: checkout: moving from main to test-mesure
31a6e0a HEAD@{25}: pull origin main --rebase (finish): returning to refs/heads/main
31a6e0a HEAD@{26}: pull origin main --rebase (pick): Ajout du fichier de reponse exo4
dff28a3 HEAD@{27}: pull origin main --rebase (pick): Ajout des notes de mise à jour pour la version 2.
:
44efe0e (HEAD -> main) HEAD@{0}: reset: moving to HEAD
44efe0e (HEAD -> main) HEAD@{1}: reset: moving to HEAD~1
3aa673d (origin/main) HEAD@{2}: commit: Ajout du fichier de reponse exo 7
44efe0e (HEAD -> main) HEAD@{3}: commit: Ajout fichier de base exo 8
e121650 HEAD@{4}: commit: Ajout du compte rendu exo 8 avec les sorties de terminal
5813c7b HEAD@{5}: commit: Correction exo 7 : ajout des sorties de terminal
2e48221 HEAD@{6}: commit: Ajout du fichier de reponse exo 7
679bdfc HEAD@{7}: pull origin main: Merge made by the 'ort' strategy.
9bac9fa HEAD@{8}: commit: Modification du bas du fichier par depot A
a1553e2 HEAD@{9}: commit: Initialisation de fichier.txt avec plusieurs lignes
f10c1f4 HEAD@{10}: commit: Initialisation de fichier.txt avec plusieurs lignes
dc91b6f HEAD@{11}: commit: Ajout du fichier de reponse exo 6
f7a7306 HEAD@{12}: commit (merge): Resolution du conflit de fusion
aa4b8c5 HEAD@{13}: commit: Modification depuis le depot A
34c2708 HEAD@{14}: commit: Ajout initial du fichier pour le conflit
a08a5ee HEAD@{15}: checkout: moving from main to main
a08a5ee HEAD@{16}: commit: Ajout initial du fichier pour le conflit
bc8fbc1 HEAD@{17}: checkout: moving from main to main
bc8fbc1 HEAD@{18}: checkout: moving from main to main
bc8fbc1 HEAD@{19}: commit: Ajout du fichier de reponse exo 5
31a6e0a HEAD@{20}: checkout: moving from test-mesure to main
feee3c1 (test-mesure) HEAD@{21}: commit: Troisieme commit sur la branche
477731d HEAD@{22}: commit: Deuxieme commit sur la branche
6d17937 HEAD@{23}: commit: Premier commit sur la branche
31a6e0a HEAD@{24}: checkout: moving from main to test-mesure
31a6e0a HEAD@{25}: pull origin main --rebase (finish): returning to refs/heads/main
31a6e0a HEAD@{26}: pull origin main --rebase (pick): Ajout du fichier de reponse exo4
dff28a3 HEAD@{27}: pull origin main --rebase (pick): Ajout des notes de mise à jour pour la version 2.
f556949 HEAD@{28}: pull origin main --rebase (pick): Correction de la documentation du projet
:
44efe0e (HEAD -> main) HEAD@{0}: reset: moving to HEAD
44efe0e (HEAD -> main) HEAD@{1}: reset: moving to HEAD~1
3aa673d (origin/main) HEAD@{2}: commit: Ajout du fichier de reponse exo 7
44efe0e (HEAD -> main) HEAD@{3}: commit: Ajout fichier de base exo 8
e121650 HEAD@{4}: commit: Ajout du compte rendu exo 8 avec les sorties de terminal
5813c7b HEAD@{5}: commit: Correction exo 7 : ajout des sorties de terminal
2e48221 HEAD@{6}: commit: Ajout du fichier de reponse exo 7
679bdfc HEAD@{7}: pull origin main: Merge made by the 'ort' strategy.
9bac9fa HEAD@{8}: commit: Modification du bas du fichier par depot A
a1553e2 HEAD@{9}: commit: Initialisation de fichier.txt avec plusieurs lignes
f10c1f4 HEAD@{10}: commit: Initialisation de fichier.txt avec plusieurs lignes
dc91b6f HEAD@{11}: commit: Ajout du fichier de reponse exo 6
f7a7306 HEAD@{12}: commit (merge): Resolution du conflit de fusion
aa4b8c5 HEAD@{13}: commit: Modification depuis le depot A
34c2708 HEAD@{14}: commit: Ajout initial du fichier pour le conflit
a08a5ee HEAD@{15}: checkout: moving from main to main
a08a5ee HEAD@{16}: commit: Ajout initial du fichier pour le conflit
bc8fbc1 HEAD@{17}: checkout: moving from main to main
bc8fbc1 HEAD@{18}: checkout: moving from main to main
bc8fbc1 HEAD@{19}: commit: Ajout du fichier de reponse exo 5
31a6e0a HEAD@{20}: checkout: moving from test-mesure to main
feee3c1 (test-mesure) HEAD@{21}: commit: Troisieme commit sur la branche
477731d HEAD@{22}: commit: Deuxieme commit sur la branche
6d17937 HEAD@{23}: commit: Premier commit sur la branche
31a6e0a HEAD@{24}: checkout: moving from main to test-mesure
31a6e0a HEAD@{25}: pull origin main --rebase (finish): returning to refs/heads/main
31a6e0a HEAD@{26}: pull origin main --rebase (pick): Ajout du fichier de reponse exo4
dff28a3 HEAD@{27}: pull origin main --rebase (pick): Ajout des notes de mise à jour pour la version 2.
f556949 HEAD@{28}: pull origin main --rebase (pick): Correction de la documentation du projet
8e2d24d HEAD@{29}: pull origin main --rebase (start): checkout 8e2d24d6f227cedac783fd55473eda760a0c2eca
:
44efe0e (HEAD -> main) HEAD@{0}: reset: moving to HEAD
44efe0e (HEAD -> main) HEAD@{1}: reset: moving to HEAD~1
3aa673d (origin/main) HEAD@{2}: commit: Ajout du fichier de reponse exo 7
44efe0e (HEAD -> main) HEAD@{3}: commit: Ajout fichier de base exo 8
e121650 HEAD@{4}: commit: Ajout du compte rendu exo 8 avec les sorties de terminal
5813c7b HEAD@{5}: commit: Correction exo 7 : ajout des sorties de terminal
2e48221 HEAD@{6}: commit: Ajout du fichier de reponse exo 7
679bdfc HEAD@{7}: pull origin main: Merge made by the 'ort' strategy.
9bac9fa HEAD@{8}: commit: Modification du bas du fichier par depot A
a1553e2 HEAD@{9}: commit: Initialisation de fichier.txt avec plusieurs lignes
f10c1f4 HEAD@{10}: commit: Initialisation de fichier.txt avec plusieurs lignes
dc91b6f HEAD@{11}: commit: Ajout du fichier de reponse exo 6
f7a7306 HEAD@{12}: commit (merge): Resolution du conflit de fusion
aa4b8c5 HEAD@{13}: commit: Modification depuis le depot A
34c2708 HEAD@{14}: commit: Ajout initial du fichier pour le conflit
a08a5ee HEAD@{15}: checkout: moving from main to main
a08a5ee HEAD@{16}: commit: Ajout initial du fichier pour le conflit
bc8fbc1 HEAD@{17}: checkout: moving from main to main
bc8fbc1 HEAD@{18}: checkout: moving from main to main
bc8fbc1 HEAD@{19}: commit: Ajout du fichier de reponse exo 5
31a6e0a HEAD@{20}: checkout: moving from test-mesure to main
feee3c1 (test-mesure) HEAD@{21}: commit: Troisieme commit sur la branche
477731d HEAD@{22}: commit: Deuxieme commit sur la branche
6d17937 HEAD@{23}: commit: Premier commit sur la branche
31a6e0a HEAD@{24}: checkout: moving from main to test-mesure
31a6e0a HEAD@{25}: pull origin main --rebase (finish): returning to refs/heads/main
31a6e0a HEAD@{26}: pull origin main --rebase (pick): Ajout du fichier de reponse exo4
dff28a3 HEAD@{27}: pull origin main --rebase (pick): Ajout des notes de mise à jour pour la version 2.
f556949 HEAD@{28}: pull origin main --rebase (pick): Correction de la documentation du projet
8e2d24d HEAD@{29}: pull origin main --rebase (start): checkout 8e2d24d6f227cedac783fd55473eda760a0c2eca
f2f78b0 HEAD@{30}: reset: moving to HEAD
:
44efe0e (HEAD -> main) HEAD@{0}: reset: moving to HEAD
44efe0e (HEAD -> main) HEAD@{1}: reset: moving to HEAD~1
3aa673d (origin/main) HEAD@{2}: commit: Ajout du fichier de reponse exo 7
44efe0e (HEAD -> main) HEAD@{3}: commit: Ajout fichier de base exo 8
e121650 HEAD@{4}: commit: Ajout du compte rendu exo 8 avec les sorties de terminal
5813c7b HEAD@{5}: commit: Correction exo 7 : ajout des sorties de terminal
2e48221 HEAD@{6}: commit: Ajout du fichier de reponse exo 7
679bdfc HEAD@{7}: pull origin main: Merge made by the 'ort' strategy.
9bac9fa HEAD@{8}: commit: Modification du bas du fichier par depot A
a1553e2 HEAD@{9}: commit: Initialisation de fichier.txt avec plusieurs lignes
f10c1f4 HEAD@{10}: commit: Initialisation de fichier.txt avec plusieurs lignes
dc91b6f HEAD@{11}: commit: Ajout du fichier de reponse exo 6
f7a7306 HEAD@{12}: commit (merge): Resolution du conflit de fusion
aa4b8c5 HEAD@{13}: commit: Modification depuis le depot A
34c2708 HEAD@{14}: commit: Ajout initial du fichier pour le conflit
a08a5ee HEAD@{15}: checkout: moving from main to main
a08a5ee HEAD@{16}: commit: Ajout initial du fichier pour le conflit
bc8fbc1 HEAD@{17}: checkout: moving from main to main
bc8fbc1 HEAD@{18}: checkout: moving from main to main
bc8fbc1 HEAD@{19}: commit: Ajout du fichier de reponse exo 5
31a6e0a HEAD@{20}: checkout: moving from test-mesure to main
feee3c1 (test-mesure) HEAD@{21}: commit: Troisieme commit sur la branche
477731d HEAD@{22}: commit: Deuxieme commit sur la branche
6d17937 HEAD@{23}: commit: Premier commit sur la branche
31a6e0a HEAD@{24}: checkout: moving from main to test-mesure
31a6e0a HEAD@{25}: pull origin main --rebase (finish): returning to refs/heads/main
31a6e0a HEAD@{26}: pull origin main --rebase (pick): Ajout du fichier de reponse exo4
dff28a3 HEAD@{27}: pull origin main --rebase (pick): Ajout des notes de mise à jour pour la version 2.
f556949 HEAD@{28}: pull origin main --rebase (pick): Correction de la documentation du projet
8e2d24d HEAD@{29}: pull origin main --rebase (start): checkout 8e2d24d6f227cedac783fd55473eda760a0c2eca
:
44efe0e (HEAD -> main) HEAD@{0}: reset: moving to HEAD
44efe0e (HEAD -> main) HEAD@{1}: reset: moving to HEAD~1
3aa673d (origin/main) HEAD@{2}: commit: Ajout du fichier de reponse exo 7
44efe0e (HEAD -> main) HEAD@{3}: commit: Ajout fichier de base exo 8
e121650 HEAD@{4}: commit: Ajout du compte rendu exo 8 avec les sorties de terminal
5813c7b HEAD@{5}: commit: Correction exo 7 : ajout des sorties de terminal
2e48221 HEAD@{6}: commit: Ajout du fichier de reponse exo 7
679bdfc HEAD@{7}: pull origin main: Merge made by the 'ort' strategy.
9bac9fa HEAD@{8}: commit: Modification du bas du fichier par depot A
a1553e2 HEAD@{9}: commit: Initialisation de fichier.txt avec plusieurs lignes
f10c1f4 HEAD@{10}: commit: Initialisation de fichier.txt avec plusieurs lignes
dc91b6f HEAD@{11}: commit: Ajout du fichier de reponse exo 6
f7a7306 HEAD@{12}: commit (merge): Resolution du conflit de fusion
aa4b8c5 HEAD@{13}: commit: Modification depuis le depot A
34c2708 HEAD@{14}: commit: Ajout initial du fichier pour le conflit
a08a5ee HEAD@{15}: checkout: moving from main to main
a08a5ee HEAD@{16}: commit: Ajout initial du fichier pour le conflit
bc8fbc1 HEAD@{17}: checkout: moving from main to main
bc8fbc1 HEAD@{18}: checkout: moving from main to main
bc8fbc1 HEAD@{19}: commit: Ajout du fichier de reponse exo 5
31a6e0a HEAD@{20}: checkout: moving from test-mesure to main
feee3c1 (test-mesure) HEAD@{21}: commit: Troisieme commit sur la branche
477731d HEAD@{22}: commit: Deuxieme commit sur la branche
6d17937 HEAD@{23}: commit: Premier commit sur la branche
31a6e0a HEAD@{24}: checkout: moving from main to test-mesure
:
44efe0e (HEAD -> main) HEAD@{0}: reset: moving to HEAD
44efe0e (HEAD -> main) HEAD@{1}: reset: moving to HEAD~1
3aa673d (origin/main) HEAD@{2}: commit: Ajout du fichier de reponse exo 7
44efe0e (HEAD -> main) HEAD@{3}: commit: Ajout fichier de base exo 8
e121650 HEAD@{4}: commit: Ajout du compte rendu exo 8 avec les sorties de terminal
5813c7b HEAD@{5}: commit: Correction exo 7 : ajout des sorties de terminal
2e48221 HEAD@{6}: commit: Ajout du fichier de reponse exo 7
679bdfc HEAD@{7}: pull origin main: Merge made by the 'ort' strategy.
9bac9fa HEAD@{8}: commit: Modification du bas du fichier par depot A
:
44efe0e (HEAD -> main) HEAD@{0}: reset: moving to HEAD
44efe0e (HEAD -> main) HEAD@{1}: reset: moving to HEAD~1
3aa673d (origin/main) HEAD@{2}: commit: Ajout du fichier de reponse exo 7
44efe0e (HEAD -> main) HEAD@{3}: commit: Ajout fichier de base exo 8
e121650 HEAD@{4}: commit: Ajout du compte rendu exo 8 avec les sorties de terminal
5813c7b HEAD@{5}: commit: Correction exo 7 : ajout des sorties de terminal
2e48221 HEAD@{6}: commit: Ajout du fichier de reponse exo 7
679bdfc HEAD@{7}: pull origin main: Merge made by the 'ort' strategy.
9bac9fa HEAD@{8}: commit: Modification du bas du fichier par depot A
a1553e2 HEAD@{9}: commit: Initialisation de fichier.txt avec plusieurs lignes
f10c1f4 HEAD@{10}: commit: Initialisation de fichier.txt avec plusieurs lignes
dc91b6f HEAD@{11}: commit: Ajout du fichier de reponse exo 6
f7a7306 HEAD@{12}: commit (merge): Resolution du conflit de fusion
aa4b8c5 HEAD@{13}: commit: Modification depuis le depot A
34c2708 HEAD@{14}: commit: Ajout initial du fichier pour le conflit
a08a5ee HEAD@{15}: checkout: moving from main to main
a08a5ee HEAD@{16}: commit: Ajout initial du fichier pour le conflit
bc8fbc1 HEAD@{17}: checkout: moving from main to main
bc8fbc1 HEAD@{18}: checkout: moving from main to main
bc8fbc1 HEAD@{19}: commit: Ajout du fichier de reponse exo 5
31a6e0a HEAD@{20}: checkout: moving from test-mesure to main
feee3c1 (test-mesure) HEAD@{21}: commit: Troisieme commit sur la branche
477731d HEAD@{22}: commit: Deuxieme commit sur la branche
:
44efe0e (HEAD -> main) HEAD@{0}: reset: moving to HEAD
44efe0e (HEAD -> main) HEAD@{1}: reset: moving to HEAD~1
3aa673d (origin/main) HEAD@{2}: commit: Ajout du fichier de reponse exo 7
44efe0e (HEAD -> main) HEAD@{3}: commit: Ajout fichier de base exo 8
e121650 HEAD@{4}: commit: Ajout du compte rendu exo 8 avec les sorties de terminal
5813c7b HEAD@{5}: commit: Correction exo 7 : ajout des sorties de terminal
2e48221 HEAD@{6}: commit: Ajout du fichier de reponse exo 7
679bdfc HEAD@{7}: pull origin main: Merge made by the 'ort' strategy.
9bac9fa HEAD@{8}: commit: Modification du bas du fichier par depot A
a1553e2 HEAD@{9}: commit: Initialisation de fichier.txt avec plusieurs lignes
f10c1f4 HEAD@{10}: commit: Initialisation de fichier.txt avec plusieurs lignes
dc91b6f HEAD@{11}: commit: Ajout du fichier de reponse exo 6
f7a7306 HEAD@{12}: commit (merge): Resolution du conflit de fusion
aa4b8c5 HEAD@{13}: commit: Modification depuis le depot A
34c2708 HEAD@{14}: commit: Ajout initial du fichier pour le conflit
a08a5ee HEAD@{15}: checkout: moving from main to main
a08a5ee HEAD@{16}: commit: Ajout initial du fichier pour le conflit
bc8fbc1 HEAD@{17}: checkout: moving from main to main
bc8fbc1 HEAD@{18}: checkout: moving from main to main
bc8fbc1 HEAD@{19}: commit: Ajout du fichier de reponse exo 5
31a6e0a HEAD@{20}: checkout: moving from test-mesure to main
feee3c1 (test-mesure) HEAD@{21}: commit: Troisieme commit sur la branche
477731d HEAD@{22}: commit: Deuxieme commit sur la branche
6d17937 HEAD@{23}: commit: Premier commit sur la branche
:
44efe0e (HEAD -> main) HEAD@{0}: reset: moving to HEAD
44efe0e (HEAD -> main) HEAD@{1}: reset: moving to HEAD~1
3aa673d (origin/main) HEAD@{2}: commit: Ajout du fichier de reponse exo 7
44efe0e (HEAD -> main) HEAD@{3}: commit: Ajout fichier de base exo 8
e121650 HEAD@{4}: commit: Ajout du compte rendu exo 8 avec les sorties de terminal
5813c7b HEAD@{5}: commit: Correction exo 7 : ajout des sorties de terminal
2e48221 HEAD@{6}: commit: Ajout du fichier de reponse exo 7
679bdfc HEAD@{7}: pull origin main: Merge made by the 'ort' strategy.
9bac9fa HEAD@{8}: commit: Modification du bas du fichier par depot A
a1553e2 HEAD@{9}: commit: Initialisation de fichier.txt avec plusieurs lignes
f10c1f4 HEAD@{10}: commit: Initialisation de fichier.txt avec plusieurs lignes
dc91b6f HEAD@{11}: commit: Ajout du fichier de reponse exo 6
f7a7306 HEAD@{12}: commit (merge): Resolution du conflit de fusion
aa4b8c5 HEAD@{13}: commit: Modification depuis le depot A
:
44efe0e (HEAD -> main) HEAD@{0}: reset: moving to HEAD
:
44efe0e (HEAD -> main) HEAD@{0}: reset: moving to HEAD
44efe0e (HEAD -> main) HEAD@{1}: reset: moving to HEAD~1
:
44efe0e (HEAD -> main) HEAD@{0}: reset: moving to HEAD
44efe0e (HEAD -> main) HEAD@{1}: reset: moving to HEAD~1
3aa673d (origin/main) HEAD@{2}: commit: Ajout du fichier de reponse exo 7
:
44efe0e (HEAD -> main) HEAD@{0}: reset: moving to HEAD
44efe0e (HEAD -> main) HEAD@{1}: reset: moving to HEAD~1
3aa673d (origin/main) HEAD@{2}: commit: Ajout du fichier de reponse exo 7
44efe0e (HEAD -> main) HEAD@{3}: commit: Ajout fichier de base exo 8
:
44efe0e (HEAD -> main) HEAD@{0}: reset: moving to HEAD
44efe0e (HEAD -> main) HEAD@{1}: reset: moving to HEAD~1
3aa673d (origin/main) HEAD@{2}: commit: Ajout du fichier de reponse exo 7
44efe0e (HEAD -> main) HEAD@{3}: commit: Ajout fichier de base exo 8
e121650 HEAD@{4}: commit: Ajout du compte rendu exo 8 avec les sorties de terminal
:
44efe0e (HEAD -> main) HEAD@{0}: reset: moving to HEAD
44efe0e (HEAD -> main) HEAD@{1}: reset: moving to HEAD~1
3aa673d (origin/main) HEAD@{2}: commit: Ajout du fichier de reponse exo 7
44efe0e (HEAD -> main) HEAD@{3}: commit: Ajout fichier de base exo 8
e121650 HEAD@{4}: commit: Ajout du compte rendu exo 8 avec les sorties de terminal
5813c7b HEAD@{5}: commit: Correction exo 7 : ajout des sorties de terminal
:
44efe0e (HEAD -> main) HEAD@{0}: reset: moving to HEAD
44efe0e (HEAD -> main) HEAD@{1}: reset: moving to HEAD~1
3aa673d (origin/main) HEAD@{2}: commit: Ajout du fichier de reponse exo 7
44efe0e (HEAD -> main) HEAD@{3}: commit: Ajout fichier de base exo 8
e121650 HEAD@{4}: commit: Ajout du compte rendu exo 8 avec les sorties de terminal
5813c7b HEAD@{5}: commit: Correction exo 7 : ajout des sorties de terminal
2e48221 HEAD@{6}: commit: Ajout du fichier de reponse exo 7
679bdfc HEAD@{7}: pull origin main: Merge made by the 'ort' strategy.
9bac9fa HEAD@{8}: commit: Modification du bas du fichier par depot A
a1553e2 HEAD@{9}: commit: Initialisation de fichier.txt avec plusieurs lignes
f10c1f4 HEAD@{10}: commit: Initialisation de fichier.txt avec plusieurs lignes
dc91b6f HEAD@{11}: commit: Ajout du fichier de reponse exo 6
f7a7306 HEAD@{12}: commit (merge): Resolution du conflit de fusion
aa4b8c5 HEAD@{13}: commit: Modification depuis le depot A
:
44efe0e (HEAD -> main) HEAD@{0}: reset: moving to HEAD
44efe0e (HEAD -> main) HEAD@{1}: reset: moving to HEAD~1
3aa673d (origin/main) HEAD@{2}: commit: Ajout du fichier de reponse exo 7
44efe0e (HEAD -> main) HEAD@{3}: commit: Ajout fichier de base exo 8
e121650 HEAD@{4}: commit: Ajout du compte rendu exo 8 avec les sorties de terminal
5813c7b HEAD@{5}: commit: Correction exo 7 : ajout des sorties de terminal
2e48221 HEAD@{6}: commit: Ajout du fichier de reponse exo 7
679bdfc HEAD@{7}: pull origin main: Merge made by the 'ort' strategy.
9bac9fa HEAD@{8}: commit: Modification du bas du fichier par depot A
a1553e2 HEAD@{9}: commit: Initialisation de fichier.txt avec plusieurs lignes
f10c1f4 HEAD@{10}: commit: Initialisation de fichier.txt avec plusieurs lignes
dc91b6f HEAD@{11}: commit: Ajout du fichier de reponse exo 6
f7a7306 HEAD@{12}: commit (merge): Resolution du conflit de fusion
aa4b8c5 HEAD@{13}: commit: Modification depuis le depot A
34c2708 HEAD@{14}: commit: Ajout initial du fichier pour le conflit
a08a5ee HEAD@{15}: checkout: moving from main to main
a08a5ee HEAD@{16}: commit: Ajout initial du fichier pour le conflit
bc8fbc1 HEAD@{17}: checkout: moving from main to main
:
44efe0e (HEAD -> main) HEAD@{0}: reset: moving to HEAD
44efe0e (HEAD -> main) HEAD@{1}: reset: moving to HEAD~1
3aa673d (origin/main) HEAD@{2}: commit: Ajout du fichier de reponse exo 7
44efe0e (HEAD -> main) HEAD@{3}: commit: Ajout fichier de base exo 8
e121650 HEAD@{4}: commit: Ajout du compte rendu exo 8 avec les sorties de terminal
5813c7b HEAD@{5}: commit: Correction exo 7 : ajout des sorties de terminal
2e48221 HEAD@{6}: commit: Ajout du fichier de reponse exo 7
679bdfc HEAD@{7}: pull origin main: Merge made by the 'ort' strategy.
9bac9fa HEAD@{8}: commit: Modification du bas du fichier par depot A
a1553e2 HEAD@{9}: commit: Initialisation de fichier.txt avec plusieurs lignes
f10c1f4 HEAD@{10}: commit: Initialisation de fichier.txt avec plusieurs lignes
dc91b6f HEAD@{11}: commit: Ajout du fichier de reponse exo 6
f7a7306 HEAD@{12}: commit (merge): Resolution du conflit de fusion
aa4b8c5 HEAD@{13}: commit: Modification depuis le depot A
34c2708 HEAD@{14}: commit: Ajout initial du fichier pour le conflit
a08a5ee HEAD@{15}: checkout: moving from main to main
a08a5ee HEAD@{16}: commit: Ajout initial du fichier pour le conflit
bc8fbc1 HEAD@{17}: checkout: moving from main to main
bc8fbc1 HEAD@{18}: checkout: moving from main to main
bc8fbc1 HEAD@{19}: commit: Ajout du fichier de reponse exo 5
:
44efe0e (HEAD -> main) HEAD@{0}: reset: moving to HEAD
44efe0e (HEAD -> main) HEAD@{1}: reset: moving to HEAD~1
3aa673d (origin/main) HEAD@{2}: commit: Ajout du fichier de reponse exo 7
44efe0e (HEAD -> main) HEAD@{3}: commit: Ajout fichier de base exo 8
e121650 HEAD@{4}: commit: Ajout du compte rendu exo 8 avec les sorties de terminal
5813c7b HEAD@{5}: commit: Correction exo 7 : ajout des sorties de terminal
2e48221 HEAD@{6}: commit: Ajout du fichier de reponse exo 7
679bdfc HEAD@{7}: pull origin main: Merge made by the 'ort' strategy.
9bac9fa HEAD@{8}: commit: Modification du bas du fichier par depot A
a1553e2 HEAD@{9}: commit: Initialisation de fichier.txt avec plusieurs lignes
f10c1f4 HEAD@{10}: commit: Initialisation de fichier.txt avec plusieurs lignes
dc91b6f HEAD@{11}: commit: Ajout du fichier de reponse exo 6
f7a7306 HEAD@{12}: commit (merge): Resolution du conflit de fusion
aa4b8c5 HEAD@{13}: commit: Modification depuis le depot A
34c2708 HEAD@{14}: commit: Ajout initial du fichier pour le conflit
a08a5ee HEAD@{15}: checkout: moving from main to main
a08a5ee HEAD@{16}: commit: Ajout initial du fichier pour le conflit
bc8fbc1 HEAD@{17}: checkout: moving from main to main
bc8fbc1 HEAD@{18}: checkout: moving from main to main
bc8fbc1 HEAD@{19}: commit: Ajout du fichier de reponse exo 5
31a6e0a HEAD@{20}: checkout: moving from test-mesure to main
:
44efe0e (HEAD -> main) HEAD@{0}: reset: moving to HEAD
44efe0e (HEAD -> main) HEAD@{1}: reset: moving to HEAD~1
3aa673d (origin/main) HEAD@{2}: commit: Ajout du fichier de reponse exo 7
44efe0e (HEAD -> main) HEAD@{3}: commit: Ajout fichier de base exo 8
e121650 HEAD@{4}: commit: Ajout du compte rendu exo 8 avec les sorties de terminal
5813c7b HEAD@{5}: commit: Correction exo 7 : ajout des sorties de terminal
2e48221 HEAD@{6}: commit: Ajout du fichier de reponse exo 7
679bdfc HEAD@{7}: pull origin main: Merge made by the 'ort' strategy.
9bac9fa HEAD@{8}: commit: Modification du bas du fichier par depot A
a1553e2 HEAD@{9}: commit: Initialisation de fichier.txt avec plusieurs lignes
f10c1f4 HEAD@{10}: commit: Initialisation de fichier.txt avec plusieurs lignes
dc91b6f HEAD@{11}: commit: Ajout du fichier de reponse exo 6
f7a7306 HEAD@{12}: commit (merge): Resolution du conflit de fusion
aa4b8c5 HEAD@{13}: commit: Modification depuis le depot A
34c2708 HEAD@{14}: commit: Ajout initial du fichier pour le conflit
a08a5ee HEAD@{15}: checkout: moving from main to main
a08a5ee HEAD@{16}: commit: Ajout initial du fichier pour le conflit
bc8fbc1 HEAD@{17}: checkout: moving from main to main
:
44efe0e (HEAD -> main) HEAD@{0}: reset: moving to HEAD
44efe0e (HEAD -> main) HEAD@{1}: reset: moving to HEAD~1
3aa673d (origin/main) HEAD@{2}: commit: Ajout du fichier de reponse exo 7
:
44efe0e (HEAD -> main) HEAD@{0}: reset: moving to HEAD
44efe0e (HEAD -> main) HEAD@{1}: reset: moving to HEAD~1
3aa673d (origin/main) HEAD@{2}: commit: Ajout du fichier de reponse exo 7
44efe0e (HEAD -> main) HEAD@{3}: commit: Ajout fichier de base exo 8
e121650 HEAD@{4}: commit: Ajout du compte rendu exo 8 avec les sorties de terminal
5813c7b HEAD@{5}: commit: Correction exo 7 : ajout des sorties de terminal
2e48221 HEAD@{6}: commit: Ajout du fichier de reponse exo 7
679bdfc HEAD@{7}: pull origin main: Merge made by the 'ort' strategy.
9bac9fa HEAD@{8}: commit: Modification du bas du fichier par depot A
a1553e2 HEAD@{9}: commit: Initialisation de fichier.txt avec plusieurs lignes
f10c1f4 HEAD@{10}: commit: Initialisation de fichier.txt avec plusieurs lignes
dc91b6f HEAD@{11}: commit: Ajout du fichier de reponse exo 6
f7a7306 HEAD@{12}: commit (merge): Resolution du conflit de fusion
aa4b8c5 HEAD@{13}: commit: Modification depuis le depot A
34c2708 HEAD@{14}: commit: Ajout initial du fichier pour le conflit
:
44efe0e (HEAD -> main) HEAD@{0}: reset: moving to HEAD
44efe0e (HEAD -> main) HEAD@{1}: reset: moving to HEAD~1
3aa673d (origin/main) HEAD@{2}: commit: Ajout du fichier de reponse exo 7
44efe0e (HEAD -> main) HEAD@{3}: commit: Ajout fichier de base exo 8
e121650 HEAD@{4}: commit: Ajout du compte rendu exo 8 avec les sorties de terminal
5813c7b HEAD@{5}: commit: Correction exo 7 : ajout des sorties de terminal
2e48221 HEAD@{6}: commit: Ajout du fichier de reponse exo 7
679bdfc HEAD@{7}: pull origin main: Merge made by the 'ort' strategy.
9bac9fa HEAD@{8}: commit: Modification du bas du fichier par depot A
a1553e2 HEAD@{9}: commit: Initialisation de fichier.txt avec plusieurs lignes
f10c1f4 HEAD@{10}: commit: Initialisation de fichier.txt avec plusieurs lignes
dc91b6f HEAD@{11}: commit: Ajout du fichier de reponse exo 6
f7a7306 HEAD@{12}: commit (merge): Resolution du conflit de fusion
aa4b8c5 HEAD@{13}: commit: Modification depuis le depot A
34c2708 HEAD@{14}: commit: Ajout initial du fichier pour le conflit
a08a5ee HEAD@{15}: checkout: moving from main to main
:
44efe0e (HEAD -> main) HEAD@{0}: reset: moving to HEAD
44efe0e (HEAD -> main) HEAD@{1}: reset: moving to HEAD~1
3aa673d (origin/main) HEAD@{2}: commit: Ajout du fichier de reponse exo 7
44efe0e (HEAD -> main) HEAD@{3}: commit: Ajout fichier de base exo 8
e121650 HEAD@{4}: commit: Ajout du compte rendu exo 8 avec les sorties de terminal
5813c7b HEAD@{5}: commit: Correction exo 7 : ajout des sorties de terminal
2e48221 HEAD@{6}: commit: Ajout du fichier de reponse exo 7
679bdfc HEAD@{7}: pull origin main: Merge made by the 'ort' strategy.
9bac9fa HEAD@{8}: commit: Modification du bas du fichier par depot A
a1553e2 HEAD@{9}: commit: Initialisation de fichier.txt avec plusieurs lignes
f10c1f4 HEAD@{10}: commit: Initialisation de fichier.txt avec plusieurs lignes
dc91b6f HEAD@{11}: commit: Ajout du fichier de reponse exo 6
f7a7306 HEAD@{12}: commit (merge): Resolution du conflit de fusion
aa4b8c5 HEAD@{13}: commit: Modification depuis le depot A
34c2708 HEAD@{14}: commit: Ajout initial du fichier pour le conflit
a08a5ee HEAD@{15}: checkout: moving from main to main
a08a5ee HEAD@{16}: commit: Ajout initial du fichier pour le conflit
:
44efe0e (HEAD -> main) HEAD@{0}: reset: moving to HEAD
44efe0e (HEAD -> main) HEAD@{1}: reset: moving to HEAD~1
3aa673d (origin/main) HEAD@{2}: commit: Ajout du fichier de reponse exo 7
44efe0e (HEAD -> main) HEAD@{3}: commit: Ajout fichier de base exo 8
e121650 HEAD@{4}: commit: Ajout du compte rendu exo 8 avec les sorties de terminal
5813c7b HEAD@{5}: commit: Correction exo 7 : ajout des sorties de terminal
2e48221 HEAD@{6}: commit: Ajout du fichier de reponse exo 7
679bdfc HEAD@{7}: pull origin main: Merge made by the 'ort' strategy.
9bac9fa HEAD@{8}: commit: Modification du bas du fichier par depot A
a1553e2 HEAD@{9}: commit: Initialisation de fichier.txt avec plusieurs lignes
f10c1f4 HEAD@{10}: commit: Initialisation de fichier.txt avec plusieurs lignes
dc91b6f HEAD@{11}: commit: Ajout du fichier de reponse exo 6
f7a7306 HEAD@{12}: commit (merge): Resolution du conflit de fusion
aa4b8c5 HEAD@{13}: commit: Modification depuis le depot A
34c2708 HEAD@{14}: commit: Ajout initial du fichier pour le conflit
a08a5ee HEAD@{15}: checkout: moving from main to main
a08a5ee HEAD@{16}: commit: Ajout initial du fichier pour le conflit
bc8fbc1 HEAD@{17}: checkout: moving from main to main
:
44efe0e (HEAD -> main) HEAD@{0}: reset: moving to HEAD
44efe0e (HEAD -> main) HEAD@{1}: reset: moving to HEAD~1
3aa673d (origin/main) HEAD@{2}: commit: Ajout du fichier de reponse exo 7
44efe0e (HEAD -> main) HEAD@{3}: commit: Ajout fichier de base exo 8
e121650 HEAD@{4}: commit: Ajout du compte rendu exo 8 avec les sorties de terminal
5813c7b HEAD@{5}: commit: Correction exo 7 : ajout des sorties de terminal
2e48221 HEAD@{6}: commit: Ajout du fichier de reponse exo 7
679bdfc HEAD@{7}: pull origin main: Merge made by the 'ort' strategy.
9bac9fa HEAD@{8}: commit: Modification du bas du fichier par depot A
a1553e2 HEAD@{9}: commit: Initialisation de fichier.txt avec plusieurs lignes
f10c1f4 HEAD@{10}: commit: Initialisation de fichier.txt avec plusieurs lignes
dc91b6f HEAD@{11}: commit: Ajout du fichier de reponse exo 6
f7a7306 HEAD@{12}: commit (merge): Resolution du conflit de fusion
aa4b8c5 HEAD@{13}: commit: Modification depuis le depot A
34c2708 HEAD@{14}: commit: Ajout initial du fichier pour le conflit
a08a5ee HEAD@{15}: checkout: moving from main to main
a08a5ee HEAD@{16}: commit: Ajout initial du fichier pour le conflit
bc8fbc1 HEAD@{17}: checkout: moving from main to main
bc8fbc1 HEAD@{18}: checkout: moving from main to main
bc8fbc1 HEAD@{19}: commit: Ajout du fichier de reponse exo 5
31a6e0a HEAD@{20}: checkout: moving from test-mesure to main
feee3c1 (test-mesure) HEAD@{21}: commit: Troisieme commit sur la branche
477731d HEAD@{22}: commit: Deuxieme commit sur la branche
6d17937 HEAD@{23}: commit: Premier commit sur la branche
:




















