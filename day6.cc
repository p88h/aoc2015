#include <bitset>
#include <iostream>
#include "common.h"

using namespace std;

int main() {
    bitset<1000000> bits;
    int vals[1000000] = { 0 };
    int cnt = 0;
    int tot2 = 0;
    for (const string& s: handle_inputs("day6")) {
        char* ptr = const_cast<char *>(s.c_str());
        int mode = 1;
        if (s[1] == 'o') { // toggle
            ptr += 7;
            mode = 2;
        } else if (s[6] == 'f') { // off
            ptr += 9;
            mode = 3;
        } else {
            ptr += 8;
        }
        long x1 = strtol(ptr, &ptr, 10);
        long y1 = strtol(ptr+1, &ptr, 10);
        long x2 = strtol(ptr+9, &ptr, 10);
        long y2 = strtol(ptr+1, &ptr, 10);
        cout << x1 << ',' << y1 << " : " << x2 << ',' << y2 << endl;
        for (int x=x1; x<=x2; x++) for (int y=y1; y<=y2; y++) {
            cnt++;
            int pos = y*1000 + x;
            tot2 -= vals[pos];
            if (mode == 1) {
                bits.set(pos);
                vals[pos]++;
            } else if (mode == 2) {
                bits.flip(pos);
                vals[pos]+=2;
            } else {
                bits.reset(pos);
                vals[pos]--;
            }
            if (vals[pos]<0) {
                vals[pos] = 0;
            }
            tot2 += vals[pos];
        }
    }
    int tot = bits.count();
    cout << cnt << endl;
    cout << tot << endl;
    cout << tot2 << endl;
}