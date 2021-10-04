#include "matplotlibcpp.h"
#include "sort_engine.hpp"

#include <iostream>
#include <string>
#include <chrono>
#include <random>
#include <map>
#include <cmath>

namespace plt = matplotlibcpp;

enum class SortType
{
    insertion = 0, selection = 1,
    quick3 = 2, merge = 3
};

template <class Sort>
void write_sort_datapoints(SortType sort_name, std::vector<int> vec,
    std::map<SortType, std::vector<int>>& datapoints, int l, int r, Sort sorting)
{
    /* Record time. */
    auto t1 = std::chrono::high_resolution_clock::now();
    sorting(vec, l, r, nullptr);
    auto t2 = std::chrono::high_resolution_clock::now();

    /* Getting number of microseconds as an integer. */
    auto ms_int = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);
    datapoints[sort_name].push_back(ms_int.count());
}

int main(int argc, char* argv[])
{
    std::vector<int> data_sizes =
    { 5000, 7500, 10000, 15000, 20000, 25000, 30000, 35000 };
    std::map<SortType, std::vector<int>> datapoints;

    // Dirty init.
    std::map<SortType, std::string> type2name;
    type2name[SortType::insertion] = "Insertion sort";
    type2name[SortType::selection] = "Selection sort";
    type2name[SortType::quick3] = "Quick3sort";
    type2name[SortType::merge] = "Merge sort";

    // First create an instance of an engine.
    std::random_device rnd_device;
    // Specify the engine and distribution.
    std::mt19937 mersenne_engine{ rnd_device() };
    // Generates random integers
    std::uniform_int_distribution<int> dist{ 0, 10000 };

    for (auto&& data_size : data_sizes) {
        std::vector<int> vec(data_size);
        vec.reserve(data_size);

        std::generate_n(vec.begin(), data_size,
            [&dist, &mersenne_engine]() -> int
            { return dist(mersenne_engine); });

        write_sort_datapoints(SortType::insertion, vec,
            datapoints, 0, data_size - 1, &insertion_sort);

        write_sort_datapoints(SortType::selection, vec,
            datapoints, 0, data_size - 1, &selection_sort);

        write_sort_datapoints(SortType::quick3, vec,
            datapoints, 0, data_size - 1, &quick3_sort);

        write_sort_datapoints(SortType::merge, vec,
            datapoints, 0, data_size - 1, &merge_sort);
    }

    // Set the size of output image to 1200x780 pixels
    plt::figure_size(1200, 780);

    for (auto& pair : type2name) {
        auto sort_type = pair.first;
        auto sort_name = pair.second;
        // Plot line from given x and y data. Color is selected automatically.
        plt::named_plot(sort_name, data_sizes, datapoints[sort_type]);
        // Plot a line whose name will show up as "log(x)" in the legend.
    }

    // Set x-axis to display interval.
    plt::xlim(*data_sizes.begin(), data_sizes.back());
    // Set y-axis to display interval.
    auto quick3_res = datapoints[SortType::quick3];
    auto max_y_val = *std::max_element(quick3_res.begin(), quick3_res.end());
    plt::ylim(0, max_y_val * 100);

    plt::xlabel("Data amount");
    plt::ylabel("Microseconds");
    // Add graph title
    plt::title("Time in microseconds");
    // Enable legend.
    plt::legend();
    // Save the image (file format is determined by the extension)
    plt::save("./performance.png");
    plt::show();
    return 0;
}