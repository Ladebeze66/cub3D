# Cub3D
![illustration cub3d](./picture.png)
Le projet Cub3D de l'École 42 consiste à développer un moteur graphique en C, inspiré du jeu classique Wolfenstein 3D. L'objectif principal est d'implémenter une vue en trois dimensions à partir d'une carte en deux dimensions en utilisant la technique du raycasting. Ce projet permet aux étudiants de se familiariser avec les concepts fondamentaux de la programmation graphique et de la gestion des événements en temps réel.

🎯 Objectifs du Projet
Compréhension du Raycasting : Apprendre et implémenter la technique du raycasting pour simuler une perspective 3D à partir d'une carte 2D.

Manipulation de la MiniLibX : Utiliser la bibliothèque graphique minimaliste MiniLibX pour gérer l'affichage, les événements clavier et souris, ainsi que le rendu des images.

Gestion des Textures et des Couleurs : Appliquer des textures aux surfaces rendues et gérer les couleurs pour améliorer le réalisme de la scène.

Gestion des Collisions : Implémenter la détection des collisions pour empêcher le joueur de traverser les murs ou les obstacles.

Parsage de Fichiers de Configuration : Lire et interpréter des fichiers de configuration pour définir la carte du jeu, les positions de départ, les textures, etc.

🛠️ Spécifications Techniques
Langage de Programmation : C.

Bibliothèque Graphique : MiniLibX, une bibliothèque graphique simple fournie par l'École 42.

Fonctionnalités à Implémenter :

Affichage en 3D : Rendu en temps réel d'une scène 3D en utilisant le raycasting.
Mouvements du Joueur : Gestion des déplacements avant, arrière et latéraux, ainsi que la rotation de la vue.
Gestion des Textures : Application de textures sur les murs et autres surfaces.
Minicarte : Affichage d'une minicarte 2D pour représenter la position du joueur et la disposition de la carte.
Gestion des Événements : Réponse aux entrées clavier et souris pour le contrôle du joueur.
Parsage de la Carte : Lecture de fichiers de configuration pour générer la carte du jeu.
🔧 Approche d'Implémentation
Initialisation de la MiniLibX :

Configurer la fenêtre d'affichage et initialiser les paramètres nécessaires.
Parsage de la Carte :

Lire le fichier de configuration pour créer une représentation en mémoire de la carte, incluant les positions des murs, des espaces vides, et la position initiale du joueur.
Implémentation du Raycasting :

Calculer les intersections des rayons avec les murs pour déterminer les distances et les angles, afin de rendre la scène en 3D.
Gestion des Mouvements et des Collisions :

Mettre en place la logique pour déplacer le joueur tout en détectant et en empêchant les collisions avec les murs.
Application des Textures :

Charger les images des textures et les appliquer aux surfaces correspondantes lors du rendu.
Gestion des Événements :

Configurer les callbacks pour les entrées clavier et souris afin de permettre le contrôle du joueur.
Affichage de la Minicarte :

Dessiner une représentation 2D de la carte et de la position du joueur pour faciliter la navigation.

🧪 Tests et Validation
Tests Fonctionnels :

Vérifier que le rendu 3D est correct et que les murs apparaissent aux bonnes positions.
Tester les mouvements du joueur pour s'assurer qu'ils sont fluides et que les collisions sont correctement détectées.
Confirmer que les textures sont correctement appliquées aux surfaces correspondantes.
Tests de Performance :

Évaluer le taux de rafraîchissement pour s'assurer que le jeu fonctionne de manière fluide.
Optimiser le code pour réduire la charge processeur et améliorer les performances.
Tests d'Intégration :

S'assurer que tous les composants (parsing, rendu, gestion des entrées) fonctionnent ensemble de manière cohérente.

📚 **Ressources Utiles

Dépôts GitHub d'étudiants :

Guides et tutoriels :

[42: A Comprehensive Guide to Cub3D : Un guide détaillé qui explore les détails de l'implémentation de l'algorithme de raycasting, en se concentrant sur les fonctions clés et leur rôle dans le rendu de l'environnement 3D.][https://reactive.so/post/42-a-comprehensive-guide-to-cub3d/]

Documentation :

[cub3d | 42 Docs : Une documentation complète sur le projet Cub3D, incluant des exemples de code, des astuces d'optimisation, et bien plus encore.][https://harm-smits.github.io/42docs/projects/cub3d]
