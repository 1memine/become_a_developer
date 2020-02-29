#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void push_back(int **array, size_t *n, int val);
int quick_select(int nums[], int k, int n);
float quick_select_median(int nums[], size_t n);

int main()
{
    FILE *fp = fopen("10m.txt", "r");
    char *buffer = malloc(16 * sizeof(char));

    int *numbers = NULL;
    size_t n = 0;

    clock_t begin = clock();
    // Load
    while (fgets(buffer, 16, fp))
        push_back(&numbers, &n, atoi(buffer));
    free(buffer);

    long sum = 0;
    int min = numbers[0];
    int max = numbers[0];

    int inc_seq_len = 1;
    int dec_seq_len = 1;

    int prev_inc_seq_len = 1;
    int prev_dec_seq_len = 1;

    int inc_seq_i = 0;
    int dec_seq_i = 0;

    int inc_seq_count = 1;
    int dec_seq_count = 1;
    float med = quick_select_median(numbers, n);

    for (size_t i = 0; i < n; ++i)
    {
        sum += numbers[i];
        if (max < numbers[i])
            max = numbers[i];
        else if (min > numbers[i])
            min = numbers[i];
        if (numbers[(i - 1) % n] < numbers[i])
        {
            dec_seq_count = 1;
            inc_seq_count++;
            if (inc_seq_len < inc_seq_count)
            {
                inc_seq_len = inc_seq_count;
                if (inc_seq_len > prev_inc_seq_len)
                {
                    prev_inc_seq_len = inc_seq_len;
                    inc_seq_i = i;
                }
            }
        }
        else if(numbers[(i - 1) % n] > numbers[i])
        {
            inc_seq_count = 1;
            dec_seq_count++;
            if (dec_seq_len < dec_seq_count)
            {
                dec_seq_len = dec_seq_count;
                if (dec_seq_len > prev_dec_seq_len)
                {
                    prev_dec_seq_len = dec_seq_len;
                    dec_seq_i = i;
                }
            }
        } else {
            inc_seq_count = 1;
            dec_seq_count = 1;
        }
    }
    clock_t end = clock();
    printf("Maximum: %d\n", max);
    printf("Minimum: %d\n", min);
    printf("Median: %f\n", med);
    printf("Average: %f\n", (float)sum/n);
    printf("Increasing seq length: %d (Starts at %d string)\n", inc_seq_len, inc_seq_i - inc_seq_len + 2);
    printf("Decreasing seq length: %d (Starts at %d string)\n\n", dec_seq_len, dec_seq_i - dec_seq_len + 2);

    printf("Time elapsed: %f\n", (double)(end - begin)/CLOCKS_PER_SEC);
    free(numbers);
    fclose(fp);
}

int quick_select(int nums[], int k, int n)
{
    if (n == 1)
        return nums[0];

    int pivot = nums[n / 2];

    int *lows = NULL;
    size_t n_lows = 0;
    int *highs = NULL;
    size_t n_highs = 0;
    int *pivots = NULL;
    size_t n_pivots = 0;

    for (int i = 0; i < n; ++i)
    {
        if (nums[i] < pivot)
            push_back(&lows, &n_lows, nums[i]);
        else if (nums[i] > pivot)
            push_back(&highs, &n_highs, nums[i]);
        else
            push_back(&pivots, &n_pivots, nums[i]);
    }

    if (k < n_lows)
        return quick_select(lows, k, n_lows);
    else if (k < n_lows + n_pivots)
        return pivots[0];
    else
        return quick_select(highs, k - n_lows - n_pivots, n_highs);
}

float quick_select_median(int nums[], size_t n)
{
    if (n % 2)
        return (float)quick_select(nums, n / 2, n);
    else
        return 0.5 * ((float)quick_select(nums, n / 2 - 1, n) +
                      (float)quick_select(nums, n / 2, n));
}

void push_back(int **array, size_t *n, int val)
{
    (*n)++;
    *array = realloc(*array, (*n) * sizeof(int));
    *(*array + (*n) - 1) = val;
}