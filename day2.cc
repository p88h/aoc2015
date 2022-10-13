#include <cstdlib>
#include <iostream>

#include "common.h"

using namespace std;

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

int main() {
    long sum = 0;
    long sum2 = 0;
    for (const string& s : handle_inputs("day2")) {
        char* ptr = const_cast<char*>(s.c_str());
        long w = strtol(ptr, &ptr, 10);
        long h = strtol(ptr + 1, &ptr, 10);
        long d = strtol(ptr + 1, &ptr, 10);
        long m = MAX(MAX(w, h), d);
        long n = MIN(MIN(w + h, w + d), h + d);
        sum += 2 * (w * h + h * d + w * d) + (w * h * d) / m;
        sum2 += 2 * n + w * h * d;
    }
    cout << sum << endl;
    cout << sum2 << endl;
}