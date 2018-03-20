# Notes importantes
 - **Toujours tester avant de commit.**
 - En cas d'erreur lors du commit suivre cette syntaxe : Correction - Classe(s) - Brève description.
 - Vous devez choisir entre Create, Modify, Debug ou Remove.

# Format des descriptions pour les fichiers C++ du projet. (Commit)
[Create / Modify / Debug / Remove] - Classe(s) - Brève description de ce qui a été fait.

# Format des descriptions pour les fichiers de documentation et autres fichiers.
Lorsque l'on modifie un seul fichier directement dans gitHub, nous ometterons le nom du fichier.

Exemple: [Create / Modify / Remove] - Brève description.

Sinon, nous suiverons le modèle suivant:
[Create / Modify / Remove] - Nom des fichier - Brève description.

# Fréquence suggérée des commits
 - À chaque fois que l'on quitte ou qu'on arrête de travailler sur le projet.
 - À chaque modification significative (ajout de fonctionnalité, création de header, correction d'un bug, suppression,[...]).
 - À chaque fois que l'on ajoute un ou plusieurs fichiers (image, modèles, textures. [...])
 
# Rappel des commandes
- git config --global user.name "Prénom Nom"
- git config --global user.email "adresse@courriel.qc.ca"
- git log
- git status -s
- git add [fichierA fichierB ...]
- git remove [fichierA fichierB ...]
- git commit -am "Commentaire"
- git pull origin master
- git push origin master
