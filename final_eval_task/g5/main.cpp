#include "sort_engine.hpp"

#include <iostream>
#include <algorithm>
#include <functional>
#include <string>
#include <random>
#include <chrono>
#include <cassert>

template <class Sort>
void test_compare_sorts(std::string&& sort_name, std::vector<int> vec,
    int l, int r, sort_comp_storage* cmp_struct, Sort sorting)
{
    /* Record time. */
    auto t1 = std::chrono::high_resolution_clock::now();
    sorting(vec, l, r, cmp_struct);
    auto t2 = std::chrono::high_resolution_clock::now();

    if (sort_name != "Merge sort") {
        assert(std::is_sorted(vec.begin(), vec.end()));
    }

    /* Getting number of milliseconds as an integer. */
    auto ns_int = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
    cmp_struct->etime_sort += ns_int.count();
    cmp_struct->operations_num = cmp_struct->comp_num + cmp_struct->swap_num;

    std::cout << sort_name << ":\n" << std::string(20, '-')
        << "\nComparisons: " << cmp_struct->comp_num
        << "\nSwaps: " << cmp_struct->swap_num
        << "\nOperations: " << cmp_struct->operations_num
        << "\nElapsed time: " << cmp_struct->etime_sort << "[ms]\n";
}

int main(int argc, char* argv[])
{
    int data_size = 0, print_el_num = 0;
    std::cout << "Enter the data size:\n";
    std::cin >> data_size;
    std::cout << std::endl;
    std::vector<int> vec(data_size);
    vec.reserve(data_size);

    // First create an instance of an engine.
    std::random_device rnd_device;
    // Specify the engine and distribution.
    std::mt19937 mersenne_engine{ rnd_device() };
    // Generates random integers
    std::uniform_int_distribution<int> dist{ 0, std::max(10000, data_size * 10) };

    std::generate_n(vec.begin(), data_size,
        [&dist, &mersenne_engine]() -> int
        { return dist(mersenne_engine); });

    sort_comp_storage insert_data, selection_data, quick_data, merge_data;

    test_compare_sorts("Insertion sort", vec, 0, data_size - 1,
        &insert_data, &insertion_sort);
    std::cout << std::endl << std::endl;

    test_compare_sorts("Selection sort", vec, 0, data_size - 1,
        &selection_data, &selection_sort);
    std::cout << std::endl << std::endl;

    test_compare_sorts("Partition quick sort", vec, 0, data_size - 1,
        &quick_data, &quick3_sort);
    std::cout << std::endl << std::endl;

    test_compare_sorts("Merge sort", vec, 0, data_size - 1,
        &merge_data, &merge_sort);

    // dirty but working solution
    auto res = merge_sort(vec, 0, data_size - 1);
    assert(std::is_sorted(res.begin(), res.end()));

    return 0;
}