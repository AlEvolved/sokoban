#ifndef STRUCT_H
#define STRUCT_H

typedef struct {
    int x_player;
    int y_player;
    int x_caisse;
    int y_caisse;
    int x_target;
    int y_target;
    int x_cible;
    int y_cible
}jeux;

char plateau[TAILLE][TAILLE];
#define MUR '#'
#define VIDE ' '
#define JOUEUR 'o'
#define CAISSE 'x'
#define CIBLE '.'  
#define TAILLE 10


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


#endif