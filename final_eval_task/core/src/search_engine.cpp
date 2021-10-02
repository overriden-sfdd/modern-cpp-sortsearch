#include "search_engine.hpp"

int linear_search(const std::vector<int>& vec, int value, int* comp_num)
{
    for (int i = 0; i < vec.size(); ++i) {
        if (comp_num) ++*comp_num;
        if (value == vec[i]) return i;
    }
    return -1;
}

int binary_search(const std::vector<int>& numbers, int number, int* comp_num)
{
    std::size_t n = numbers.size();
    int l = 0, r = n - 1;

    while (l <= r) {
        if (comp_num) ++*comp_num;
        int m = l + ((r - l) / 2);
        if (numbers[m] == number) { return m + 1; }
        if (numbers[m] > number) { r = m - 1; } else { l = m + 1; }
    }
    return -1;
}
