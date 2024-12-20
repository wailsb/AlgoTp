#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Fonction pour échanger deux éléments
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Fonction pour afficher un tableau
void afficher_tableau(int t[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", t[i]);
    }
    printf("\n");
}

// Tri par sélection
void tri_selection(int t[], int n, int *nbComp, int *nbPerm) {
    for (int i = 0; i < n - 1; i++) {
        int k = i;
        for (int j = i + 1; j < n; j++) {
            (*nbComp)++; // Comparaison
            if (t[j] < t[k]) {
                k = j;
            }
        }
        if (k != i) {
            swap(&t[k], &t[i]);
            (*nbPerm)++; // Permutation
        }
        printf("État après l'itération %d : ", i + 1);
        afficher_tableau(t, n);
    }
}

// Tri à bulles
void tri_bulle(int t[], int n, int *nbComp, int *nbPerm) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            (*nbComp)++; // Comparaison
            if (t[j] > t[j + 1]) {
                swap(&t[j], &t[j + 1]);
                (*nbPerm)++; // Permutation
            }
        }
        printf("État après l'itération %d : ", i + 1);
        afficher_tableau(t, n);
    }
}

// Tri par insertion
void tri_insertion(int t[], int n, int *nbComp, int *nbPerm) {
    for (int i = 1; i < n; i++) {
        int k = t[i];
        int j = i - 1;
        while (j >= 0 && t[j] > k) {
            (*nbComp)++; // Comparaison
            t[j + 1] = t[j];
            j--;
            (*nbPerm)++; // Déplacement
        }
        (*nbComp)++; // Comparaison échouée
        t[j + 1] = k;
        printf("État après l'itération %d : ", i);
        afficher_tableau(t, n);
    }
}

// Tri fusion
void fusion(int t[], int gauche, int milieu, int droit, int *nbComp, int *nbPerm) {
    int n1 = milieu - gauche + 1;
    int n2 = droit - milieu;
    int L[n1], R[n2];

    for (int i = 0; i < n1; i++) L[i] = t[gauche + i];
    for (int j = 0; j < n2; j++) R[j] = t[milieu + 1 + j];

    int i = 0, j = 0, k = gauche;
    while (i < n1 && j < n2) {
        (*nbComp)++;
        if (L[i] <= R[j]) {
            t[k++] = L[i++];
        } else {
            t[k++] = R[j++];
        }
        (*nbPerm)++;
        // Afficher l'état du tableau après chaque insertion dans t
        afficher_tableau(t, droit + 1);
    }

    while (i < n1) {
        t[k++] = L[i++];
        (*nbPerm)++;
        afficher_tableau(t, droit + 1);
    }

    while (j < n2) {
        t[k++] = R[j++];
        (*nbPerm)++;
        afficher_tableau(t, droit + 1);
    }
}


void tri_fusion(int t[], int gauche, int droit, int *nbComp, int *nbPerm) {
    if (gauche < droit) {
        int milieu = gauche + (droit - gauche) / 2;
        tri_fusion(t, gauche, milieu, nbComp, nbPerm);
        tri_fusion(t, milieu + 1, droit, nbComp, nbPerm);
        fusion(t, gauche, milieu, droit, nbComp, nbPerm);
    }
}

// Tri rapide
void tri_rapide(int t[], int low, int high, int *nbComp, int *nbPerm) {
    if (low < high) {
        int pivot = t[high];
        int i = low - 1;

        for (int j = low; j < high; j++) {
            (*nbComp)++;
            if (t[j] < pivot) {
                i++;
                swap(&t[i], &t[j]);
                (*nbPerm)++;
                afficher_tableau(t,high+1);
            }
          
        }
        swap(&t[i + 1], &t[high]);
        (*nbPerm)++;
        afficher_tableau(t,high);
        int pi = i + 1;

        tri_rapide(t, low, pi - 1, nbComp, nbPerm);
        tri_rapide(t, pi + 1, high, nbComp, nbPerm);
    }
}

// Tri peigne
void tri_peigne(int t[], int n, int *nbComp, int *nbPerm) {
    int gap = n;
    bool swapped = true;

    while (gap > 1 || swapped) {
        gap = (gap * 10) / 13;
        if (gap < 1) gap = 1;

        swapped = false;
        for (int i = 0; i < n - gap; i++) {
            (*nbComp)++;
            if (t[i] > t[i + gap]) {
                swap(&t[i], &t[i + gap]);
                (*nbPerm)++;
                afficher_tableau(t,n);
                swapped = true;
            }
        }
    }
}

int main() {
    int choix, n, nbComp, nbPerm;

    printf("Entrez la taille du tableau : ");
    scanf("%d", &n);
    if (n <= 0) {
        printf("La taille du tableau doit être positive.\n");
        return 1;
    }

    int *t = (int *)malloc(n * sizeof(int));
    if (t == NULL) {
        printf("Erreur d'allocation mémoire.\n");
        return 1;
    }

    printf("Entrez les %d éléments du tableau :\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &t[i]);
    }

    do {
        printf("\n--- Menu des algorithmes de tri ---\n");
        printf("1. Tri par sélection\n");
        printf("2. Tri à bulles\n");
        printf("3. Tri par insertion\n");
        printf("4. Tri fusion\n");
        printf("5. Tri rapide\n");
        printf("6. Tri peigne\n");
        printf("7. Quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        
        nbComp = 0;
        nbPerm = 0;

        switch (choix) {
            case 1:
                printf("\nTri par sélection :\n");
                tri_selection(t, n, &nbComp, &nbPerm);
                break;
            case 2:
                printf("\nTri à bulles :\n");
                tri_bulle(t, n, &nbComp, &nbPerm);
                break;
            case 3:
                printf("\nTri par insertion :\n");
                tri_insertion(t, n, &nbComp, &nbPerm);
                break;
            case 4:
                printf("\nTri fusion :\n");
                tri_fusion(t, 0, n - 1, &nbComp, &nbPerm);
                afficher_tableau(t, n);
                break;
            case 5:
                printf("\nTri rapide :\n");
                tri_rapide(t, 0, n - 1, &nbComp, &nbPerm);
                afficher_tableau(t, n);
                break;
            case 6:
                printf("\nTri peigne :\n");
                tri_peigne(t, n, &nbComp, &nbPerm);
                afficher_tableau(t, n);
                break;
            case 7:
                printf("Au revoir !\n");
                break;
            default:
                printf("Choix invalide.\n");
        }

        if (choix >= 1 && choix <= 6) {
            printf("Nombre de comparaisons : %d\n", nbComp);
            printf("Nombre de permutations : %d\n", nbPerm);
        }
    } while (choix != 7);

    free(t);
    return 0;
}
