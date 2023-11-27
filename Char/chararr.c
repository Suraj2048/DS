#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Function to perform insertion sort on an array of characters
void insertionSort(char A[], int n) {
    for (int i = 1; i < n; i++) {
        char x = A[i];
        int j = i - 1;
        while (j >= 0 && A[j] > x) {
            A[j + 1] = A[j];
            j--;
        }
        A[j + 1] = x;
    }
}

int main() {
    char A[100024];  // Array to store characters
    int n = 0;

    // Read data from the file and insert it into the array
    FILE* file = fopen("char.txt", "r");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }

    while (fscanf(file, " %c", &A[n]) == 1) {
        n++;
    }

    fclose(file);

    clock_t start_time = clock();
    insertionSort(A, n);
    clock_t end_time = clock();

    double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    // Print the sorted array of characters
    for (int i = 0; i < n; i++) {
        printf("%c ", A[i]);
    }
    printf("\nSorting took %lf seconds to execute.\n", time_taken);

    return 0;
}
