#include <iostream>

#include "common.h"

using namespace std;

int main() {
    int prev = 999999999;
    int tot = 0, tot2 = 0;
    int win[3]{999999999, 999999999, 999999999};
    int pos = 0;
    for (const string& s : handle_inputs("day1")) {
        int num = stoi(s);
        if (num > prev) tot += 1;
        if (num > win[pos]) tot2 += 1;
        win[pos] = num;
        pos = (pos + 1) % 3;
        prev = num;
    }
    cout << tot << endl;
    cout << tot2 << endl;
}