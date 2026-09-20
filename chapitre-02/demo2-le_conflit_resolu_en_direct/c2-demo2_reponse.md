# Démonstration 2 : Le conflit résolu en direct

## 1. Procédure réelle de provocation du conflit

```bash
# Création du fichier initial sur main
echo "Ligne initiale du fichier" > fichier_conflit.txt
git add fichier_conflit.txt
git commit -m "demo2: fichier initial sur main"
# Commit généré : 221b5f3

# Modification sur la branche 'feature-conflit'
git checkout -b feature-conflit
echo "Ligne modifiee par la branche feature-conflit" > fichier_conflit.txt
git commit -am "demo2: modification sur feature-conflit"
# Commit généré : ba751b7

# Modification concurrente sur 'main'
git checkout main
echo "Ligne modifiee en parallele sur main" > fichier_conflit.txt
git commit -am "demo2: modification concurrente sur main"
# Commit généré : 9784270

# Tentative de fusion
git merge feature-conflit
# Sortie : CONFLICT (content): Merge conflict in chapitre-02/demo2-le_conflit_resolu_en_direct/fichier_conflit.txt

## 2. Lecture réelle des marqueurs de conflit

### Contenu exact généré par Git dans ⁠fichier_conflit.txt⁠ au moment du conflit :
<<<<<<< HEAD
Ligne modifiee en parallele sur main
=======
Ligne modifiee par la branche feature-conflit
>>>>>>> feature-conflit

<<<<<<< HEAD⁠ à ⁠=======⁠ : Modifications apportées sur la branche courante (⁠main⁠).
 ⁠=======⁠ à ⁠>>>>>>> feature-conflit⁠ : Modifications apportées par la branche intégrée (⁠feature-conflit⁠).

 ##3. Résolution et reconstruction du fichier

### Décision : Conservation des deux apports pour intégrer l'ensemble des modifications.

### Contenu final du fichier nettoyé (⁠fichier_conflit.txt⁠) :
Ligne modifiee en parallele sur main
Ligne modifiee par la branche feature-conflit

##4. Validation et graphe 

### Commandes de finalisation :
git add fichier_conflit.txt
git commit -m "demo2: resolution du conflit en direct"
# Commit de fusion généré : 64d2bb5

### Extrait de ⁠git log --graph --oneline -n 5⁠ :
*   64d2bb5 (HEAD -> main) demo2: resolution du conflit en direct
|\  
| * ba751b7 (feature-conflit) demo2: modification sur feature-conflit
* | 9784270 demo2: modification concurrente sur main
|/  
* 221b5f3 demo2: fichier initial sur main


