#include <stdio.h>
#include <stdlib.h>

#define MAX 5   // maximum numbers that can fit into memory (RAM)

// Function to merge two sorted files
void mergeFiles(char *file1, char *file2, char *output) {
    FILE *f1 = fopen(file1, "r");
    FILE *f2 = fopen(file2, "r");
    FILE *out = fopen(output, "w");

    int num1, num2;
    int hasNum1 = fscanf(f1, "%d", &num1);
    int hasNum2 = fscanf(f2, "%d", &num2);

    // Merge like in Merge Sort
    while (hasNum1 == 1 && hasNum2 == 1) {
        if (num1 <= num2) {
            fprintf(out, "%d ", num1);
            hasNum1 = fscanf(f1, "%d", &num1);
        } else {
            fprintf(out, "%d ", num2);
            hasNum2 = fscanf(f2, "%d", &num2);
        }
    }

    // Copy remaining elements
    while (hasNum1 == 1) {
        fprintf(out, "%d ", num1);
        hasNum1 = fscanf(f1, "%d", &num1);
    }

    while (hasNum2 == 1) {
        fprintf(out, "%d ", num2);
        hasNum2 = fscanf(f2, "%d", &num2);
    }

    fclose(f1);
    fclose(f2);
    fclose(out);
}

// Function to sort a small chunk (using simple Bubble Sort)
void sortChunk(int *arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Main function simulating External Sort
int main() {
    FILE *input = fopen("input.txt", "r");
    if (!input) {
        printf("Error: Cannot open input.txt\n");
        return 1;
    }

    int arr[MAX];
    int count = 0, fileCount = 0, num;

    // PHASE 1: Create sorted chunks (runs)
    while (fscanf(input, "%d", &num) == 1) {
        arr[count++] = num;
        if (count == MAX) {
            sortChunk(arr, count);

            char filename[20];
            sprintf(filename, "chunk%d.txt", fileCount++);
            FILE *chunk = fopen(filename, "w");

            for (int i = 0; i < count; i++)
                fprintf(chunk, "%d ", arr[i]);

            fclose(chunk);
            count = 0;
        }
    }

    // Handle remaining numbers
    if (count > 0) {
        sortChunk(arr, count);
        char filename[20];
        sprintf(filename, "chunk%d.txt", fileCount++);
        FILE *chunk = fopen(filename, "w");
        for (int i = 0; i < count; i++)
            fprintf(chunk, "%d ", arr[i]);
        fclose(chunk);
    }

    fclose(input);

    printf("✅ Phase 1 complete: Created %d sorted chunks.\n", fileCount);

    // PHASE 2: Merge chunks pair by pair
    int mergeStep = 0;
    while (fileCount > 1) {
        int newFileCount = 0;

        for (int i = 0; i < fileCount; i += 2) {
            if (i + 1 < fileCount) {
                char file1[20], file2[20], output[20];
                sprintf(file1, "chunk%d.txt", i);
                sprintf(file2, "chunk%d.txt", i + 1);
                sprintf(output, "merged%d.txt", newFileCount++);

                mergeFiles(file1, file2, output);
            } else {
                char file1[20], output[20];
                sprintf(file1, "chunk%d.txt", i);
                sprintf(output, "merged%d.txt", newFileCount++);
                rename(file1, output);
            }
        }

        fileCount = newFileCount;
        mergeStep++;

        // Rename merged files back to chunk files for next round
        for (int i = 0; i < fileCount; i++) {
            char oldName[20], newName[20];
            sprintf(oldName, "merged%d.txt", i);
            sprintf(newName, "chunk%d.txt", i);
            rename(oldName, newName);
        }
    }

    printf("✅ Phase 2 complete: Final sorted output in 'chunk0.txt'\n");

    return 0;
}
