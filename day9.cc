#include <algorithm>
#include <iostream>
#include <unordered_map>

#include "common.h"

using namespace std;

static int matrix[10][10];
vector<int> results;

void explore(int start, int limit, int path_mask, int cur_dist, int cnt) {
    if (cnt == limit) {
        results.push_back(cur_dist);
        return;
    }
    for (int i = 0; i < limit; i++) {
        int mask = 1 << i;
        if (!(path_mask & mask)) {
            explore(i, limit, path_mask | mask, cur_dist + matrix[start][i], cnt + 1);
        }
    }
}

int main() {
    unordered_map<string, int> cities;
    int idx = 0;
    for (const string &s : handle_inputs("day9")) {
        vector<string> ss = split_str(s, ' ');
        if (cities.find(ss[0]) == cities.end()) {
            cities[ss[0]] = ++idx;
            matrix[0][idx] = 0;
        }
        if (cities.find(ss[2]) == cities.end()) {
            cities[ss[2]] = ++idx;
            matrix[0][idx] = 0;
        }
        int a = cities[ss[0]];
        int b = cities[ss[2]];
        int d = stoi(ss[4]);
        matrix[a][b] = matrix[b][a] = d;
    }
    explore(0, idx + 1, 1, 0, 1);
    cout << *min_element(results.begin(), results.end()) << endl;
    cout << *max_element(results.begin(), results.end()) << endl;
}