#include <iostream>
#include <unordered_map>

#include "common.h"

using namespace std;

bool nice(const string &s) {
    int v = 0;
    int d = 0;
    int b = 0;
    char prev = ' ';
    for (int i = 0; i < s.length(); i++) {
        switch (s[i]) {
            case 'a':
            case 'e':
            case 'i':
            case 'o':
            case 'u':
                v++;
                break;
            case 'b':
            case 'd':
            case 'q':
            case 'y':
                if (prev == s[i] - 1) b++;
                break;
        }
        if (prev == s[i]) d++;
        prev = s[i];
    }
    return (v > 2) && (d > 0) && (b == 0);
}

bool nice2(const string &s) {
    unordered_map<string, int> first;
    bool havep = false;
    bool haved = false;
    for (int i = 1; i < s.length(); i++) {
        string p = s.substr(i - 1, 2);
        if (first[p] > 0 && first[p] < i - 1) {
            havep = true;
        } else if (!first[p]) {
            first[p] = i;
        }
        if (i > 2 && s[i - 2] == s[i]) {
            haved = true;
        }
    }
    return havep && haved;
}

int main() {
    int tot = 0;
    int tot2 = 0;
    for (const string &s : handle_inputs("day5")) {
        if (nice(s)) tot++;
        if (nice2(s)) tot2++;
    }
    cout << tot << endl;
    cout << tot2 << endl;
}