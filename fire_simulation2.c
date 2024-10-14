#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define N 10        // Taille de la grille (N x N)
#define STEPS 6    // Nombre d'étapes de simulation
#define DELAY 100000 // Délai entre les étapes (en microsecondes)  0.1 secondes

// États possibles des cellules
#define INTACT 0
#define BURNING 1
#define BURNED 2

// Fonction pour initialiser la console
void initialize_console() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    csbi.wAttributes = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE; // Couleur par défaut
    SetConsoleTextAttribute(hConsole, csbi.wAttributes);
}

// Fonction pour dessiner la grille avec des caractères ASCII
void draw_grid(int grid[N][N]) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (grid[i][j] == BURNING) {
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); // Rouge pour brûlé
                printf("F");
            } else if (grid[i][j] == BURNED) {
                SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY); // Bleu clair pour brûlé
                printf(" ");
            } else {
                SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY); // Vert pour intact
                printf(".");
            }
        }
        printf("\n");
    }

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // Réinitialiser la couleur
}

// Fonction pour mettre à jour la grille
void update_grid(int current[N][N], int next[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (current[i][j] == INTACT && (
                (i > 0 && current[i-1][j] == BURNING) ||
                (i < N-1 && current[i+1][j] == BURNING) ||
                (j > 0 && current[i][j-1] == BURNING) ||
                (j < N-1 && current[i][j+1] == BURNING))) {
                next[i][j] = BURNING;
            } else if (current[i][j] == BURNING) {
                next[i][j] = BURNED;
            } else {
                next[i][j] = current[i][j];
            }
        }
    }
}

int main() {
    initialize_console();

    int grid[N][N] = {0};     // Grille actuelle
    int next_grid[N][N] = {0}; // Grille mise à jour

    // Initialisation : on met le feu à une partie du terrain
    grid[N/2][N/2] = BURNING;

    // Simulation sur un nombre défini d'étapes
    for (int step = 0; step < STEPS; step++) {
        // Mettre à jour la grille
        update_grid(grid, next_grid);

        // Dessiner la grille
        draw_grid(next_grid);

        // Attendre quelques millisecondes pour observer l'animation
        Sleep(DELAY / 1000); // Délai entre les étapes (en millisecondes)  100 millisecondes => 0.1 seconde

        // Copier la nouvelle grille dans l'ancienne
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                grid[i][j] = next_grid[i][j];
            }
        }

        system("cls"); // Effacer l'écran pour la prochaine mise à jour
    }

    return 0;
}
