# Exercice 9-1 : L'histoire d'un fichier

## Fichier analysé
**Chemin du fichier :** `Applications/NKCode/ROADMAP.md`

---

## 1. Création du fichier
* **Commit initial :** `3dcb6c78`
* **Message de commit :** `refactor(widgets): Phase 1 - gestionnaire de menu contextuel REUTILISABLE (shell-level)`
* **Contexte de création :**
Le fichier a été introduit lors de la mise en place de la Phase 1 du projet NKCode. Il sert de feuille de route pour consigner les spécifications techniques, les phases de développement et le suivi de l'avancement global du composant NKCode au sein de l'écosystème Nkentseu.

---

## 2. Les 3 moments clés de son évolution

### Moment 1 : Structuration initiale et gestion des agents (Phase 11)
* **Commit :** `96a1e159`
* **Message :** `docs(nkcode): ROADMAP a jour - Phase 11 Agents (chat/permissions/Compte&Usage FAITS) + 4 points en attente`
* **Nature des modifications :** Mise à jour majeure documentant la Phase 11 concernant l'intégration des agents IA (systèmes de chat, permissions et compte d'usage).
* **Raison transmise par le message :** Le message explique précisément que la Phase 11 des agents a été complétée et fait le point sur les 4 éléments restants à traiter.

### Moment 2 : Intégration de l'IA, du PDF et du support Linux (Phase 14)
* **Commit :** `18f96e22`
* **Message :** `NKCode : visionneuse PDF, portage Linux, execution dediee et agents IA (pont IDE + MCP + comptes) (#56)`
* **Nature des modifications :** Ajout de spécifications techniques pour le support multiplateforme (Linux/X11), la visionneuse PDF embarquée et la connexion avancée des agents IA via MCP.
* **Raison transmise par le message :** Le commit documente l'extension des fonctionnalités clés de NKCode pour devenir un environnement de développement autonome et multiplateforme.

### Moment 3 : Recadrage de la vision et clarification de l'échéance Web
* **Commit :** `12b8c339`
* **Message :** `Feuilles de route : remettre d aplomb ce que le code dement`
* **Nature des modifications :** Révision critique de la roadmap pour aligner la documentation sur l'état réel du code et supprimer les incohérences.
* **Raison transmise par le message :** L'auteur exprime la nécessité d'assainir la feuille de route afin qu'elle reflète strictement la réalité technique de l'implémentation plutôt que des affirmations obsolètes.

---

## 3. Synthèse de l'histoire du fichier
Initialement créé au commit `3dcb6c78` pour encadrer le développement des premières interfaces de NKCode, le fichier `ROADMAP.md` a évolué au rythme des grandes étapes du projet. Il est passé par une phase d'expansion fonctionnelle majeure (intégration des agents IA et support Linux aux commits `96a1e159` et `18f96e22`), avant de faire l'objet de révisions plus réalistes au commit `12b8c339` pour corriger les décalages entre la théorie documentée et le code réellement implémenté.