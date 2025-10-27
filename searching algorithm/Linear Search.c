#include <stdio.h>

// Function to perform Linear Search
int linearSearch(int arr[], int n, int key) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == key) {
            return i; // Return index if element is found
        }
    }
    return -1; // Return -1 if element not found
}

int main() {
    int arr[] = {10, 25, 30, 45, 50, 75};
    int n = sizeof(arr) / sizeof(arr[0]);
    int key;

    printf("Enter the element to search: ");
    scanf("%d", &key);

    int result = linearSearch(arr, n, key);

    if (result == -1)
        printf("Element %d not found in the array.\n", key);
    else
        printf("Element %d found at position %d.\n", key, result + 1); // +1 for 1-based index

    return 0;
}
