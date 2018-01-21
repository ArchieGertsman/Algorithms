#include <iostream>
#include <deque> // using deque for `pop_front`
#include <random>

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
        while (i < chunks.size()) {
            tmp.push_back(mergeChunks(chunks[i], chunks[i + 1]));
            i += 2;
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
    ret.insert(ret.end(), b.begin(), b.end());
    ret.insert(ret.end(), a.begin(), a.end());

    return ret;
}

int randomNum(int min, int max) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(min, max);
    return dist(mt);
}

std::deque<int> randomList(int len, int min, int max) {
    std::deque<int> ret;
    for (int i = 0; i < len; ++i) {
        ret.push_back(randomNum(min, max));
    }
    return ret;
}

int main() {
    for (int i = 0; i < 5; ++i) {
        auto list = randomList(8, 1, 100);
        for (const auto &a : list) {
            std::cout << a << " ";
        }

        std::cout << '\n';

        list = mergeSort(list);
        for (const auto &a : list) {
            std::cout << a << " ";
        }

        std::cout << "\n\n";
    }
}

int main() {
    auto sorted_list = quickSort({ 15, 35, 91, 11, 27, 71, 65, 47 });
}