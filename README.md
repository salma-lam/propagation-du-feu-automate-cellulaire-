# Propagation du Feu avec Automates Cellulaires

## Description

Ce projet simule la propagation du feu sur une grille en utilisant des automates cellulaires. Le modèle implémente une simulation simple où le feu se propage d'une cellule à une autre en fonction des cellules voisines en feu. La simulation est parallélisée à l'aide d'OpenMP pour améliorer les performances.

## Contenu

- **`incendie.c`** :  Ce code simule la propagation du feu sur une grille carrée en parallélisant les mises à jour avec OpenMP pour améliorer la performance.
- **`incendie2.c`** : Ce code simule la propagation du feu sur une grille carrée et utilise des couleurs dans la console Windows pour visualiser l'état des cellules à chaque étape.
- **`fire_simulation.c`** : Ce code utilise OpenMP pour simuler la propagation du feu sur une grille, affiche les états des cellules en utilisant des couleurs ANSI dans la console Windows, et actualise l'affichage à chaque étape avec un délai pour l'animation.

## Fonctionnalités

- **Simulation de la propagation du feu** : Le feu se propage à partir d'une cellule enflammée vers les cellules voisines.
- **Affichage en couleurs** :
  - Vert pour les cellules intactes
  - Rouge pour les cellules en feu
  - Jaune pour les cellules brûlées
- **Parallélisation avec OpenMP** : Améliore les performances de la simulation en exécutant les mises à jour de la grille en parallèle.

## Prérequis

- **Compilateur C** (gcc, clang, etc.)
- **OpenMP** pour la parallélisation
- **Windows** (pour les fonctionnalités spécifiques à la console Windows)

## Compilation et Exécution

1. **Compilation** :

   ```sh
   gcc -o simulation main.c -fopenmp
