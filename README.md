# Propagation du Feu avec Automates Cellulaires

## Description

La propagation des feux est un phénomène complexe qui peut être modélisé à l'aide d’automate cellulaire, une technique permettant de simuler des systèmes dynamiques discrets. Dans le contexte de la simulation de propagation des feux, les cellules d'une grille se transforment selon des règles spécifiques qui imitent la manière dont un feu se propage dans un environnement donné. Cette simulation peut être visualisée de différentes manières, et ce rapport présente trois implémentations distinctes pour modéliser et afficher ce phénomène.

## Contenu

- **`fire_simulation.c`** :  Ce code utilise une grille simple pour afficher les états des cellules à l'aide de caractères ASCII :
                    •	**`.`** : pour les cellules intactes
                    •	**`F`** : pour les cellules en feu
                    •	**`B`** : pour les cellules brûlées

- **`fire_simulation2.c`** : Ce code utilise les fonctionnalités de la console Windows pour afficher les cellules avec différentes couleurs :
                    •	**`Rouge`** pour les cellules en feu
                    •	**`Bleu`** clair pour les cellules brûlées
                    •	**`Vert`** pour les cellules intactes

- **`fire_simulation3.c`** : Ce code combine l'affichage de couleurs ANSI pour les cellules avec la parallélisation OpenMP pour la mise à jour de la grille. Les couleurs utilisées sont :
                    •	**`Vert`** pour les cellules intactes
                    •	**`Rouge`** pour les cellules en feu
                    •	**`Jaune`** pour les cellules brûlées
- **`Amelioration_fire.c`** : Ce code est une version ameliorée du code **`fire_simulation3.c`**.


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

- **Ouvrez le terminal MSYS2 MINGW64.**
- **Naviguez jusqu'au répertoire contenant votre fichier source`fire_simulation.c`.**
- **Compilez le code avec les commandes suivantes :**
   ```sh
    gcc -fopenmp -o fire_simulation fire_simulation.c
   ./fire_simulation


