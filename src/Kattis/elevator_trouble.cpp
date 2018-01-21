#include <iostream>
#include <map>
#include <cmath>

// problem: https://open.kattis.com/problems/elevatortrouble
    
static bool isEven(int a) {
    return a % 2 == 0;
}

static bool isOdd(int a) {
    return a % 2 == 1;
}

static int minPushes(int f, int s, int g, int u, int d, int &cur, std::map<int, int> &floors) {
    if (floors.find(cur) != floors.end()) {
        int p = floors[cur];
        return p > 0 ? p : -1;
    }
    
    if (isEven(u) && isEven(d) && (isEven(s) && isOdd(g) || isOdd(s) && isEven(g))) {
        return -1;
    }
    
    int pushes = 0;
    int cur_prev = cur; 

    if (cur > g) {
        if (d == 0) {
            return -1;
        }
        
        pushes = (int)ceil((cur - g) / (double)d);
        if (cur - d * pushes >= 1) {
            cur -= d * pushes;
        }
        else if (cur - d * --pushes >= 1 && pushes > 0) {
            cur -= d * pushes;
        }
        else {
            if (u == 0) {
                return -1;
            }
            
            pushes = (int)ceil((1 + d - cur) / (double)u);
            if (cur + u * pushes <= f) {
                cur += u * pushes;
            }
            else if (cur + u * --pushes <= f && pushes > 0) {
                cur += u * pushes;
            }
            else {
                return -1;
            }
        }
    }
    else if (cur < g) {
        if (u == 0) {
            return -1;
        }
        
        pushes = (int)ceil((g - cur) / (double)u);
        if (cur + u * pushes <= f) {
            cur += u * pushes;
        }
        else if (cur + u * --pushes <= f && pushes > 0) {
            cur += u * pushes;
        }
        else {
            if (d == 0) {
                return -1;
            }
            
            pushes = (int)ceil((cur + u - f) / (double)d);
            if (cur - d * pushes >= 1) {
                cur -= d * pushes;
            }
            else if (cur - d * --pushes >= 1 && pushes > 0) {
                cur -= d * pushes;
            }
            else {
                return -1;
            }
        }
    }
    else {
        return 0;
    }
    
    int min_pushes = minPushes(f, s, g, u, d, cur, floors);
    if (min_pushes == -1) {
        floors[cur_prev] = -1;
        return -1;
    }
    
    pushes += min_pushes;
    floors[cur_prev] = pushes;
    
    return pushes;
}

int main() {
    int f, s, g, u, d;
    std::cin >> f >> s >> g >> u >> d;
    
    std::map<int, int> floors;
    
    int min_num = minPushes(f, s, g, u, d, s, floors);
    if (min_num == -1) {
        std::cout << "use the stairs\n";
    }
    else {
        std::cout << min_num << '\n';
    }
}
