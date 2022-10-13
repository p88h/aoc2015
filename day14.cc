#include <algorithm>
#include <iostream>

#include "common.h"

using namespace std;

int main() {
    int m = 0, n = 0;
    vector<int> vs, tds, ts, ps, pts;
    for (string& s : handle_inputs("day14")) {
        vector<string> ss = split_str(s, ' ');
        int v = stoi(ss[3]);
        int t = stoi(ss[6]);
        int d = stoi(ss[13]);
        vs.push_back(v);
        tds.push_back(t+d);
        ts.push_back(t);
        ps.push_back(0);
        pts.push_back(0);
        int f = 2503 / (t + d);
        int r = 2503 % (t + d);
        if (r > t) r = t;
        int p = (f * t + r) * v;
        m = max(p, m); 
    }
    cout << m << endl;
    for (int i = 0; i < 2503; i++) {
        m = n = 0;
        for (size_t j = 0; j < vs.size(); j++) {
            if ((i % tds[j]) < ts[j]) {
                ps[j] += vs[j];
            }
            if (ps[j] > m) {
                m = ps[j];
                n = j;
            }
        }
        pts[n]++;
    }
    cout << *max_element(pts.begin(), pts.end()) << endl;
}