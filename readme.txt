Vous pouvez retrouver plus d'informations dans le rapport concernant les instructions de compilation, de lancement, et de fonctionnement du jeu.

Les fichiers sources se trouvent dans le répertoire "TheMind".
Les documents se trouvent dans le répertoire "Documents".

Dépendances nécessaires pour compiler :
- sudo apt-get install make
- sudo apt-get install cmake

Dépendances nécessaires pour exécuter :
- sudo apt-get install texlive-latex-base
- sudo apt-get install texlive-latex-extra
- sudo apt-get install texlive-lang-french

Dépendances optionnelles :
- sudo apt-get install doxygen

Pour compiler, dans le répertoire "TheMind", tapez les commandes :
- cmake .
- make

Pour lancer le serveur, exécutez le fichier :
- "TheMind/ServerProject/ServerProject"

Pour lancer un ou plusieurs clients, exécutez le fichier :
- "TheMind/ClientProject/ClientProject"

À renseigner dans l'écran de connexion d'un client :
- IP du serveur   : 127.0.0.1
- Port du serveur : 25565