#include <iostream>

#include "common.h"

using namespace std;

long exp_mod_m(long start, long b, long e, long m) {
    long res = start;
    while (e) {
        if (e % 2 == 1) res = (res * b) % m;
        e /= 2;
        b = (b * b) % m;
    }
    return res;
}

int main() {
    string line = handle_input1("day25");
    vector<string> ss = split_str(line, ' ');
    int row = stoi(ss[15]);
    int col = stoi(ss[17]);
    int diag = row + col - 1;
    int prev = diag * (diag - 1) / 2;
    int idx = prev + col;
    cout << exp_mod_m(20151125, 252533, idx - 1, 33554393) << endl;
}