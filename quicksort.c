// compilar con el sgte comando: gcc -O3 -march=native -flto -funroll-loops -o quicksort quicksort.c

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

inline void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

inline int medianOfThree(int arr[], int low, int high) {
    int mid = low + (high - low) / 2;
    if (arr[low] > arr[mid]) swap(&arr[low], &arr[mid]);
    if (arr[low] > arr[high]) swap(&arr[low], &arr[high]);
    if (arr[mid] > arr[high]) swap(&arr[mid], &arr[high]);
    return mid;
}

inline int partition(int arr[], int low, int high) {
    int pivotIndex = medianOfThree(arr, low, high);
    int pivotValue = arr[pivotIndex];
    swap(&arr[pivotIndex], &arr[high]); 
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (arr[j] < pivotValue) {
            ++i;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]); 
    return i + 1;
}


inline void sort(int arr[], int low, int high) {
    for (int i = low + 1; i <= high; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= low && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}


void quickSort(int arr[], int low, int high) {
    while (low < high) {
       
        if (high - low < 10) {
            sort(arr, low, high);
            break;
        } else {
            int pi = partition(arr, low, high);

            
            if (pi - low < high - pi) {
                quickSort(arr, low, pi - 1);
                low = pi + 1;
            } else {
                quickSort(arr, pi + 1, high);
                high = pi - 1;
            }
        }
    }
}


void shuffleArray(int arr[], int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        swap(&arr[i], &arr[j]);
    }
}

// Benchmark QuickSort function
void benchmarkQuickSort(int arr[], int n) {
    shuffleArray(arr, n);

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    quickSort(arr, 0, n - 1);

    clock_gettime(CLOCK_MONOTONIC, &end);
    double duration = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

    printf("Execution time: %f seconds\n", duration);
    printf("Memory usage: %lu bytes\n", sizeof(int) * n);
}

int main() {
    srand(time(NULL));

    int small[100], medium[300], large[500];

    // Fill the arrays with random integers
    for (int i = 0; i < 100; ++i) small[i] = rand() % 1000;
    for (int i = 0; i < 300; ++i) medium[i] = rand() % 1000;
    for (int i = 0; i < 500; ++i) large[i] = rand() % 1000;

    printf("Small array (100 elements):\n");
    benchmarkQuickSort(small, 100);

    printf("\nMedium array (300 elements):\n");
    benchmarkQuickSort(medium, 300);

    printf("\nLarge array (500 elements):\n");
    benchmarkQuickSort(large, 500);

    return 0;
}
