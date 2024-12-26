#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_ROWS 100
#define MAX_COLS 100
// Fonction pour échanger deux éléments
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
// Affichage d'une matrice
void afficher_matrice(char mat[][MAX_COLS], int lignes)
{
    for (int i = 0; i < lignes; i++)
    {
        printf("%s\n", mat[i]);
    }
}
// Tri à bulles pour une matrice (tri des lignes en ordre alphabétique)
void tri_bulle_matrice(char mat[][MAX_COLS], int lignes, int *nbComp, int *nbPerm)
{
    for (int i = 0; i < lignes - 1; i++)
    {
        for (int j = 0; j < lignes - i - 1; j++)
        {
            (*nbComp)++;
            if (strcmp(mat[j], mat[j + 1]) > 0)
            {
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
void fusion_matrice(char mat[][MAX_COLS], int gauche, int milieu, int droit, int *nbComp, int *nbPerm)
{
    int n1 = milieu - gauche + 1; // Taille de la partie gauche
    int n2 = droit - milieu;      // Taille de la partie droite
    char gaucheMat[n1][MAX_COLS], droiteMat[n2][MAX_COLS];

    // Copie des sous-matrices gauche et droite
    for (int i = 0; i < n1; i++)
        strncpy(gaucheMat[i], mat[gauche + i], MAX_COLS);
    for (int j = 0; j < n2; j++)
        strncpy(droiteMat[j], mat[milieu + 1 + j], MAX_COLS);

    int i = 0, j = 0, k = gauche; // Pointeurs pour gaucheMat, droiteMat et mat

    // Fusion des deux sous-matrices
    while (i < n1 && j < n2)
    {
        (*nbComp)++;
        if (strcmp(gaucheMat[i], droiteMat[j]) <= 0)
        {
            strncpy(mat[k], gaucheMat[i], MAX_COLS);
            i++;
        }
        else
        {
            strncpy(mat[k], droiteMat[j], MAX_COLS);
            j++;
            (*nbPerm)++;
        }
        k++;
    }

    // Copie des éléments restants de gaucheMat
    while (i < n1)
    {
        strncpy(mat[k], gaucheMat[i], MAX_COLS);
        i++;
        k++;
    }

    // Copie des éléments restants de droiteMat
    while (j < n2)
    {
        strncpy(mat[k], droiteMat[j], MAX_COLS);
        j++;
        k++;
    }
}
// Tri fusion pour matrice
void tri_fusion_matrice(char mat[][MAX_COLS], int gauche, int droit, int *nbComp, int *nbPerm)
{
    if (gauche < droit)
    {
        int milieu = gauche + (droit - gauche) / 2;
        tri_fusion_matrice(mat, gauche, milieu, nbComp, nbPerm);
        tri_fusion_matrice(mat, milieu + 1, droit, nbComp, nbPerm);
        fusion_matrice(mat, gauche, milieu, droit, nbComp, nbPerm);

        printf("Etat apres l'iteration:\n");
        afficher_matrice(mat, droit + 1);
    }
}

typedef struct Node
{
    char data[100];
    struct Node *next;
} Node;
// Fonction pour afficher la liste
void afficher_liste(Node *head)
{
    while (head != NULL)
    {
        printf("%s -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}
// Tri à bulles pour liste chaînée
void tri_bulle_liste(Node *head, int *nbComp, int *nbPerm)
{
    if (!head)
        return;
    bool swapped;
    Node *ptr;
    do
    {
        swapped = false;
        ptr = head;
        while (ptr->next != NULL)
        {
            (*nbComp)++;
            if (strcmp(ptr->data, ptr->next->data) > 0)
            {
                char temp[100];
                strcpy(temp, ptr->data);
                strcpy(ptr->data, ptr->next->data);
                strcpy(ptr->next->data, temp);
                (*nbPerm)++;
                afficher_liste(head);
                swapped = true;
            }
            ptr = ptr->next;
        }
    } while (swapped);
}
// Tri par insertion pour liste chaînée
Node *tri_insertion_liste(Node *head, int *nbComp, int *nbPerm)
{
    if (!head)
        return NULL;

    Node *sorted = NULL;

    while (head != NULL)
    {
        Node *current = head;
        head = head->next;
        if (sorted == NULL || strcmp(sorted->data, current->data) >= 0)
        {
            current->next = sorted;
            sorted = current;
        }
        else
        {
            Node *temp = sorted;
            while (temp->next != NULL && strcmp(temp->next->data, current->data) < 0)
            {
                (*nbComp)++;
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
        (*nbPerm)++;
        afficher_liste(head);
    }

    return sorted;
}

// Fonction pour afficher un tableau
void afficher_tableau(int t[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", t[i]);
    }
    printf("\n");
}
// Tri par sélection
void tri_selection(int t[], int n, int *nbComp, int *nbPerm)
{
    for (int i = 0; i < n - 1; i++)
    {
        int k = i;
        for (int j = i + 1; j < n; j++)
        {
            (*nbComp)++; // Comparaison
            if (t[j] < t[k])
            {
                k = j;
            }
        }
        if (k != i)
        {
            swap(&t[k], &t[i]);
            (*nbPerm)++; // Permutation
        }
        printf("État après l'itération %d : ", i + 1);
        afficher_tableau(t, n);
    }
}
// Tri à bulles
void tri_bulle(int t[], int n, int *nbComp, int *nbPerm)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            (*nbComp)++; // Comparaison
            if (t[j] > t[j + 1])
            {
                swap(&t[j], &t[j + 1]);
                (*nbPerm)++; // Permutation
            }
        }
        printf("État après l'itération %d : ", i + 1);
        afficher_tableau(t, n);
    }
}
// Tri par insertion
void tri_insertion(int t[], int n, int *nbComp, int *nbPerm)
{
    for (int i = 1; i < n; i++)
    {
        int k = t[i];
        int j = i - 1;
        while (j >= 0 && t[j] > k)
        {
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
void fusion(int t[], int gauche, int milieu, int droit, int *nbComp, int *nbPerm)
{
    int n1 = milieu - gauche + 1;
    int n2 = droit - milieu;
    int L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = t[gauche + i];
    for (int j = 0; j < n2; j++)
        R[j] = t[milieu + 1 + j];

    int i = 0, j = 0, k = gauche;
    while (i < n1 && j < n2)
    {
        (*nbComp)++;
        if (L[i] <= R[j])
        {
            t[k++] = L[i++];
        }
        else
        {
            t[k++] = R[j++];
        }
        (*nbPerm)++;
        // Afficher l'état du tableau après chaque insertion dans t
        afficher_tableau(t, droit + 1);
    }

    while (i < n1)
    {
        t[k++] = L[i++];
        (*nbPerm)++;
        afficher_tableau(t, droit + 1);
    }

    while (j < n2)
    {
        t[k++] = R[j++];
        (*nbPerm)++;
        afficher_tableau(t, droit + 1);
    }
}
void tri_fusion(int t[], int gauche, int droit, int *nbComp, int *nbPerm)
{
    if (gauche < droit)
    {
        int milieu = gauche + (droit - gauche) / 2;
        tri_fusion(t, gauche, milieu, nbComp, nbPerm);
        tri_fusion(t, milieu + 1, droit, nbComp, nbPerm);
        fusion(t, gauche, milieu, droit, nbComp, nbPerm);
    }
}
// Tri rapide
void tri_rapide(int t[], int low, int high, int *nbComp, int *nbPerm)
{
    if (low < high)
    {
        int pivot = t[high];
        int i = low - 1;

        for (int j = low; j < high; j++)
        {
            (*nbComp)++;
            if (t[j] < pivot)
            {
                i++;
                swap(&t[i], &t[j]);
                (*nbPerm)++;
                afficher_tableau(t, high + 1);
            }
        }
        swap(&t[i + 1], &t[high]);
        (*nbPerm)++;
        afficher_tableau(t, high);
        int pi = i + 1;

        tri_rapide(t, low, pi - 1, nbComp, nbPerm);
        tri_rapide(t, pi + 1, high, nbComp, nbPerm);
    }
}
// Tri peigne
void tri_peigne(int t[], int n, int *nbComp, int *nbPerm)
{
    int gap = n;
    bool swapped = true;

    while (gap > 1 || swapped)
    {
        gap = (gap * 10) / 13;
        if (gap < 1)
            gap = 1;

        swapped = false;
        for (int i = 0; i < n - gap; i++)
        {
            (*nbComp)++;
            if (t[i] > t[i + gap])
            {
                swap(&t[i], &t[i + gap]);
                (*nbPerm)++;
                afficher_tableau(t, n);
                swapped = true;
            }
        }
    }
}

int main()
{
    int choix_structure;
    do
    {
        printf("\n=== Menu Principal ===\n");
        printf("1. Tri de liste chainee\n");
        printf("2. Tri de matrice\n");
        printf("3. Tri de vecteur\n");
        printf("4. Quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choix_structure);

        switch (choix_structure)
        {
        case 1:
        {
            int choix, nbComp = 0, nbPerm = 0;
            Node *head = NULL, *tail = NULL;

            printf("Entrez les mots pour la liste chainee (entrez \"FIN\" pour arreter) :\n");
            while (true)
            {
                char buffer[100];
                scanf("%s", buffer);

                if (strcmp(buffer, "FIN") == 0)
                    break;

                Node *newNode = (Node *)malloc(sizeof(Node));
                strcpy(newNode->data, buffer);
                newNode->next = NULL;

                if (!head)
                {
                    head = newNode;
                    tail = newNode;
                }
                else
                {
                    tail->next = newNode;
                    tail = newNode;
                }
            }

            do
            {
                printf("\n--- Menu Tri pour Liste Chaînée ---\n");
                printf("1. Tri à bulles\n");
                printf("2. Tri par insertion\n");
                printf("3. Quitter\n");
                printf("Votre choix : ");
                scanf("%d", &choix);

                nbComp = 0;
                nbPerm = 0;

                switch (choix)
                {
                case 1:
                    printf("\nTri a bulles :\n");
                    tri_bulle_liste(head, &nbComp, &nbPerm);
                    afficher_liste(head);
                    break;
                case 2:
                    printf("\nTri par insertion :\n");
                    head = tri_insertion_liste(head, &nbComp, &nbPerm);
                    afficher_liste(head);
                    break;
                case 3:
                    printf("Au revoir !\n");
                    break;
                default:
                    printf("Choix invalide.\n");
                }

                if (choix == 1 || choix == 2)
                {
                    printf("Nombre de comparaisons : %d\n", nbComp);
                    printf("Nombre de permutations : %d\n", nbPerm);
                }
            } while (choix != 3);

            // Libération de la mémoire
               while (head)
                {
                  Node *temp = head;
                  head = head->next;
                  free(temp);
                }

        break;
        }
        case 2:
        {
            int choix, nbComp, nbPerm, lignes;
            char matrice[MAX_ROWS][MAX_COLS];

            printf("Entrez le nombre de lignes de la matrice  : ");
            if (scanf("%d", &lignes) != 1 || lignes <= 0 || lignes > MAX_ROWS)
            {
                printf("Nombre de lignes invalide.\n");
                return 1;
            }
            getchar(); // pour consommer le caractère '\n' restant

            printf("Entrez les chaines de caracteres ");
            for (int i = 0; i < lignes; i++)
            {
                if (!fgets(matrice[i], MAX_COLS, stdin))
                {
                    printf("Erreur de lecture.\n");
                    return 1;
                }
                matrice[i][strcspn(matrice[i], "\n")] = '\0'; // Supprime le '\n'
            }

            do
            {
                printf("\n--- Menu Tri pour Matrice ---\n");
                printf("1. Tri a bulles\n");
                printf("2. Tri fusion\n");
                printf("3. Quitter\n");
                printf("Votre choix : ");
                if (scanf("%d", &choix) != 1)
                {
                    printf("Erreur de saisie.\n");
                    break;
                }
                getchar(); // Consomme '\n'
                nbComp = 0;
                nbPerm = 0;
                switch (choix)
                {
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

                if (choix == 1 || choix == 2)
                {
                    printf("Nombre de comparaisons : %d\n", nbComp);
                    printf("Nombre de permutations : %d\n", nbPerm);
                }
            } while (choix != 3);

         break;
        }
        case 3:
        {
            // Code pour vecteur
            int choix, n, nbComp, nbPerm;
            printf("Entrez la taille du tableau : ");
            scanf("%d", &n);
            if (n <= 0)
            {
                printf("La taille du tableau doit etre positive.\n");
                return 1;
            }
            int *t = (int *)malloc(n * sizeof(int));
            if (t == NULL)
            {
                printf("Erreur d'allocation memoire.\n");
                return 1;
            }
            int *original = (int *)malloc(n * sizeof(int));
            printf("Entrez les %d elements du tableau :\n", n);
            for (int i = 0; i < n; i++)
            {
                scanf("%d", &t[i]);
                original[i] = t[i];
            }

            do
            {
                printf("\n--- Menu des algorithmes de tri ---\n");
                printf("1. Tri par selection\n");
                printf("2. Tri a bulles\n");
                printf("3. Tri par insertion\n");
                printf("4. Tri fusion\n");
                printf("5. Tri rapide\n");
                printf("6. Tri peigne\n");
                printf("7. Quitter\n");
                printf("Votre choix : ");
                scanf("%d", &choix);
                nbComp = 0;
                nbPerm = 0;

                switch (choix)
                {
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

                if (choix >= 1 && choix <= 6)
                {
                    printf("Nombre de comparaisons : %d\n", nbComp);
                    printf("Nombre de permutations : %d\n", nbPerm);
                }
            } while (choix != 7);

            free(t);
            break;
        }
        }
    } while (choix_structure != 4);

    return 0;
}