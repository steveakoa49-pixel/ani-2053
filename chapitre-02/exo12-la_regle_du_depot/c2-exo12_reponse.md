# Charte Git du Projet — Équipe de 4 Étudiants

## 1. Nommage des branches
* **Branche principale (`main`) :** Contient le code stable, validé et prêt à être déployé ou rendu.
* **Branches de fonctionnalités :** Doivent suivre la convention `<type>/<prenom>-<description>` :
  * `feat/steve-login` (nouvelle fonctionnalité)
  * `fix/loveline-bug-auth` (correction de bug)
  * `docs/emma-readme` (mise à jour de la documentation)

---

## 2. Contenu et format des commits
* **Atomicité :** Un commit doit représenter une seule modification logique (pas de "gros commit" regroupant plusieurs fonctionnalités indépendantes).
* **Format du message :** Suivre la convention *Conventional Commits* en anglais ou français clair :
  * `<type>: <description courte et claire au présent>`
  * Exemple : `feat: ajout du formulaire de connexion` ou `fix: correction de l'erreur d'affichage du profil`

---

## 3. Relecture du code (Code Review)
* **Revue obligatoire :** Aucun push direct sur `main`. Tout passage par `main` se fait via une **Pull Request (PR)**.
* **Qui relit quoi :** Chaque Pull Request doit être relue et approuvée par **au moins un autre membre de l'équipe** avant d'être fusionnée.
* **Critères de relecture :** Le code doit fonctionner localement, respecter les normes de nommage et ne pas contenir de fichiers inutiles.

---

## 4. Ce qui est strictement interdit
* ❌ **Pas de push direct sur `main`** : toutes les modifications passent par une branche dédiée et une PR.
* ❌ **Pas de fichiers sensibles/volumineux** : interdiction de commiter des clés d'API, des mots de passe ou des fichiers de build/dépendances (utiliser `.gitignore`).
* ❌ **Pas de `git push --force` sur `main`** : afin de ne pas altérer l'historique commun de l'équipe.

---

## 5. Procédure en cas de branche principale (`main`) cassée
Si le code sur `main` ne fonctionne plus suite à une fusion :
1. **Alerter l'équipe :** Prévenir immédiatement les 3 autres membres sur le canal de discussion du groupe.
2. **Priorité absolue :** L'auteur du dernier commit fusionné prend en charge la résolution en priorité.
3. **Correction ou Annulation (Revert) :**
   * Si le correctif est rapide (< 10 min) : créer une branche `fix/hotfix-main`, corriger et faire valider la PR en urgence.
   * Si la correction prend du temps : exécuter `git revert <hash_du_commit>` sur une branche corrective pour annuler les modifications défectueuses et rétablir `main` dans un état stable immédiatement.