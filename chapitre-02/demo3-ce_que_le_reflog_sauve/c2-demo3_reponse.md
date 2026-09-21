# Démonstration 3 : Ce que le reflog sauve

## 1. Création et suppression volontaire du travail

1. **Commit du travail important :**
   ```bash
   echo "Fichier tres important avec du code crucial" > travail_important.txt
   git add travail_important.txt
   git commit -m "demo3: travail important a ne pas perdre"
   # Commit créé : e7f7cf1

a. Destruction du travail via reset --hard :
Bash
*git reset --hard HEAD~1*
# Sortie : HEAD is now at 6a86ba4 fichier_conflit.txt

b. Constat de la perte dans git log :
Le commit e7f7cf1 n'apparaît plus dans l'historique classique (git log --oneline -n 3).


## 2. Consultation du reflog et identification de l'empreinte

1. **Sortie de la commande git reflog -n 5 : :**
   6a86ba4 (HEAD -> main, origin/main) HEAD@{0}: reset: moving to HEAD~1
e7f7cf1 HEAD@{1}: commit: demo3: travail important a ne pas perdre
6a86ba4 (HEAD -> main, origin/main) HEAD@{2}: commit: fichier_conflit.txt
b0fc62a HEAD@{3}: commit: demo2: resolution du conflit en direct
64d2bb5 HEAD@{4}: commit (merge): demo2: resolution du conflit en direct

Analyse : Le reflog conserve l'historique de toutes les actions sur HEAD. Le commit perdu e7f7cf1 est clairement identifié au niveau HEAD@{1}.


## 3. Restauration du commit perdu

**Commande de restauration exécutée : :**
git reset --hard e7f7cf1
# Sortie : HEAD is now at e7f7cf1 demo3: travail important a ne pas perdre

Résultat : Le travail a été entièrement restauré, et le fichier travail_important.txt est de nouveau présent dans le répertoire de travail.