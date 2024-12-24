#include "trieliste.h"
#include "triematrice.h"
#include "trievecteur.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_ROWS 100
#define MAX_COLS 100

// Structures
typedef struct Node {
    char data[100];
    struct Node *next;
} Node;

// Prototypes des fonctions pour listes chaînées
void afficher_liste(Node *head);
void tri_bulle_liste(Node *head, int *nbComp, int *nbPerm);
Node *tri_insertion_liste(Node *head, int *nbComp, int *nbPerm);

// Prototypes des fonctions pour matrices
void afficher_matrice(char mat[][MAX_COLS], int lignes);
void tri_bulle_matrice(char mat[][MAX_COLS], int lignes, int *nbComp, int *nbPerm);
void tri_fusion_matrice(char mat[][MAX_COLS], int gauche, int droit, int *nbComp, int *nbPerm);

// Prototypes des fonctions pour vecteurs
void afficher_tableau(int t[], int n);
void tri_selection(int t[], int n, int *nbComp, int *nbPerm);
void tri_bulle(int t[], int n, int *nbComp, int *nbPerm);
void tri_insertion(int t[], int n, int *nbComp, int *nbPerm);
void tri_fusion(int t[], int gauche, int droit, int *nbComp, int *nbPerm);
void tri_rapide(int t[], int low, int high, int *nbComp, int *nbPerm);
void tri_peigne(int t[], int n, int *nbComp, int *nbPerm);

// [Insérer ici toutes les implémentations des fonctions des trois fichiers]

int main() {
    int choix_structure;
    
    do {
        printf("\n=== Menu Principal ===\n");
        printf("1. Tri de liste chainee\n");
        printf("2. Tri de matrice\n");
        printf("3. Tri de vecteur\n");
        printf("4. Quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choix_structure);

        switch (choix_structure) {
            case 1: {
                // Code pour liste chaînée
                Node *head = NULL, *tail = NULL;
                printf("Entrez les mots (FIN pour terminer):\n");
                while (1) {
                    char buffer[100];
                    scanf("%s", buffer);
                    if (strcmp(buffer, "FIN") == 0) break;

                    Node *newNode = malloc(sizeof(Node));
                    strcpy(newNode->data, buffer);
                    newNode->next = NULL;

                    if (!head) {
                        head = tail = newNode;
                    } else {
                        tail->next = newNode;
                        tail = newNode;
                    }
                }
                
                int choix_tri;
                do {
                    printf("\n--- Menu Tri Liste ---\n");
                    printf("1. Tri bulles\n2. Tri insertion\n3. Retour\n");
                    scanf("%d", &choix_tri);
                    
                    int nbComp = 0, nbPerm = 0;
                    switch (choix_tri) {
                        case 1:
                            tri_bulle_liste(head, &nbComp, &nbPerm);
                            break;
                        case 2:
                            head = tri_insertion_liste(head, &nbComp, &nbPerm);
                            break;
                    }
                    if (choix_tri < 3) {
                        printf("Comparaisons: %d, Permutations: %d\n", nbComp, nbPerm);
                    }
                } while (choix_tri != 3);
                
                // Libération mémoire
                while (head) {
                    Node *temp = head;
                    head = head->next;
                    free(temp);
                }
                break;
            }
            case 2: {
                // Code pour matrice
                char matrice[MAX_ROWS][MAX_COLS];
                int lignes;
                printf("Nombre de lignes: ");
                scanf("%d", getchar(), &lignes);
                
                printf("Entrez les chaines:\n");
                for (int i = 0; i < lignes; i++) {
                    fgets(matrice[i], MAX_COLS, stdin);
                    matrice[i][strcspn(matrice[i], "\n")] = '\0';
                }

                int choix_tri;
                do {
                    printf("\n--- Menu Tri Matrice ---\n");
                    printf("1. Tri bulles\n2. Tri fusion\n3. Retour\n");
                    scanf("%d", &choix_tri);
                    
                    int nbComp = 0, nbPerm = 0;
                    switch (choix_tri) {
                        case 1:
                            tri_bulle_matrice(matrice, lignes, &nbComp, &nbPerm);
                            break;
                        case 2:
                            tri_fusion_matrice(matrice, 0, lignes - 1, &nbComp, &nbPerm);
                            break;
                    }
                    if (choix_tri < 3) {
                        printf("Comparaisons: %d, Permutations: %d\n", nbComp, nbPerm);
                    }
                } while (choix_tri != 3);
                break;
            }
            case 3: {
                // Code pour vecteur
                int n;
                printf("Taille du tableau: ");
                scanf("%d", &n);
                
                int *t = malloc(n * sizeof(int));
                printf("Entrez les %d elements:\n", n);
                for (int i = 0; i < n; i++) {
                    scanf("%d", &t[i]);
                }

                int choix_tri;
                do {
                    printf("\n--- Menu Tri Vecteur ---\n");
                    printf("1. Selection\n2. Bulles\n3. Insertion\n");
                    printf("4. Fusion\n5. Rapide\n6. Peigne\n7. Retour\n");
                    scanf("%d", &choix_tri);
                    
                    int nbComp = 0, nbPerm = 0;
                    switch (choix_tri) {
                        case 1: tri_selection(t, n, &nbComp, &nbPerm); break;
                        case 2: tri_bulle(t, n, &nbComp, &nbPerm); break;
                        case 3: tri_insertion(t, n, &nbComp, &nbPerm); break;
                        case 4: tri_fusion(t, 0, n - 1, &nbComp, &nbPerm); break;
                        case 5: tri_rapide(t, 0, n - 1, &nbComp, &nbPerm); break;
                        case 6: tri_peigne(t, n, &nbComp, &nbPerm); break;
                    }
                    if (choix_tri < 7) {
                        printf("Comparaisons: %d, Permutations: %d\n", nbComp, nbPerm);
                    }
                } while (choix_tri != 7);
                
                free(t);
                break;
            }
        }
    } while (choix_structure != 4);

    return 0;
}