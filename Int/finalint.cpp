#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Define a structure for a singly linked list node
struct Node {
    int data;
    struct Node* next;
};

// Define a structure for a doubly linked list node
struct DoubleNode {
    int data;
    struct DoubleNode* prev;
    struct DoubleNode* next;
};

// Function declarations
void insertionSort(int A[], int n);
void insertionSortLinkedList(struct Node** head);
void insertionSortDoublyLinkedList(struct DoubleNode** head);
void printArray(int A[], int n);
void printList(struct Node* head);
void printListDoubly(struct DoubleNode* head);
void freeArray(int A[]);
void freeList(struct Node* head);
void freeListDoubly(struct DoubleNode* head);

// Function to insert a new node at the end of the linked list
void insertAtEnd(struct Node** head, int data);

// Function to insert a new node at the end of the doubly linked list
void insertAtEndDoubly(struct DoubleNode** head, int data);

// Function to perform insertion sort on the array
void insertionSort(int A[], int n) {
    int i, j, key;
    for (i = 1; i < n; i++) {
        key = A[i];
        j = i - 1;

        while (j >= 0 && A[j] > key) {
            A[j + 1] = A[j];
            j = j - 1;
        }

        A[j + 1] = key;
    }
}

// Function to perform insertion sort on the linked list
void insertionSortLinkedList(struct Node** head) {
    struct Node* sorted = NULL;
    struct Node* current = *head;

    while (current != NULL) {
        struct Node* next = current->next;

        if (sorted == NULL || current->data <= sorted->data) {
            current->next = sorted;
            sorted = current;
        } else {
            struct Node* currentSorted = sorted;
            while (currentSorted->next != NULL && current->data > currentSorted->next->data) {
                currentSorted = currentSorted->next;
            }
            current->next = currentSorted->next;
            currentSorted->next = current;
        }

        current = next;
    }

    *head = sorted;
}

// Function to perform insertion sort on the doubly linked list
void insertionSortDoublyLinkedList(struct DoubleNode** head) {
    struct DoubleNode* sorted = NULL;
    struct DoubleNode* current = *head;

    while (current != NULL) {
        struct DoubleNode* next = current->next;

        if (sorted == NULL || current->data <= sorted->data) {
            current->next = sorted;
            current->prev = NULL;
            if (sorted != NULL) {
                sorted->prev = current;
            }
            sorted = current;
        } else {
            struct DoubleNode* currentSorted = sorted;
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

// Function to print the sorted array
void printArray(int A[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
}

// Function to print the linked list
void printList(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// Function to print the doubly linked list
void printListDoubly(struct DoubleNode* head) {
    struct DoubleNode* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// Function to free the memory of the array
void freeArray(int A[]) {
    free(A);
}

// Function to free the memory of the linked list
void freeList(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        struct Node* temp = current;
        current = current->next;
        free(temp);
    }
}

// Function to free the memory of the doubly linked list
void freeListDoubly(struct DoubleNode* head) {
    struct DoubleNode* current = head;
    while (current != NULL) {
        struct DoubleNode* temp = current;
        current = current->next;
        free(temp);
    }
}

// Function to insert a new node at the end of the linked list
void insertAtEnd(struct Node** head, int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
    } else {
        struct Node* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

// Function to insert a new node at the end of the doubly linked list
void insertAtEndDoubly(struct DoubleNode** head, int data) {
    struct DoubleNode* newNode = (struct DoubleNode*)malloc(sizeof(struct DoubleNode));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
    } else {
        struct DoubleNode* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        newNode->prev = current;
        current->next = newNode;
    }
}

int main() {
    int choice;
    struct Node* head = NULL;
    struct DoubleNode* headDoubly = NULL;

    do {
        printf("\nMenu:\n");
        printf("1. Read and Sort Array\n");
        printf("2. Read and Sort Singly Linked List\n");
        printf("3. Read and Sort Doubly Linked List\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
           case 1: {
                FILE* file = fopen("int.txt", "r");
                if (file == NULL) {
                    printf("Error opening the file.\n");
                    return 1;
                }

                int n;
                if (fscanf(file, "%d", &n) != 1) {
                    printf("Error reading the size of the array from the file.\n");
                    fclose(file);
                    return 1;
                }

                int* A = (int*)malloc(n * sizeof(int));

                if (A == NULL) {
                    printf("Memory allocation failed.\n");
                    fclose(file);
                    return 1;
                }

                for (int i = 0; i < n; i++) {
                    if (fscanf(file, "%d", &A[i]) != 1) {
                        printf("Error reading data from the file.\n");
                        fclose(file);
                        freeArray(A);
                        return 1;
                    }
                }

                fclose(file);

                clock_t start_time = clock();
                insertionSort(A, n);
                clock_t end_time = clock();

                double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

                printf("Sorted Array: ");
                printArray(A, n);
                printf("Sorting took %lf seconds to execute.\n", time_taken);

                freeArray(A);
                break;
            }
            case 2: {
                FILE* file = fopen("int.txt", "r");
                if (file == NULL) {
                    printf("Error opening the file.\n");
                    return 1;
                }

                int number;
                while (fscanf(file, "%d", &number) == 1) {
                    insertAtEnd(&head, number);
                }

                fclose(file);

                clock_t start_time = clock();
                insertionSortLinkedList(&head);
                clock_t end_time = clock();

                double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

                printf("Sorted Singly Linked List: ");
                printList(head);
                printf("Sorting took %lf seconds to execute.\n", time_taken);

                freeList(head);
                break;
            }
            case 3: {
                FILE* file = fopen("int.txt", "r");
                if (file == NULL) {
                    printf("Error opening the file.\n");
                    return 1;
                }

                int number;
                while (fscanf(file, "%d", &number) == 1) {
                    insertAtEndDoubly(&headDoubly, number);
                }

                fclose(file);

                clock_t start_time = clock();
                insertionSortDoublyLinkedList(&headDoubly);
                clock_t end_time = clock();

                double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

                printf("Sorted Doubly Linked List: ");
                printListDoubly(headDoubly);
                printf("Sorting took %lf seconds to execute.\n", time_taken);

                freeListDoubly(headDoubly);
                break;
            }
            case 4: {
                printf("Exiting the program.\n");
                break;
            }
            default: {
                printf("Invalid choice. Please enter a valid option.\n");
                break;
            }
        }
    } while (choice != 4);

    return 0;
}
