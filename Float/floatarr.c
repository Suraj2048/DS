#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void insertionSort(double A[], int n) {
    int i, j;
    double x;
    for (i = 1; i < n; i++) {
        x = A[i];
        j = i - 1;
        while (j >= 0 && A[j] > x) {
            A[j + 1] = A[j];
            j--;
        }
        A[j + 1] = x;
    }
}

int main() {
    int n = 0; // Number of elements to read
    FILE *file = fopen("float.txt", "r");

    if (file == NULL) {
        printf("Error opening the file.\n");
        return 1; // Exit with an error code
    }

    // Determine the number of elements in the file
    double number;
    while (fscanf(file, "%lf", &number) == 1) {
        n++;
    }

    // Reset the file pointer to the beginning
    fseek(file, 0, SEEK_SET);

    // Allocate memory for the array
    double *A = (double *)malloc(n * sizeof(double));

    if (A == NULL) {
        printf("Memory allocation failed.\n");
        fclose(file);
        return 1; // Exit with an error code
    }

    // Read the data from the file into the array
    for (int i = 0; i < n; i++) {
        if (fscanf(file, "%lf", &A[i]) != 1) {
            printf("Error reading data from the file.\n");
            fclose(file);
            free(A);
            return 1; // Exit with an error code
        }
    }

    fclose(file);

    clock_t start_time = clock();
    insertionSort(A, n);
    clock_t end_time = clock();

    double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    // Print the sorted array
    for (int i = 0; i < n; i++) {
        printf("%.6f ", A[i]);
    }
    printf("\nSorting took %lf seconds to execute.\n", time_taken);

    // Free the allocated memory
    free(A);

    return 0;
}
