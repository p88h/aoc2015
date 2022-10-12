#include <iostream>

#include "common.h"

using namespace std;

string expand(const string &s) {
    string buf;
    int p = 0;
    while (p < s.length()) {
        int q = p;
        while (q < s.length() && s[q] == s[p]) q++;
        int c = q - p;
        buf += to_string(c);
        buf += s[p];
        p = q;
    }
    return buf;
}

int main() {
    string s = handle_input1("day10");
    for (int iter = 0; iter < 40; ++iter) s = expand(s);
    cout << s.length() << endl;
    for (int iter = 0; iter < 10; ++iter) s = expand(s);
    cout << s.length() << endl;
    return 0;
}