#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>

// original problem: https://open.kattis.com/problems/10kindsofpeople

struct Point {
    int x, y;
    friend bool operator==(const Point &p1, const Point &p2);
};

bool operator==(const Point &p1, const Point &p2) {
    return p1.x == p2.x && p1.y == p2.y;
}

std::vector<Point> memo; // take note of the visited locations to avoid revisiting them

bool memoContains(const Point &p1) {
    return std::find_if(memo.begin(), memo.end(), [&](const Point &p) { return p == p1; }) != memo.end();
}

bool canTravel(const std::vector<std::string> &space, const Point &p1, const Point &p2, char c) {
    if (p1 == p2) return true; // base case: the start == the destination
    memo.push_back(p1); // add current location to the list of visited locations

    /*
    format:

    const auto &next_location =
        avoid out of bounds error &&
        next location has the same digit as the current one &&
        avoid revisiting a location &&
        recursively check whether the next location can reach the destination
    
    */

    const auto &right = 
        p1.x < space[p1.y].length() - 1 && 
        space[p1.y][p1.x + 1] == c && 
        !memoContains({ p1.x + 1, p1.y }) && 
        canTravel(space, { p1.x + 1, p1.y }, p2, c);

    if (right) return true;

    const auto &left = 
        p1.x > 0 && 
        space[p1.y][p1.x - 1] == c && 
        !memoContains({ p1.x - 1, p1.y }) && 
        canTravel(space, { p1.x - 1, p1.y }, p2, c);

    if (left) return true;

    const auto &down = 
        p1.y < space.size() - 1 && 
        space[p1.y + 1][p1.x] == c && 
        !memoContains({ p1.x, p1.y + 1 }) && 
        canTravel(space, { p1.x, p1.y + 1 }, p2, c);

    if (down) return true;

    const auto &up = 
        p1.y > 0 && 
        space[p1.y - 1][p1.x] == c && 
        !memoContains({ p1.x, p1.y - 1 }) && 
        canTravel(space, { p1.x, p1.y - 1 }, p2, c);

    if (up) return true;

    return false;
}

std::string answer(const std::vector<std::string> &space, const Point &p1, const Point &p2) {
    memo = std::vector<Point>(); // reset the memo for each test case
    if (space[p1.y][p1.x] != space[p2.y][p2.x]) return "neither";
    if (space[p1.y][p1.x] == '0') return canTravel(space, p1, p2, '0') ? "binary" : "neither";
    else return canTravel(space, p1, p2, '1') ? "decimal" : "neither";
}

int main() {
    int height, width;
    std::cin >> height >> width;

    std::vector<std::string> space;

    std::string line;
    std::getline(std::cin, line);

    for (int i = 0; i < height; ++i) {
        std::string line;
        std::getline(std::cin, line);
        space.push_back(line);
    }

    int num_cases;
    std::cin >> num_cases;

    for (int i = 0; i < num_cases; ++i) {
        Point p1, p2;
        std::cin >> p1.y >> p1.x >> p2.y >> p2.x;
        --p1.x; --p1.y; --p2.x; --p2.y; // input coordinates start with 1, while indices start with 0
        std::cout << answer(space, p1, p2) << '\n';
    }
}
