#include <cstring>
#include <iostream>

#include "common.h"

using namespace std;

void incr(char *buf, int pos) {
    if (buf[pos] == 'z') {
        buf[pos] = 'a';
        incr(buf, pos - 1);
    } else {
        buf[pos]++;
        if (buf[pos] == 'o' || buf[pos] == 'i' || buf[pos] == 'l') {
            buf[pos]++;
        }
    }
}

bool valid(char *buf) {
    int pc = 0;
    int ic = 0;
    for (int i = 1; i < 8; i++)
        if (buf[i] == buf[i - 1]) {
            pc += 1;
            i++;
        }
    for (int i = 2; i < 8; i++)
        if (buf[i] == buf[i - 1] + 1 && buf[i] == buf[i - 2] + 2) {
            ic = 1;
        }
    return (pc > 1) && (ic > 0);
}

int main() {
    string s = handle_input1("day11");
    char *buf = const_cast<char *>(s.c_str());
    while (!valid(buf)) incr(buf, 7);
    cout << s << endl;
    incr(buf, 7);
    while (!valid(buf)) incr(buf, 7);
    cout << s << endl;
    return 0;
}