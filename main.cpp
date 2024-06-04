#include <time.h>
#include <ctime>
#include <stdlib.h>
#include <algorithm>
#include <iostream>

using namespace std;

static const int NUMBERS_SIZE = 50000; // Max array size
static const int CLOCKS_PER_MS = CLOCKS_PER_SEC / 1000; // Clock per milliseconds

// Get a random integer
static int genRandInt(int low, int high) {
   return low + rand() % (high - low + 1);
}

// Fill arrays with random integers
static void fillArrays(int arr1[], int arr2[], int arr3[]) {
    for (int i = 0; i < NUMBERS_SIZE; i++){
        arr1[i] = genRandInt(0, NUMBERS_SIZE);
        arr2[i] = arr1[i];
        arr3[i] = arr1[i];
    }
}

// Swap lowIndex and highIndex elements that are in the wrong position
static int Partition(int numbers[], int lowIndex, int highIndex, int pivot) {

    while (true) {

        // Increment lowIndex 
        while (numbers[lowIndex] < pivot) {
            lowIndex++;
        }

        // Decrement highIndex
        while (numbers[highIndex] > pivot) {
            highIndex--;
        }

        // If numbers is partitioned, return
        if (lowIndex >= highIndex) {
            return highIndex;
        }

        // Parition
        else {
            // Swap lowIndex and highIndex elements
            int swap = numbers[lowIndex];
            numbers[lowIndex] = numbers[highIndex];
            numbers[highIndex] = swap;

            // Update low and high index
            lowIndex++;
            highIndex--;
        }
    }

    return highIndex;
}

// Quicksort method using a midpoint as pivot
static void Quicksort_midpoint(int numbers[], int lowIndex, int highIndex) {

    if (lowIndex >= highIndex) return;

    int pivot = numbers[(lowIndex + highIndex) / 2];
    int lowEndIndex = Partition(numbers, lowIndex, highIndex, pivot);

    Quicksort_midpoint(numbers, lowIndex, lowEndIndex);
    Quicksort_midpoint(numbers, lowEndIndex + 1, highIndex);
}

// Quicksort method using a median of three numbers: first, middle, last
static void Quicksort_medianOfThree(int numbers[], int lowIndex, int highIndex) {

    if (lowIndex >= highIndex) return;

    int midIndex = (lowIndex + highIndex) / 2;
    int pivot = max(min(numbers[lowIndex], numbers[midIndex]), min(max(numbers[lowIndex], numbers[midIndex]), numbers[highIndex]));
    int lowEndIndex = Partition(numbers, lowIndex, highIndex, pivot);

    Quicksort_medianOfThree(numbers, lowIndex, lowEndIndex);
    Quicksort_medianOfThree(numbers, lowEndIndex + 1, highIndex);
}

// Insertion sort method 
static void InsertionSort(int numbers[], int numbersSize) {
    
    int swap; // Temp swap variable
    int j; // Keep track of what to swap

    for (int i = 1; i < numbersSize; i++) {
        
        // j follows i
        j = i;

        // Swap if j is greater than j - 1
        while (j > 0 && numbers[j] < numbers[j - 1]) {

            swap = numbers[j];
            numbers[j] = numbers[j-1];
            numbers[j - 1] = swap;
            j--;
        }
    }
}

// Check if the array is sorted
static bool is_sorted(int numbers[], int numbersSize) {

    if (numbersSize <= 0) return true;

    int last = numbers[0];

    for (int i = 0; i < numbersSize; i++) {

        int curr = numbers[i];
        if (curr < last) return false;

        last = curr;
    }

    return true;
}

int main() {

    // Arrays for each sorting algorithm
    int quicksortMidPointArray[NUMBERS_SIZE];
    int quicksortMedianArray[NUMBERS_SIZE];
    int InsertionSortArray[NUMBERS_SIZE];

    /*
    Test already sorted array
    
    int sortedArray[NUMBERS_SIZE];
    for (int i=0; i< NUMBERS_SIZE; i++) {
        sortedArray[i] = i;
    }
    */

    // Generate random integers to fill the arrays
    fillArrays(quicksortMidPointArray, quicksortMedianArray, InsertionSortArray);

    // Measure time for quicksort midpoint
    clock_t Start = clock();
    Quicksort_midpoint(quicksortMidPointArray, 0, NUMBERS_SIZE - 1);
    clock_t End = clock();
    int elapsedTime = (End - Start)/CLOCKS_PER_MS; // converts elapsed time from microseconds to milliseconds.
    cout << "Quick sort midpoint took " << elapsedTime << " seconds." << endl;
    cout << "Quick sort midpoint is " << (is_sorted(quicksortMidPointArray,NUMBERS_SIZE)?"GOOD":"BAD") << endl;

    // Measure time for quicksort median
    Start = clock();
    Quicksort_medianOfThree(quicksortMedianArray, 0, NUMBERS_SIZE - 1);
    End = clock();
    elapsedTime = (End - Start)/CLOCKS_PER_MS; // converts elapsed time from microseconds to milliseconds.
    cout << "Quick sort median took " << elapsedTime << " seconds." << endl;
    cout << "Quick sort median is " << (is_sorted(quicksortMedianArray,NUMBERS_SIZE)?"GOOD":"BAD") << endl;

    // Measure time for insertion sort
    Start = clock();
    InsertionSort(InsertionSortArray, NUMBERS_SIZE);
    End = clock();
    elapsedTime = (End - Start)/CLOCKS_PER_MS; // converts elapsed time from microseconds to milliseconds.
    cout << "Insertion sort took " << elapsedTime << " seconds." << endl;
    cout << "Insertion sort midpoint is " << (is_sorted(InsertionSortArray,NUMBERS_SIZE)?"GOOD":"BAD") << endl;

    return 0;
}