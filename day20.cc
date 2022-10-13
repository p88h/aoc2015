#include <algorithm>
#include <iostream>
#include <unordered_map>

#include "common.h"

using namespace std;

#define HMAX 1000001
int main() {
    int minh = HMAX;
    int limit = stoi(handle_input1("day20"));
    int houses[HMAX] = { 0 };
    for (int elf = 1; elf < HMAX; elf++) {
        for (int m = 1; elf * m < HMAX; m++) {
            houses[elf*m] += elf * 10;
            if (houses[elf*m] >= limit && elf*m < minh) {
                cout << elf << "*" << m << "=" << elf*m << endl;
                minh = elf*m;
            }
        }        
    }
    minh = HMAX;
    int houses2[HMAX] = { 0 };
    for (int elf = 1; elf < HMAX; elf++) {
        for (int m = 1; m <= 50 && elf * m < HMAX; m++) {
            houses2[elf*m] += elf * 11;
            if (houses2[elf*m] >= limit && elf*m < minh) {
                cout << elf << "*" << m << "=" << elf*m << endl;
                minh = elf*m;
            }
        }        
    }
    return 0;
}