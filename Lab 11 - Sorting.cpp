// Author: Aayush Keshari
// M Number: M15039880
// Email: kesharah@mail.uc.edu
// -------------------------------------------------------------------------------------------------------
// Lab 11 - Sorting.cpp : This file contains the 'main' function. Program execution begins and ends there.
// -------------------------------------------------------------------------------------------------------

#include <iostream>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <algorithm>

typedef std::chrono::high_resolution_clock Clock;

// Function to generate an array of random integers
void generateRandomArray(int arr[], int size) {
    srand(time(0));
    for (int i = 0; i < size; ++i) {
        arr[i] = rand() % (2 * size);  // Fills random integers between 0 and 2n in the array
    }
}

// Function to print the array
void printArray(int arr[], int size) {
    for (int i = 0; i < size; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

// Sorting functions
void bubbleSort(int arr[], int size) {  // Bubble Sort
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void insertionSort(int arr[], int size) {   // Insertion Sort
    for (int i = 1; i < size; ++i) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }

        arr[j + 1] = key;
    }
}

void merge(int arr[], int low, int mid, int high) {
    int n1 = mid - low + 1;
    int n2 = high - mid;

    int* left = new int[n1];
    int* right = new int[n2];

    for (int i = 0; i < n1; ++i) {
        left[i] = arr[low + i];
    }

    for (int j = 0; j < n2; ++j) {
        right[j] = arr[mid + 1 + j];
    }

    int i = 0, j = 0, k = low;
    while (i < n1 && j < n2) {
        if (left[i] <= right[j]) {
            arr[k] = left[i];
            ++i;
        }
        else {
            arr[k] = right[j];
            ++j;
        }
        ++k;
    }

    while (i < n1) {
        arr[k] = left[i];
        ++i;
        ++k;
    }

    while (j < n2) {
        arr[k] = right[j];
        ++j;
        ++k;
    }

    delete[] left;
    delete[] right;
}

void mergeSort(int arr[], int low, int high) {  // Merge Sort
    if (low < high) {
        int mid = low + (high - low) / 2;
        mergeSort(arr, low, mid);
        mergeSort(arr, mid + 1, high);
        merge(arr, low, mid, high);
    }
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; ++j) {
        if (arr[j] < pivot) {
            ++i;
            std::swap(arr[i], arr[j]);
        }
    }

    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(int arr[], int low, int high) {  // Quick Sort
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main() {
    const int sizes[] = { 10, 100, 500, 5000, 25000, 100000 };
    const int num_runs = 10;

    for (int size : sizes) {
        double total_time_bubble = 0, total_time_insertion = 0, total_time_merge = 0, total_time_quick = 0;

        for (int run = 0; run < num_runs; ++run) {
            int* arr_bubble = new int[size];
            int* arr_insertion = new int[size];
            int* arr_merge = new int[size];
            int* arr_quick = new int[size];

            generateRandomArray(arr_bubble, size);
            std::copy(arr_bubble, arr_bubble + size, arr_insertion);
            std::copy(arr_bubble, arr_bubble + size, arr_merge);
            std::copy(arr_bubble, arr_bubble + size, arr_quick);

            auto t1_bubble = Clock::now();
            bubbleSort(arr_bubble, size);
            auto t2_bubble = Clock::now();
            total_time_bubble += std::chrono::duration_cast<std::chrono::milliseconds>(t2_bubble - t1_bubble).count();

            auto t1_insertion = Clock::now();
            insertionSort(arr_insertion, size);
            auto t2_insertion = Clock::now();
            total_time_insertion += std::chrono::duration_cast<std::chrono::milliseconds>(t2_insertion - t1_insertion).count();

            auto t1_merge = Clock::now();
            mergeSort(arr_merge, 0, size - 1);
            auto t2_merge = Clock::now();
            total_time_merge += std::chrono::duration_cast<std::chrono::milliseconds>(t2_merge - t1_merge).count();

            auto t1_quick = Clock::now();
            quickSort(arr_quick, 0, size - 1);
            auto t2_quick = Clock::now();
            total_time_quick += std::chrono::duration_cast<std::chrono::milliseconds>(t2_quick - t1_quick).count();

            delete[] arr_bubble;
            delete[] arr_insertion;
            delete[] arr_merge;
            delete[] arr_quick;
        }

        std::cout << "Size: " << size << "\n";
        std::cout << "Bubble Sort: " << total_time_bubble / num_runs << " ms\n";
        std::cout << "Insertion Sort: " << total_time_insertion / num_runs << " ms\n";
        std::cout << "Merge Sort: " << total_time_merge / num_runs << " ms\n";
        std::cout << "Quick Sort: " << total_time_quick / num_runs << " ms\n";
        std::cout << "------------------------\n";
    }

    return 0;
}
