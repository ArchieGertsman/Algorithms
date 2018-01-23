#include <iostream>
#include <vector>

std::vector<int> &append(std::vector<int> &v1, const std::vector<int> &v2) {
    v1.insert(v1.end(), v2.begin(), v2.end());
    return v1;
}

std::vector<int> quickSort(const std::vector<int> &v) {
    int pivot = v[v.size() / 2];
    std::vector<int> chunk1, chunk2, pivots;

    for (const auto &a : v) {
        if (a == pivot) {
            pivots.push_back(a); continue;
        }
        (a <= pivot ? chunk1 : chunk2).push_back(a);
    }

    if (chunk1.size() > 1) chunk1 = quickSort(chunk1);
    if (chunk2.size() > 1) chunk2 = quickSort(chunk2);

    return append(append(chunk1, pivots), chunk2);
}

int main() {
    const auto &sorted_list = quickSort({ 15, 35, 91, 11, 27, 71, 65, 47 });
}
