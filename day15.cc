#include <algorithm>
#include <iostream>

#include "common.h"

using namespace std;
vector<int> vs, ds, fs, ts, cs;
vector<int> results;
vector<int> results2;
vector<int> path;

void print(string label, vector<int> &ref) {
    cout << label << ": " << endl;
    int tot = 0;
    for (int i = 0; i < path.size(); ++i) {
        cout << path[i] << "*" << ref[i];
        tot += path[i] * ref[i];
        cout << ((i < path.size() - 1) ? " + " : " = ");
    }
    cout << tot << endl;
}

void evaluate (int idx, int rem, int v, int d, int f, int t, int c) {
    if (idx == vs.size() - 1) {
        path.push_back(rem);
        v = max(0, v + rem * vs[idx]);
        d = max(0, d + rem * ds[idx]);
        f = max(0, f + rem * fs[idx]);
        t = max(0, t + rem * ts[idx]);
        c = max(0, c + rem * cs[idx]);
        results.push_back(v*d*f*t);
        if (c == 500) results2.push_back(v*d*f*t);
        path.pop_back();
        return;
    }
    for (int k=0; k<=rem; k++) {
        path.push_back(k);
        evaluate(idx + 1, rem-k, v+vs[idx]*k, d+ds[idx]*k, f+fs[idx]*k, t+ts[idx]*k, c+cs[idx]*k);
        path.pop_back();
    }
}

int main() {
    for (string& s : handle_inputs("day15")) {
        vector<string> ss = split_str(s, ' ');
        vs.push_back(stoi(ss[2]));
        ds.push_back(stoi(ss[4]));
        fs.push_back(stoi(ss[6]));
        ts.push_back(stoi(ss[8]));
        cs.push_back(stoi(ss[10]));
    }
    evaluate(0, 100, 0, 0, 0, 0, 0);
    cout << *max_element(results.begin(), results.end()) << endl;
    cout << *max_element(results2.begin(), results2.end()) << endl;
}