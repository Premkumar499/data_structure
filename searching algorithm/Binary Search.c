#include <stdio.h>

// Function to perform Binary Search
int binarySearch(int arr[], int n, int key) {
    int low = 0, high = n - 1;

    while (low <= high) {
        int mid = (low + high) / 2; // Find the middle index

        if (arr[mid] == key)
            return mid;  // Element found, return index
        else if (arr[mid] < key)
            low = mid + 1; // Search in right half
        else
            high = mid - 1; // Search in left half
    }

    return -1; // Element not found
}

int main() {
    int arr[] = {10, 20, 30, 40, 50, 60, 70};
    int n = sizeof(arr) / sizeof(arr[0]);
    int key;

    printf("Enter the element to search: ");
    scanf("%d", &key);

    int result = binarySearch(arr, n, key);

    if (result == -1)
        printf("Element %d not found in the array.\n", key);
    else
        printf("Element %d found at position %d.\n", key, result + 1); // +1 for 1-based index

    return 0;
}
