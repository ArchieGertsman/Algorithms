#include <iostream>
#include <string>
#include <random>   
#include <algorithm>
    
int randBinDig() {
    std::random_device rand;
    std::mt19937 mt(rand());
    std::uniform_int_distribution<int> dist(0, 1);
    return dist(mt);
}

int main() {
    std::string meme;
    std::getline(std::cin, meme);
    std::transform(meme.begin(), meme.end(), meme.begin(), [&](char &c) { 
        return (randBinDig() == 0 ? std::tolower : std::toupper)(c);    
    });
    std::cout << meme << '\n';
}
