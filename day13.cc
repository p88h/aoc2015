#include <algorithm>
#include <iostream>
#include <unordered_map>

#include "common.h"

using namespace std;

vector<string> names;
unordered_map<string, int> name2idx;
static int matrix[10][10];
vector<int> results;

int get_id(const string& name) {
    if (name2idx.find(name) == name2idx.end()) {
        name2idx[name] = names.size();
        names.push_back(name);
    }
    return name2idx[name];
}

void explore(int start, int limit, int path_mask, int cur_dist, int cnt, int first) {
    if (cnt == limit) {
        int cost = matrix[start][first] + matrix[first][start];
        results.push_back(cur_dist + cost);
        return;
    }
    for (int i = 0; i < limit; i++) {
        int mask = 1 << i;
        if (!(path_mask & mask)) {
            int cost = matrix[start][i] + matrix[i][start];
            explore(i, limit, path_mask | mask, cur_dist + cost, cnt + 1, first);
        }
    }
}

int main() {
    for (string& s : handle_inputs("day13")) {
        // trim .
        s.resize(s.length() - 1);
        vector<string> ss = split_str(s, ' ');
        int a = get_id(ss[0]);
        int b = get_id(ss[10]);
        int c = stoi(ss[3]);
        matrix[a][b] = ss[2] == "gain" ? c : -c;
    }
    explore(0, names.size(), 1, 0, 1, 0);
    cout << *max_element(results.begin(), results.end()) << endl;
    results.clear();
    names.emplace_back("Santa?");
    explore(0, names.size(), 1, 0, 1, 0);
    cout << *max_element(results.begin(), results.end()) << endl;
}