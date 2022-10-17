#include <algorithm>
#include <iostream>
#include <unordered_map>

#include "common.h"

using namespace std;

vector<int> path;
vector<int> best;
long minqe = 999999999999;
int pickmin(const vector<int> &weights, int target, int remains, int idx, int limit, int num) {
    if (idx < 0 || num >= limit) {
        return limit;
    }
    if (target == weights[idx]) {
        long qe = 1;
        for (auto w : path) {
            // cout << w << "*";
            qe *= (long)w;
        }
        qe *= (long)target;
        // cout << target << " = " << qe << endl;
        if (qe < minqe) {
            minqe = qe;
            best = path;
            best.push_back(target);
        }
        return num + 1;
    }
    int minn = limit;
    if (target > weights[idx]) {
        path.push_back(weights[idx]);
        minn = pickmin(weights, target - weights[idx], remains - weights[idx], idx - 1, limit, num + 1);
        path.pop_back();
    }
    if (remains >= target) {
        int minr = pickmin(weights, target, remains - weights[idx], idx - 1, limit, num);
        if (minr < minn) minn = minr;
    }
    return minn;
}

int main() {
    vector<int> quants;
    int total = 0;
    for (string &line : handle_inputs("day24")) {
        int w = stoi(line);
        quants.push_back(w);
        total += w;
    }
    pickmin(quants, total / 3, total, quants.size() - 1, 6, 0);
    cout << minqe << endl;
    minqe = 999999999999;
    pickmin(quants, total / 4, total, quants.size() - 1, 4, 0);
    cout << minqe << endl;
    return 0;
}