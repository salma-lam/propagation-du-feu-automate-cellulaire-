#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 20        // Taille de la grille (N x N)
#define STEPS 20    // Nombre d'étapes de simulation réduit à 20

// États possibles des cellules
#define INTACT 0
#define BURNING 1
#define BURNED 2

// Fonction pour afficher la grille
void print_grid(int grid[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (grid[i][j] == INTACT) {
                printf(".");
            } else if (grid[i][j] == BURNING) {
                printf("F");
            } else {
                printf("B");
            }
        }
        printf("\n");
    }
    printf("\n");
}

// Fonction pour compter les cellules en feu autour d'une cellule
int is_burning_nearby(int grid[N][N], int x, int y) {
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue;  // Ignorer la cellule elle-même
            int nx = (x + i + N) % N;  // Gestion des bords
            int ny = (y + j + N) % N;
            if (grid[nx][ny] == BURNING) {
                return 1;
            }
        }
    }
    return 0;
}

// Mise à jour de la grille
void update_grid(int current[N][N], int next[N][N]) {
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (current[i][j] == INTACT && is_burning_nearby(current, i, j)) {
                next[i][j] = BURNING;  // Le feu se propage
            } else if (current[i][j] == BURNING) {
                next[i][j] = BURNED;  // La cellule a brûlé
            } else {
                next[i][j] = current[i][j];  // Sinon, reste inchangée
            }
        }
    }
}

int main() {
    int grid[N][N] = {0};     // Grille actuelle
    int next_grid[N][N] = {0}; // Grille mise à jour

    // Initialisation : on met le feu à une partie du terrain
    grid[N/2][N/2] = BURNING;

    printf("État initial :\n");
    print_grid(grid);

    // Simulation sur un nombre défini d'étapes
    for (int step = 0; step < STEPS; step++) {
        update_grid(grid, next_grid);

        // Copier la nouvelle grille dans l'ancienne
        #pragma omp parallel for collapse(2)
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                grid[i][j] = next_grid[i][j];
            }
        }

        // Afficher la grille après chaque étape
        printf("Étape %d :\n", step + 1);
        print_grid(grid);
    }

    return 0;
}
