#include "search_engine.hpp"

#include <iostream>
#include <algorithm>
#include <string>
#include <chrono>

void test_compare_searches(const std::vector<int>& vec, int repetitions,
    std::uint8_t is_successful, time_comp_storage* timings)
{
    for (auto i = repetitions; i > 0; --i) {

        int value =
            is_successful ? abs(2 * std::rand() + 1) % vec.size()
            : abs(2 * std::rand()) % vec.size();

        /* Record time. */
        auto t1 = std::chrono::high_resolution_clock::now();
        binary_search(vec, value, &timings->bin_comp_num);
        auto t2 = std::chrono::high_resolution_clock::now();

        /* Getting number of nanoseconds as an integer. */
        auto ns_int = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1);
        timings->etime_bin += ns_int.count() / repetitions;

        /* Record time. */
        auto tt1 = std::chrono::high_resolution_clock::now();
        linear_search(vec, value, &timings->linear_comp_num);
        auto tt2 = std::chrono::high_resolution_clock::now();

        /* Getting number of nanoseconds as an integer. */
        auto ns_int_lin = std::chrono::duration_cast<std::chrono::nanoseconds>(tt2 - tt1);
        timings->etime_linear += ns_int_lin.count() / repetitions;
    }
    timings->linear_comp_num /= repetitions;
    timings->bin_comp_num /= repetitions;
}

int main(int argc, char* argv[])
{
    auto data_size = 0, repetitions = 0, key = 0, i = -1;
    std::cout << "Enter the data size and the number of repetitions:\n";
    std::cin >> data_size >> repetitions;
    std::cout << std::endl;
    std::vector<int> vec(data_size);
    vec.reserve(data_size);
    std::generate_n(vec.begin(), data_size,
        [&i]() -> int { return i += 2; });

    time_comp_storage successful_timings;
    test_compare_searches(vec, repetitions, 1, &successful_timings);

    time_comp_storage unsuccessful_timings;
    test_compare_searches(vec, repetitions, 0, &unsuccessful_timings);

    std::cout << "Linear search:\n" << std::string(20, '-')
        << "\nStatus: Successful\n" << "Elapsed per search: "
        << successful_timings.etime_linear << "[ns]\n"
        << "Comparisons per search: " << successful_timings.linear_comp_num
        << "\nSearches: " << repetitions << "\n\nStatus: Unsuccessful\n"
        << "Elapsed per search: " << unsuccessful_timings.etime_linear << "[ns]\n"
        << "Comparisons per search: " << unsuccessful_timings.linear_comp_num
        << "\nSearches: " << repetitions << "\n\n\n";

    std::cout << "Iterative binary search:\n" << std::string(30, '-')
        << "\nStatus: Successful\n" << "Elapsed per search: "
        << successful_timings.etime_bin << "[ns]\n"
        << "Comparisons per search: " << successful_timings.bin_comp_num
        << "\nSearches: " << repetitions << "\n\nStatus: Unsuccessful\n"
        << "Elapsed per search: " << unsuccessful_timings.etime_bin << "[ns]\n"
        << "Comparisons per search: " << unsuccessful_timings.bin_comp_num
        << "\nSearches: " << repetitions << std::endl;

    return 0;
}