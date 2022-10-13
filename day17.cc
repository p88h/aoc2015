#include <algorithm>
#include <iostream>
#include <unordered_map>

#include "common.h"

using namespace std;
vector<int> caps;
vector<int> path;
size_t mm = 100;

int count(int idx, int rem, size_t exm) {
    int tot = 0;
    if (rem == 0 && path.size() <= exm) {
        mm = min(path.size(), mm);
        return 1;
    }
    if (rem > 0 && idx < caps.size()) {
        tot += count(idx + 1, rem, exm);
        if (rem >= caps[idx]) {
            path.push_back(caps[idx]);
            tot += count(idx + 1, rem - caps[idx], exm);
            path.pop_back();
        }
    }
    return tot;
}

int main() {
    for (string& s : handle_inputs("day17")) caps.push_back(stoi(s));
    cout << count(0, 150, 1000) << endl;
    cout << count(0, 150, mm) << endl;
}