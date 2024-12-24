#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROWS 100
#define MAX_COLS 100

// Affichage d'une matrice
void afficher_matrice(char mat[][MAX_COLS], int lignes) {
    for (int i = 0; i < lignes; i++) {
        printf("%s\n", mat[i]);
    }
}

// Tri à bulles pour une matrice (tri des lignes en ordre alphabétique)
void tri_bulle_matrice(char mat[][MAX_COLS], int lignes, int *nbComp, int *nbPerm) {
    for (int i = 0; i < lignes - 1; i++) {
        for (int j = 0; j < lignes - i - 1; j++) {
            (*nbComp)++;
            if (strcmp(mat[j], mat[j + 1]) > 0) {
                char temp[MAX_COLS];
                strncpy(temp, mat[j], MAX_COLS);
                strncpy(mat[j], mat[j + 1], MAX_COLS);
                strncpy(mat[j + 1], temp, MAX_COLS);
                (*nbPerm)++;
            }
        }
        printf("Etat apres l'iteration %d :\n", i + 1);
        afficher_matrice(mat, lignes);
    }
}

// Fusion pour tri fusion (matrice)
void fusion_matrice(char mat[][MAX_COLS], int gauche, int milieu, int droit, int *nbComp, int *nbPerm) {
    int n1 = milieu - gauche + 1; // Taille de la partie gauche
    int n2 = droit - milieu;     // Taille de la partie droite
    char gaucheMat[n1][MAX_COLS], droiteMat[n2][MAX_COLS];

    // Copie des sous-matrices gauche et droite
    for (int i = 0; i < n1; i++) strncpy(gaucheMat[i], mat[gauche + i], MAX_COLS);
    for (int j = 0; j < n2; j++) strncpy(droiteMat[j], mat[milieu + 1 + j], MAX_COLS);

    int i = 0, j = 0, k = gauche; // Pointeurs pour gaucheMat, droiteMat et mat

    // Fusion des deux sous-matrices
    while (i < n1 && j < n2) {
        (*nbComp)++;
        if (strcmp(gaucheMat[i], droiteMat[j]) <= 0) {
            strncpy(mat[k], gaucheMat[i], MAX_COLS);
            i++;
        } else {
            strncpy(mat[k], droiteMat[j], MAX_COLS);
            j++;
            (*nbPerm)++;
        }
        k++;
    }

    // Copie des éléments restants de gaucheMat
    while (i < n1) {
        strncpy(mat[k], gaucheMat[i], MAX_COLS);
        i++;
        k++;
        (*nbPerm)++; 
    }

    // Copie des éléments restants de droiteMat
    while (j < n2) {
        strncpy(mat[k], droiteMat[j], MAX_COLS);
        j++;
        k++;
        (*nbPerm)++; 
    }
}

// Tri fusion pour matrice
void tri_fusion_matrice(char mat[][MAX_COLS], int gauche, int droit, int *nbComp, int *nbPerm) {
    if (gauche < droit) {
        int milieu = gauche + (droit - gauche) / 2;
        tri_fusion_matrice(mat, gauche, milieu, nbComp, nbPerm);
        tri_fusion_matrice(mat, milieu + 1, droit, nbComp, nbPerm);
        fusion_matrice(mat, gauche, milieu, droit, nbComp, nbPerm);
        
        printf("Etat apres l'iteration:\n");
        afficher_matrice(mat, droit + 1);
    }
}

int main() {
    int choix, nbComp, nbPerm, lignes;
    char matrice[MAX_ROWS][MAX_COLS];

    printf("Entrez le nombre de lignes de la matrice  : ");
    if (scanf("%d", &lignes) != 1 || lignes <= 0 || lignes > MAX_ROWS) {
        printf("Nombre de lignes invalide.\n");
        return 1;
    }
    getchar(); // pour consommer le caractère '\n' restant

    printf("Entrez les chaines de caracteres \n ");
    for (int i = 0; i < lignes; i++) {
        if (!fgets(matrice[i], MAX_COLS, stdin)) {
            printf("Erreur de lecture.\n");
            return 1;
        }
        matrice[i][strcspn(matrice[i], "\n")] = '\0'; // Supprime le '\n'
    }

    do {
        printf("\n--- Menu Tri pour Matrice ---\n");
        printf("1. Tri a bulles\n");
        printf("2. Tri fusion\n");
        printf("3. Quitter\n");
        printf("Votre choix : ");
        if (scanf("%d", &choix) != 1) {
            printf("Erreur de saisie.\n");
            break;
        }
        getchar(); // Consomme '\n'

        nbComp = 0;
        nbPerm = 0;

        switch (choix) {
            case 1:
                printf("\nTri a bulles :\n");
                tri_bulle_matrice(matrice, lignes, &nbComp, &nbPerm);
                break;
            case 2:
                printf("\nTri fusion :\n");
                tri_fusion_matrice(matrice, 0, lignes - 1, &nbComp, &nbPerm);
                break;
            case 3:
                printf("Au revoir !\n");
                break;
            default:
                printf("Choix invalide.\n");
        }

        if (choix == 1 || choix == 2) {
            printf("Nombre de comparaisons : %d\n", nbComp);
            printf("Nombre de permutations : %d\n", nbPerm);
        }
    } while (choix != 3);

    return 0;
}
