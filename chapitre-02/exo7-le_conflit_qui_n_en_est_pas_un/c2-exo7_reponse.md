# Exercice 7 : Le conflit qui n'en est pas un

## 1. Description du scénario
Deux personnes ont modifié le même fichier (`fichier.txt`), mais à des lignes différentes :
- Le Clone B a modifié la ligne 1 (haut du fichier)[span_0](start_span)[span_0](end_span).
- Le Dépôt A a modifié la ligne 5 (bas du fichier)[span_1](start_span)[span_1](end_span).

## 2. Comportement de Git
Lors de l'exécution de `git pull` dans le Dépôt A[span_2](start_span)[span_2](end_span) :
1. Git a analysé les deux versions du fichier.
2. Constatant que les modifications ne se chevauchaient pas sur les mêmes lignes, Git a effectué une fusion automatique (*auto-merge*) sans générer de conflit[span_3](start_span)[span_3](end_span).
3. Il a utilisé la stratégie de fusion par défaut (`ort strategy`) pour combiner les deux changements[span_4](start_span)[span_4](end_span).