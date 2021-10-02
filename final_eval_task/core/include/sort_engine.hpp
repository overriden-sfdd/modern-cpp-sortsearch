#include <vector>

/* for merge sort swap_num increments for each item
    copied from subvector to final vector */
struct sort_comp_storage
{
    double etime_sort = 0.0;
    long comp_num = 0, swap_num = 0, operations_num = 0;
};

/*
    Sort algorithm for group 3.
*/

/**
 * @brief In-place insertion sort.
 *
 * @param vec Input vector of integers to sort.
 **/
void insertion_sort(std::vector<int>& vec, int l,
    int r, sort_comp_storage* cmp_struct = nullptr);

/*
    Sort algorithm for group 4.
*/

/**
 * @brief In-place insertion sort.
 *
 * @param vec Input vector of integers to sort.
 * @param l Range start.
 * @param r Range end.
 *
 * @returns Partition pair used for quick sorting.
 **/
std::pair<int, int> partition(std::vector<int>& vec, int l,
    int r, sort_comp_storage* cmp_struct = nullptr);

/**
 * @brief In-place quick sort.
 *
 * @param vec Input vector of integers to sort.
 * @param l Sort range start.
 * @param r Sort range end.
 **/
void quick3_sort(std::vector<int>& vec, int l,
    int r, sort_comp_storage* cmp_struct = nullptr);

/*
    Sort algorithms for group 5.
*/

/**
 * @brief In-place selection sort (n*n)
 *
 * @param vec Input vector of integers to sort.
 */
void selection_sort(std::vector<int>& vec, int l,
    int r, sort_comp_storage* cmp_struct = nullptr);

/* Merge sort helper function */
std::vector<int> merge(std::vector<int> lhs, std::vector<int> rhs,
    sort_comp_storage* cmp_struct = nullptr);

/**
 * @brief Merge sort (n*log(n)).
 *
 * @param vec Input vector of integers to sort.
 * @param l Sort range start.
 * @param r Sort range end.
 *
 * @returns Sorted vector of integers.
 **/
std::vector<int> merge_sort(std::vector<int>& vec, int l,
    int r, sort_comp_storage* cmp_struct = nullptr);
