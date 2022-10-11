#include <iostream>

#include "common.h"

using namespace std;

int unescape_len(const string &s) {
    int pos = 1;
    int cnt = 0;
    while (pos < s.length() && s[pos] != '"') {
        if (s[pos] == '\\') {
            if (s[pos + 1] == 'x') {
                pos += 4;
            } else {
                pos += 2;
            }
        } else {
            pos++;
        }
        cnt++;
    }
    return cnt;
}

int escape_len(const string &s) {
    int pos = 1;
    int cnt = 2;
    for (pos = 0; pos < s.length(); pos++) {
        if (s[pos] == '"' || s[pos] == '\\') {
            cnt += 2;
        } else {
            cnt += 1;
        }
    }
    return cnt;
}

int main() {
    int tot = 0;
    int tot1 = 0;
    int tot2 = 0;
    for (const string &s : handle_inputs("day8")) {
        tot1 += unescape_len(s);
        tot2 += escape_len(s);
        tot += s.length();
    }
    cout << (tot - tot1) << endl;
    cout << (tot2 - tot) << endl;
}