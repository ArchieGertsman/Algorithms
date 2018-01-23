#include <iostream>
#include <deque> // using deque for `pop_front`
#include <random>

std::deque<int> &append(std::deque<int> &d1, const std::deque<int> &d2) {
    d1.insert(d1.end(), d2.begin(), d2.end());
    return d1;
}

std::deque<int> mergeChunks(std::deque<int> &a, std::deque<int> &b);

std::deque<int> mergeSort(const std::deque<int> &v) {
    std::deque<std::deque<int>> chunks; // in the end, the first element will be the sorted list
    for (const auto &a : v) {
        // add each element of `v` to `arrays` as its own array
        chunks.push_back({ a });
    }

    while (chunks.size() > 1) {
        std::deque<std::deque<int>> tmp; // this will be the new set of chunks at the end of this iteration

        std::size_t i = 0;
        for ( ; i < chunks.size(); i += 2) {
            tmp.push_back(mergeChunks(chunks[i], chunks[i + 1]));
        }

        // if there is an odd number of elements, then add the one that was missed in the for loop to `tmp`
        if (i < chunks.size() - 1) {
            tmp.push_back(chunks[chunks.size() - 1]);
        }

        chunks = tmp;
    }

    return chunks[0];
}

std::deque<int> mergeChunks(std::deque<int> &a, std::deque<int> &b) {
    std::deque<int> ret;
    while (a.size() != 0 && b.size() != 0) {
        // always comparing the first two elements of each chunk. After an element is added
        // to `ret`, pop it from the chunk
        if (a[0] <= b[0]) {
            ret.push_back(a[0]);
            a.pop_front();
        }
        else {
            ret.push_back(b[0]);
            b.pop_front();
        }
    }

    // if all the elemnts of one chunk have been added to `ret` then add the remaining 
    // elements of the other chunk to the end of `ret` (knowing that they're sorted)
    return append(append(ret, b), a);
}

int main() {
    const auto &sorted_list = mergeSort({ 15, 35, 91, 11, 27, 71, 65, 47 });
}
