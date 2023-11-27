#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Define a structure for a doubly linked list node
struct Node {
    double data;
    struct Node* prev;
    struct Node* next;
};

// Function to insert a new node at the end of the doubly linked list
void insertAtEnd(struct Node** head, double data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;

    if (*head == NULL) {
        newNode->prev = NULL;
        *head = newNode;
    } else {
        struct Node* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        newNode->prev = current;
        current->next = newNode;
    }
}

// Function to perform insertion sort on the doubly linked list
void insertionSort(struct Node** head) {
    struct Node* sorted = NULL;
    struct Node* current = *head;

    while (current != NULL) {
        struct Node* next = current->next;

        if (sorted == NULL || current->data <= sorted->data) {
            current->next = sorted;
            current->prev = NULL;
            if (sorted != NULL) {
                sorted->prev = current;
            }
            sorted = current;
        } else {
            struct Node* currentSorted = sorted;
            while (currentSorted->next != NULL && current->data > currentSorted->next->data) {
                currentSorted = currentSorted->next;
            }
            current->next = currentSorted->next;
            current->prev = currentSorted;
            if (currentSorted->next != NULL) {
                currentSorted->next->prev = current;
            }
            currentSorted->next = current;
        }

        current = next;
    }

    *head = sorted;
}

// Function to print the doubly linked list
void printList(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        printf("%.6f ", current->data);
        current = current->next;
    }
    printf("\n");
}

// Function to free the memory of the doubly linked list
void freeList(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        struct Node* temp = current;
        current = current->next;
        free(temp);
    }
}

int main() {
    struct Node* head = NULL;

    // Read data from the file and insert it into the doubly linked list
    FILE* file = fopen("float.txt", "r");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }

    double number;
    while (fscanf(file, "%lf", &number) == 1) {
        insertAtEnd(&head, number);
    }

    fclose(file);

    clock_t start_time = clock();
    insertionSort(&head);
    clock_t end_time = clock();

    double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    // Print the sorted doubly linked list
    printList(head);
    printf("Sorting took %lf seconds to execute.\n", time_taken);

    // Free the memory used by the doubly linked list
    freeList(head);

    return 0;
}
