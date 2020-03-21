/**
 *  Become a developer test
 *  Library of functions used in main
 *  March 2019
 */


#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "functions.h"

// Global counter of numbers
long amount_of_nums = 0;

/**
 * Loads in memory a dynamic array of long numbers from text file
 * Takes string with text file name as an argument
 * Returns a pointer to array with loaded data
 */
long* load(const char* name_of_file) {
    // Open text file and check for error
    FILE* numbers_txt = fopen(name_of_file, "r");
    if (!numbers_txt) {
        printf("Unable to open your file (maybe it doesn't exist)\n");
        return NULL;
    }

    // Preparation for loading
    char *buffer = malloc(sizeof(char)*LONG_LONG_MAX_LENGTH);
    long* loaded = NULL;

    // Get numbers string by string
    while (fgets(buffer, LONG_LONG_MAX_LENGTH, numbers_txt)) {

        // Reallocate memory
        if (!loaded)
            loaded = malloc(sizeof(long));
        else 
            loaded = realloc(loaded, (amount_of_nums+1)*sizeof(long));

        // Get integer from string and assign it to current element of array
        *(loaded+amount_of_nums) = atoi(buffer);
        amount_of_nums++;
    }

    free(buffer);
    return loaded;
}

// Returns size of loaded array;
long size (void) {
    return amount_of_nums;
}

/**
 *  Quick sort algorithm
 *  Taken from: https://bit.ly/2UO0mLu
 */
void quick_sort(long *s_arr, long first, long last) {
    if (first < last)
    {
        int left = first, right = last, middle = s_arr[(left + right) / 2];
        do
        {
            while (s_arr[left] < middle) left++;
            while (s_arr[right] > middle) right--;
            if (left <= right)
            {
                int tmp = s_arr[left];
                s_arr[left] = s_arr[right];
                s_arr[right] = tmp;
                left++;
                right--;
            }
        }
        while (left <= right);
        quick_sort(s_arr, first, right);
        quick_sort(s_arr, left, last);
    }
}

/**
 * Swaps two elements
 */
void swap (long *a, long *b) {
    long temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

/**
 *  Returns average value of array
 */
float find_average(long array[], long arr_size) {
    long long sum = 0;
    for (int i = 0; i < arr_size; i++)
        sum += array[i];

    return (float) sum/arr_size;
}

/**
 *  Returns median of array
 */
float find_median (long array[], long arr_size) {
    if ( arr_size%2 )
        return array[arr_size/2];
    else
        return (float) (array[arr_size/2 - 1] + array[arr_size/2] )/2 ;
}
