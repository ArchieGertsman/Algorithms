#include <iostream>
#include <vector>
#include <algorithm>

// problem: https://open.kattis.com/problems/ants

static double average(double a, double b) {
    return (a + b) / 2.0;
}

static double min(double a, double b) {
    return a < b ? a : b;
}

static double max(double a, double b) {
    return a > b ? a : b;
}

static int shortestTime(const int pole_length, const std::vector<double> &positions) {
    double min_dif = pole_length / 2.0;
    double middle_most_pos = 0;

    for (const auto &pos : positions) {
        int dif = std::abs(pos - pole_length / 2.0);
        if (dif < min_dif) {
            min_dif = dif;
            middle_most_pos = pos;
        }
    }

    return min(middle_most_pos, pole_length - middle_most_pos);
}

static int longestTime(const int pole_length, std::vector<double> &positions) {
    std::sort(positions.begin(), positions.end());

    double sum = 0;
    for (auto i = 0; i < positions.size() - 1; ++i) {
        positions[i + 1] -= sum;
        double delta_x = average(positions[i], positions[i + 1]) - positions[i];
        positions[i] += delta_x;
        positions[i + 1] -= delta_x;
        sum += delta_x;
    }

    return sum + max(positions[positions.size() - 1],
        pole_length - positions[positions.size() - 1]);
}

int main() {
    int num_test_cases = 0;
    std::cin >> num_test_cases;

    std::vector<std::vector<double>> test_cases;
    std::vector<int> pole_lengths;

    for (auto i = 0; i < num_test_cases; ++i) {
        int pole_length, num_ants;
        std::cin >> pole_length >> num_ants;
        pole_lengths.push_back(pole_length);

        std::vector<double> positions;

        for (auto j = 0; j < num_ants; ++j) {
            int pos;
            std::cin >> pos;
            positions.push_back(pos);
        }

        test_cases.push_back(positions);
    }

    for (auto i = 0; i < test_cases.size(); ++i) {
        int shortest_time = shortestTime(pole_lengths[i], test_cases[i]);
        int longest_time = longestTime(pole_lengths[i], test_cases[i]);

        std::cout << shortest_time << " " << longest_time << '\n';
    }
}
