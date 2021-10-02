#include <vector>

struct time_comp_storage
{
    double etime_bin = 0.0, etime_linear = 0.0;
    int bin_comp_num = 0, linear_comp_num = 0;
};

/**
 * @brief Linear search
 *
 * @param vec Input vector of integers for search.
 * @param value Integer value we are looking for.
 *
 * @return Position of the element in the given vector.
 **/
int linear_search(const std::vector<int>& vec, int value, int* comp_num = nullptr);

/**
 * @brief Iterative binary search
 *
 * @param numbers Input vector of integers for search.
 * @param number Integer value we are looking for.
 *
 * @return Position of the element in the given vector.
 **/
int binary_search(const std::vector<int>& numbers, int number, int* comp_num = nullptr);
