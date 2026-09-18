# Exercice : Les trois endroits

## 1. Après modification du fichier
```text
On branch main              
Your branch is up to date with 'origin/main'.

Changes not staged for commit:
  (use "git add <file>..." to update what will be committed)
  (use "git restore <file>..." to discard changes in working directory)
        modified:   ../../.github/copilot-instructions.md
        modified:   ../../.github/copilot-toolbox-mcp-skills-awareness.md
        modified:   ../../fichier1.txt

no changes added to commit (use "git add" and/or "git commit -a")
```

## 2. Après le git add
```text
On branch main
Your branch is up to date with 'origin/main'.

Changes to be committed:
  (use "git restore --staged <file>..." to unstage)
        modified:   ../../fichier1.txt

Changes not staged for commit:
  (use "git add <file>..." to update what will be committed)
  (use "git restore <file>..." to discard changes in working directory)
        modified:   ../../.github/copilot-instructions.md
        modified:   ../../.github/copilot-toolbox-mcp-skills-awareness.md
```

## 3. Après le git commit
```text
On branch main
Your branch is ahead of 'origin/main' by 1 commit.
  (use "git push" to publish your local commits)

Changes not staged for commit:
  (use "git add <file>..." to update what will be committed)
  (use "git restore <file>..." to discard changes in working directory)
        modified:   ../../.github/copilot-instructions.md
        modified:   ../../.github/copilot-toolbox-mcp-skills-awareness.md

no changes added to commit (use "git add" and/or "git commit -a")
```

## 4. Ce qui change entre les étapes (Explications)

- *Entre la modification et le git add (Espace de travail vs Index) :* 
  Le fichier modifié apparaît sous "Changes not staged for commit" (en rouge). Les modifications existent uniquement dans le répertore de travail (Working Directory) et n'ont pas encore été sélectionnées pour faire partie du futur commit.
- *Entre le git add et le git commit (Index vs Dépôt) :* 
  Le fichier passe sous "Changes to be committed" (en vert). Il se trouve désormais dans la zone de transit/indexation (Staging Area). Il est préparé et prêt à être sauvegardé définitivement.
- *Après le git commit (Dépôt actualisé) :* 
  Le fichier ⁠fichier1.txt⁠ n'apparaît plus dans l'état de Git car les modifications ont été enregistrées dans l'historique du dépôt (Local Repository). Le fichier est maintenant sauvegardé.