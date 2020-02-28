#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <functional>
#include <chrono>
#include <algorithm>
#include <numeric>

int quickSelect(const std::vector<int> &nums, int k);
float quickSelectMedian(const std::vector<int> &nums);
float findAverage(const std::vector<int> &nums);
std::pair<int, int> findMinMax(const std::vector<int> &nums);
std::pair<int, int> longestSequence(const std::vector<int> &nums, std::function<bool(int, int)> predicate);

int main()
{
    std::vector<int> numbers;
    std::ifstream file("10m.txt");
    std::string line;

    auto start = std::chrono::high_resolution_clock::now();
    while (std::getline(file, line))
    {
        if (line != "")
            numbers.push_back(std::stoi(line));
    }
    file.close();

    std::pair<int, int> minMax = findMinMax(numbers);
    std::cout << "Maximum: " << minMax.second << std::endl;
    std::cout << "Minimum: " << minMax.first << std::endl;
    std::cout << "Median: " << quickSelectMedian(numbers) << std::endl;
    std::cout << "Average: " << findAverage(numbers) << std::endl;

    std::pair<int, int> longest = longestSequence(numbers, [](int a, int b) { return a < b; });
    std::cout << "Increasing seq length: " << longest.first
              << " (Starts at " << longest.second << " string)" << std::endl;

    longest = longestSequence(numbers, [](int a, int b) { return a > b; });
    std::cout << "Decreasing seq length: " << longest.first
              << " (Starts at " << longest.second << " string)" << std::endl << std::endl;

    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Time elapsed: "
              << (std::chrono::duration_cast<std::chrono::milliseconds>(end - start)).count()
              << "ms" << std::endl;
}

float quickSelectMedian(const std::vector<int> &nums)
{
    if (nums.size() % 2)
        return quickSelect(nums, nums.size() / 2);
    else
        return 0.5 * (quickSelect(nums, nums.size() / 2 - 1) +
                      quickSelect(nums, nums.size() / 2));
}

int quickSelect(const std::vector<int> &nums, int k)
{
    if (nums.size() == 1)
        return nums[0];

    int pivot = nums[nums.size() / 2];
    std::vector<int> lows, highs, pivots;
    for (int i : nums)
    {
        if (i < pivot)
            lows.push_back(i);
        else if (i > pivot)
            highs.push_back(i);
        else
            pivots.push_back(i);
    }

    if (k < lows.size())
        return quickSelect(lows, k);
    else if (k < lows.size() + pivots.size())
        return pivots[0];
    else
        return quickSelect(highs, k - lows.size() - pivots.size());
}

std::pair<int, int> longestSequence(const std::vector<int> &nums, std::function<bool(int, int)> predicate)
{
    int counter = 1;
    int maxLen = 1;
    int prevLen = 1;
    int iLast = 0;

    for (size_t i = 0; i < nums.size(); ++i)
    {
        if (predicate(nums[i - 1], nums[i]))
        {
            counter++;
            if (maxLen < counter)
            {
                maxLen = counter;
                if (maxLen > prevLen)
                {
                    prevLen = maxLen;
                    iLast = i;
                }
            }
        }
        else
        {
            counter = 1;
        }
    }
    // Returns a pair {Length, Start position in file}
    return {maxLen, iLast - maxLen + 2};
}

std::pair<int, int> findMinMax(const std::vector<int> &nums)
{
    int min = nums[0];
    int max = nums[0];

    for (int i : nums)
    {
        if (i > max)
            max = i;
        else if (i < min)
            min = i;
    }
    return {min, max};
}

float findAverage(const std::vector<int> &nums)
{
    long long sum = 0;
    for (int i = 0; i < nums.size(); i++)
        sum += nums[i];
    return (float)sum / nums.size();
}