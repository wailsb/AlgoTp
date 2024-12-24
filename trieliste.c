#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Node {
    char data[100];
    struct Node *next;
} Node;

// Fonction pour afficher la liste
void afficher_liste(Node *head) {
    while (head != NULL) {
        printf("%s -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

// Tri à bulles pour liste chaînée
void tri_bulle_liste(Node *head, int *nbComp, int *nbPerm) {
    if (!head) return;
    bool swapped;
    Node *ptr;
    do {
        swapped = false;
        ptr = head;
        while (ptr->next != NULL) {
            (*nbComp)++;
            if (strcmp(ptr->data, ptr->next->data) > 0) {
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
Node *tri_insertion_liste(Node *head, int *nbComp, int *nbPerm) {
    if (!head) return NULL;

    Node *sorted = NULL;

    while (head != NULL) {
        Node *current = head;
        head = head->next;
        if (sorted == NULL || strcmp(sorted->data, current->data) >= 0) {
            current->next = sorted;
            sorted = current;
        } else {
            Node *temp = sorted;
            while (temp->next != NULL && strcmp(temp->next->data, current->data) < 0) {
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

int main() {
    int choix, nbComp = 0, nbPerm = 0;
    Node *head = NULL, *tail = NULL;

    printf("Entrez les mots pour la liste chainee (entrez \"FIN\" pour arreter) :\n");
    while (true) {
        char buffer[100];
        scanf("%s", buffer);

        if (strcmp(buffer, "FIN") == 0) break;

        Node *newNode = (Node *)malloc(sizeof(Node));
        strcpy(newNode->data, buffer);
        newNode->next = NULL;

        if (!head) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    do {
        printf("\n--- Menu Tri pour Liste Chainee ---\n");
        printf("1. Tri a bulles\n");
        printf("2. Tri par insertion\n");
        printf("3. Quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        nbComp = 0;
        nbPerm = 0;

        switch (choix) {
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

        if (choix == 1 || choix == 2) {
            printf("Nombre de comparaisons : %d\n", nbComp);
            printf("Nombre de permutations : %d\n", nbPerm);
        }
    } while (choix != 3);

    // Libération de la mémoire
    while (head) {
        Node *temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}
