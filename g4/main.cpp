#include "sort_engine.hpp"

#include <iostream>
#include <random>
#include <algorithm>

int main(int argc, char* argv[])
{
    int data_size = 0, print_el_num = 0;
    std::cout << "Enter the data size and the number of elements to print:\n";
    std::cin >> data_size >> print_el_num;
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

    std::cout << "Before sort:" << std::endl;
    for (auto i = 0; i < std::min(static_cast<int>(vec.size()), print_el_num); ++i) {
        std::cout << vec[i] << ' ';
    }

    quick3_sort(vec, 0, data_size - 1);

    std::cout << "\n\nAfter sort:" << std::endl;
    for (auto i = 0; i < std::min(static_cast<int>(vec.size()), print_el_num); ++i) {
        std::cout << vec[i] << ' ';
    }
    std::cout << std::endl;
    return 0;
}