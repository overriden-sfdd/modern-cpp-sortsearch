#include "sort_engine.hpp"

#include <random>
#include <algorithm>
#include <vector>

void insertion_sort(std::vector<int>& vec, int l, int r,
    sort_comp_storage* cmp_struct)
{
    for (auto i = 1 + l; i <= r; ++i) {
        auto val = vec[i];
        for (auto j = i - 1; val < vec[j] && j >= 0; --j) {
            if (cmp_struct) ++cmp_struct->comp_num;
            std::swap(vec[j + 1], vec[j]);
            if (cmp_struct) ++cmp_struct->swap_num;
        }
    }
}

std::pair<int, int> partition(std::vector<int>& vec, int l, int r,
    sort_comp_storage* cmp_struct)
{
    auto random = l + (rand() % static_cast<int>(r - l + 1));
    std::swap(vec[l], vec[random]);

    // for swap in the bottom
    if (cmp_struct) cmp_struct->swap_num += 2;

    auto x = vec[l];
    std::pair<int, int> index = { l, l };
    for (auto i = l + 1; i <= r; ++i) {
        if (vec[i] < x) {
            std::swap(vec[++index.second], vec[i]);
            std::swap(vec[index.second], vec[++index.first]);
            if (cmp_struct) {
                cmp_struct->swap_num += 2;
                ++cmp_struct->comp_num;
            }
        } else if (vec[i] == x) {
            std::swap(vec[++index.second], vec[i]);
            if (cmp_struct) ++cmp_struct->swap_num;
        } else if (cmp_struct) {
            cmp_struct->comp_num += 2;
        }
    }
    std::swap(vec[l], vec[index.first]);
    return index;
}

void quick3_sort(std::vector<int>& vec, int l, int r,
    sort_comp_storage* cmp_struct)
{
    while (l < r) {
        if (cmp_struct) ++cmp_struct->comp_num;
        auto index = partition(vec, l, r, cmp_struct);
        quick3_sort(vec, l, index.first - 1, cmp_struct);
        l = index.second + 1;
    }
}


void selection_sort(std::vector<int>& vec, int l, int r,
    sort_comp_storage* cmp_struct)
{
    // One by one move boundary of unsorted subarray
    for (auto i = l; i < r; ++i)
    {
        // Find the minimum element in unsorted array
        auto min_idx = std::min_element(vec.begin() + i, vec.begin() + r + 1);

        if (cmp_struct) cmp_struct->comp_num += (min_idx - vec.begin() + l);

        // Swap the found minimum element with the first element
        std::swap(vec[i], *min_idx);
        if(cmp_struct) ++cmp_struct->swap_num;
    }
}

std::vector<int> merge(std::vector<int> lhs, std::vector<int> rhs,
    sort_comp_storage* cmp_struct)
{
    std::vector<int> res;
    std::size_t lhs_idx = 0, rhs_idx = 0;
    for (; lhs_idx < lhs.size() && rhs_idx < rhs.size();) {
        if (lhs.at(lhs_idx) <= rhs.at(rhs_idx)) {
            res.push_back(lhs.at(lhs_idx++));
        } else {
            res.push_back(rhs.at(rhs_idx++));
        }
        if (cmp_struct) ++cmp_struct->comp_num;
    }

    if (lhs_idx >= lhs.size()) {
        std::copy(rhs.begin() + rhs_idx, rhs.end(), std::back_inserter(res));
    } else {
        std::copy(lhs.begin() + lhs_idx, lhs.end(), std::back_inserter(res));
    }

    if (cmp_struct) {
        ++cmp_struct->comp_num;
        cmp_struct->swap_num += res.size();
    }

    return res;
}

std::vector<int> merge_sort(std::vector<int>& vec, int l, int r,
    sort_comp_storage* cmp_struct)
{
    if (l < r) {
        if (cmp_struct) ++cmp_struct->comp_num;
        int middle = (l + r) / 2;
        return merge(merge_sort(vec, l, middle, cmp_struct),
            merge_sort(vec, middle + 1, r, cmp_struct), cmp_struct);
    }
    return { vec[l] };
}