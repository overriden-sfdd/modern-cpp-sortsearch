#include "search_engine.hpp"

#include <iostream>
#include <algorithm>

int main(int argc, char* argv[])
{
    auto data_size = 0, key = 0, i = -1;
    std::cout << "Enter the data size:\n";
    std::cin >> data_size;
    std::cout << std::endl;
    std::vector<int> vec(data_size);
    vec.reserve(data_size);
    std::generate_n(vec.begin(), data_size,
        [&i]() -> int { return i += 2; });

    std::cout << "\nEnter the value you are looking for.\n" <<
        "If you want halt the program, enter negative value.\n" << std::endl;

    while (true) {
        std::cin >> key;
        if (key < 0) break;
        auto pos = linear_search(vec, key);
        if (pos >= 0) {
            std::cout << "Search finished successfully. Value " <<
                key << " found on position " << pos << ".\n";
        } else {
            std::cout << "Search failed. Value was not found.\n";
        }
    }

    return 0;
}