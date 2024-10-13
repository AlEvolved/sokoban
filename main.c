#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


#define MUR '#'
#define VIDE ' '
#define JOUEUR 'o'
#define CAISSE 'x'
#define CIBLE '.'  
#define TAILLE 10

char plateau[TAILLE][TAILLE];
void afficher_grille(char plateau[TAILLE][TAILLE]) {
    for (int i = 0; i < TAILLE; i++) {
        for (int j = 0; j < TAILLE; j++) {
            printf("%c", plateau[i][j]);
        }
        printf("\n");
    }
}

void positionner_caisse(char plateau[TAILLE][TAILLE], int x_caisse, int y_caisse) {
    if (plateau[y_caisse][x_caisse] == VIDE) {
        plateau[y_caisse][x_caisse] = CAISSE;
    } else {
        printf("Erreur: la case (%d, %d) est déjà occupée ou invalide.\n", x_caisse, y_caisse);
    }
}

void positionner_joueur(char plateau[TAILLE][TAILLE], int x_joueur, int y_joueur) {
    if (plateau[y_joueur][x_joueur] == VIDE) {
        plateau[y_joueur][x_joueur] = JOUEUR;
    } else {
        printf("Erreur: la case (%d, %d) est déjà occupée ou invalide.\n", x_joueur, y_joueur);
    }
}

int pousser_caisse(char plateau[TAILLE][TAILLE], int x_caisse, int y_caisse, int delta_x, int delta_y) {
    int nouvelle_position_x = x_caisse + delta_x;
    int nouvelle_position_y = y_caisse + delta_y;

    if (nouvelle_position_x >= 0 && nouvelle_position_x < TAILLE && nouvelle_position_y >= 0 && nouvelle_position_y < TAILLE) {
        if (plateau[nouvelle_position_y][nouvelle_position_x] == VIDE || plateau[nouvelle_position_y][nouvelle_position_x] == CIBLE) {
            plateau[y_caisse][x_caisse] = VIDE;  
            plateau[nouvelle_position_y][nouvelle_position_x] = CAISSE;  
            return 1;  
        }
    }
    return 0;  
}

int deplacer_joueur(char plateau[TAILLE][TAILLE], int *x_joueur, int *y_joueur, int delta_x, int delta_y, int *x_caisse, int *y_caisse) {
    int nouvelle_position_x = *x_joueur + delta_x;
    int nouvelle_position_y = *y_joueur + delta_y;

    if (nouvelle_position_x >= 0 && nouvelle_position_x < TAILLE && nouvelle_position_y >= 0 && nouvelle_position_y < TAILLE) {
        if (plateau[nouvelle_position_y][nouvelle_position_x] == VIDE) {
            plateau[*y_joueur][*x_joueur] = VIDE;
            *x_joueur = nouvelle_position_x;
            *y_joueur = nouvelle_position_y;
            plateau[*y_joueur][*x_joueur] = JOUEUR;
            return 1;
        } else if (plateau[nouvelle_position_y][nouvelle_position_x] == CAISSE) {
            if (pousser_caisse(plateau, *x_caisse, *y_caisse, delta_x, delta_y)) {
                plateau[*y_joueur][*x_joueur] = VIDE;
                *x_joueur = nouvelle_position_x;
                *y_joueur = nouvelle_position_y;
                plateau[*y_joueur][*x_joueur] = JOUEUR;
                *x_caisse += delta_x;
                *y_caisse += delta_y;
                return 1;
            }
        }
    }
    return 0;
}

int condition_victoire(int x_caisse, int y_caisse) {
    if (x_caisse == 5 && y_caisse == 5) {  
        printf("Bravo ! Vous avez gagné, la caisse est sur l'objectif.\n");
        return 1;  
    }
    return 0; 
}
int condition_defaite(char plateau[TAILLE][TAILLE], int x_caisse, int y_caisse) {
    if ((plateau[y_caisse - 1][x_caisse] == MUR || plateau[y_caisse - 1][x_caisse] == CAISSE) &&
        (plateau[y_caisse][x_caisse - 1] == MUR || plateau[y_caisse][x_caisse - 1] == CAISSE)) {
        printf("Défaite ! La caisse est bloquée en haut à gauche.\n");
        return 1;
    }
    if ((plateau[y_caisse - 1][x_caisse] == MUR || plateau[y_caisse - 1][x_caisse] == CAISSE) &&
        (plateau[y_caisse][x_caisse + 1] == MUR || plateau[y_caisse][x_caisse + 1] == CAISSE)) {
        printf("Défaite ! La caisse est bloquée en haut à droite.\n");
        return 1;
    }
    if ((plateau[y_caisse + 1][x_caisse] == MUR || plateau[y_caisse + 1][x_caisse] == CAISSE) &&
        (plateau[y_caisse][x_caisse - 1] == MUR || plateau[y_caisse][x_caisse - 1] == CAISSE)) {
        printf("Défaite ! La caisse est bloquée en bas à gauche.\n");
        return 1;
    }
    if ((plateau[y_caisse + 1][x_caisse] == MUR || plateau[y_caisse + 1][x_caisse] == CAISSE) &&
        (plateau[y_caisse][x_caisse + 1] == MUR || plateau[y_caisse][x_caisse + 1] == CAISSE)) {
        printf("Défaite ! La caisse est bloquée en bas à droite.\n");
        return 1;
    }

    // Vérifier si la caisse est bloquée contre des murs opposés
    if ((plateau[y_caisse - 1][x_caisse] == MUR || plateau[y_caisse - 1][x_caisse] == CAISSE) &&
        (plateau[y_caisse + 1][x_caisse] == MUR || plateau[y_caisse + 1][x_caisse] == CAISSE)) {
        printf("Défaite ! La caisse est bloquée verticalement.\n");
        return 1;
    }
    if ((plateau[y_caisse][x_caisse - 1] == MUR || plateau[y_caisse][x_caisse - 1] == CAISSE) &&
        (plateau[y_caisse][x_caisse + 1] == MUR || plateau[y_caisse][x_caisse + 1] == CAISSE)) {
        printf("Défaite ! La caisse est bloquée horizontalement.\n");
        return 1;
    }

    return 0;  
}

int main() {
    for (int i = 0; i < TAILLE; i++) {
        for (int j = 0; j < TAILLE; j++) {
            plateau[i][j] = VIDE;
        }
    }
    for (int i = 0; i < TAILLE; i++) {
        plateau[0][i] = MUR;
        plateau[TAILLE - 1][i] = MUR;
        plateau[i][0] = MUR;
        plateau[i][TAILLE - 1] = MUR;
    }
    plateau[5][5] = CIBLE;  

    srand(time(NULL));
    int x_caisse = 6;  
    int y_caisse = 7; 
    int x_joueur = rand() % (TAILLE - 2) + 1;  
    int y_joueur = rand() % (TAILLE - 2) + 1;
    
    positionner_joueur(plateau, x_joueur, y_joueur);
    positionner_caisse(plateau, x_caisse, y_caisse);

    afficher_grille(plateau);

    char input;
     int game_running = 1; 
    while (game_running) {
    printf("Déplacez le joueur (z:Haut, s:Bas, q:Gauche, d:Droite, e:Quitter) : \n");
    scanf(" %c", &input);

    if (input == 'z') {
        deplacer_joueur(plateau, &x_joueur, &y_joueur, 0, -1, &x_caisse, &y_caisse);
    } else if (input == 's') {
        deplacer_joueur(plateau, &x_joueur, &y_joueur, 0, 1, &x_caisse, &y_caisse);
    } else if (input == 'q') {
        deplacer_joueur(plateau, &x_joueur, &y_joueur, -1, 0, &x_caisse, &y_caisse);
    } else if (input == 'd') {
        deplacer_joueur(plateau, &x_joueur, &y_joueur, 1, 0, &x_caisse, &y_caisse);
    } else if (input == 'e') {
        printf("Vous avez quitté le jeu.\n");
        game_running = 0;  
    } else {
        printf("Entrée invalide. Veuillez entrer z, s, q, d ou e pour quitter.\n");
    }

    // Vérifier la condition de victoire
    if (condition_victoire(x_caisse, y_caisse)) {
        game_running = 0;  
    }

    // Vérifier la condition de défaite
    if (condition_defaite(plateau, x_caisse, y_caisse)) {
        game_running = 0;  
    }
    printf("Coordonnées du joueur: (%d, %d)\n", x_joueur, y_joueur);
    printf("Coordonnées de la caisse: (%d, %d)\n", x_caisse, y_caisse);
    printf("Coordonnées de la cible: (5, 5)\n"); 

    afficher_grille(plateau);
    sleep(2);
    system("clear");
}

}


