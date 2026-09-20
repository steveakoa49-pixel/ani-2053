# Exercice 11 : Le fichier qu'on n'aurait pas dû

## 1. Expérimentation et mesures réelles

### A. État initial du dossier `.git`
* **Taille initiale mesurée :** `114 926 octets` (~114,9 Ko) pour 243 fichiers objets.

### B. Ajout, commit et suppression du fichier
1. **Création et commit du fichier :**
   * Fichier créé : `fichier_lisible_10mo.txt`
   * Commit d'ajout : `31102be` (`ajout d un fichier texte lisible de 10 Mo`)
2. **Suppression au commit suivant :**
   * Commande : `git rm fichier_lisible_10mo.txt`
   * Commit de suppression : `3225a9c` (`suppression du fichier texte lisible`)

### C. État final du dossier `.git`
* **Taille finale mesurée :** `118 219 octets` (~118,2 Ko) pour 250 fichiers objets.

---

## 2. Conclusion et analyse sur le fonctionnement de Git

### Constat
Malgré la suppression complète du fichier dans le répertoire de travail (*working tree*), **la taille du dossier `.git` a augmenté (passant de 114 926 à 118 219 octets) et n'est pas revenue à sa taille d'origine**.

### Explication technique
1. **Immuabilité de l'historique :** Git conserve l'intégralité des révisions passées. Un commit dans Git est un instantané historique permanent.
2. **Stockage sous forme d'objets (Blobs) :** Lors du `git add`, le contenu du fichier est compressé et enregistré sous forme d'objet *blob* dans la base de données interne (`.git/objects/`).
3. **Incapacité de `git rm` à effacer le passé :** La commande `git rm` enregistre simplement un nouvel état de la branche où le fichier n'apparaît plus, mais elle n'efface pas l'objet créateur dans le commit `31102be`. Git doit conserver cet objet pour qu'il soit toujours possible d'exécuter un `git checkout 31102be` et de retrouver le fichier d'origine.

### Bonne pratique
* Ne jamais commiter de fichiers très volumineux ou générés automatiquement sur un dépôt Git standard.
* Utiliser un fichier `.gitignore` en amont.
* En cas d'erreur avant envoi distant, réécrire l'historique localement (via `git filter-repo` ou `BFG Repo-Cleaner`) pour purger définitivement les blobs volumineux.