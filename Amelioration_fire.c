#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <omp.h>
#include <time.h> // Pour mesurer le temps d'exécution

#define N 100        // Taille de la grille (N x N) augmentée
#define STEPS 50    // Nombre d'étapes de simulation augmentée
#define DELAY 100000 // Délai entre les étapes (en microsecondes)

// États possibles des cellules
#define INTACT 0
#define BURNING 1
#define BURNED 2

// Fonction pour initialiser la console
void initialize_console() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    csbi.wAttributes = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE; 
    SetConsoleTextAttribute(hConsole, csbi.wAttributes);
}

// Fonction pour afficher la grille avec des couleurs ANSI
void draw_grid(int grid[N][N]) {
    // Codes de couleurs ANSI
    const char* intact_color = "\x1b[42m";  // Vert pour les cellules intactes
    const char* burning_color = "\x1b[41m"; // Rouge pour les cellules en feu
    const char* burned_color = "\x1b[43m";  // Jaune pour les cellules brûlées
    const char* reset_color = "\x1b[0m";    // Réinitialiser la couleur

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (grid[i][j] == BURNING) {
                printf("%s F %s", burning_color, reset_color);
            } else if (grid[i][j] == BURNED) {
                printf("%s B %s", burned_color, reset_color);
            } else if (grid[i][j] == INTACT) {
                printf("%s . %s", intact_color, reset_color);
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

// Mise à jour de la grille (séquentielle)
void update_grid_sequential(int current[N][N], int next[N][N]) {
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

// Mise à jour de la grille (parallèle)
void update_grid_parallel(int current[N][N], int next[N][N]) {
    #pragma omp parallel for collapse(2) schedule(dynamic)
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
    initialize_console();

    int grid[N][N] = {0};     // Grille actuelle
    int next_grid[N][N] = {0}; // Grille mise à jour

    // Initialisation : on met le feu à une partie du terrain
    grid[N/2][N/2] = BURNING;

    // ================= PARTIE SÉQUENTIELLE =================
    clock_t start_time_seq = clock();  // Début du chronométrage séquentiel

    // Simulation séquentielle sur un nombre défini d'étapes
    for (int step = 0; step < STEPS; step++) {
        // Mettre à jour la grille (séquentielle)
        update_grid_sequential(grid, next_grid);

        // Copier la nouvelle grille dans l'ancienne
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                grid[i][j] = next_grid[i][j];
            }
        }

        // Afficher la grille après chaque étape
        printf("Étape %d (Séquentielle) :\n", step + 1);
        draw_grid(grid);

        Sleep(DELAY / 1000); // Délai entre les étapes (en millisecondes)
        system("cls"); // Effacer l'écran pour la prochaine mise à jour
    }

    clock_t end_time_seq = clock();  // Fin du chronométrage séquentiel
    double execution_time_seq = (double)(end_time_seq - start_time_seq) / CLOCKS_PER_SEC;

    // ================= PARTIE PARALLÈLE =================
    // Réinitialisation de la grille
    grid[N/2][N/2] = BURNING;
    
    omp_set_num_threads(4);  // Limiter à 4 threads par exemple

    clock_t start_time_par = clock();  // Début du chronométrage parallèle

    // Simulation parallèle sur un nombre défini d'étapes
    for (int step = 0; step < STEPS; step++) {
        // Mettre à jour la grille (parallèle)
        update_grid_parallel(grid, next_grid);

        // Copier la nouvelle grille dans l'ancienne
        #pragma omp parallel for collapse(2) schedule(dynamic)
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                grid[i][j] = next_grid[i][j];
            }
        }

        // Afficher la grille après chaque étape
        printf("Étape %d (Parallèle) :\n", step + 1);
        draw_grid(grid);

        Sleep(DELAY / 1000); // Délai entre les étapes (en millisecondes)
        system("cls"); // Effacer l'écran pour la prochaine mise à jour
    }

    clock_t end_time_par = clock();  // Fin du chronométrage parallèle
    double execution_time_par = (double)(end_time_par - start_time_par) / CLOCKS_PER_SEC;

    // Calcul du speedup
    double speedup = execution_time_seq / execution_time_par;

    // Affichage des résultats
    printf("Temps d'exécution séquentiel : %.2f secondes\n", execution_time_seq);
    printf("Temps d'exécution parallèle  : %.2f secondes\n", execution_time_par);
    printf("Speedup : %.2f\n", speedup);

    return 0;
}
