#include <algorithm>
#include <iostream>
#include <unordered_map>

#include "common.h"

using namespace std;
unordered_map<string, int> reqs = {{"children:", 3}, {"cats:", 7},    {"samoyeds:", 2}, {"pomeranians:", 3},
                                   {"akitas:", 0},   {"vizslas:", 0}, {"goldfish:", 5}, {"trees:", 3},
                                   {"cars:", 2},     {"perfumes:", 1}};

bool ensure(int num, string key, int value) { return reqs[key] == value; }

bool ensure2(int num, string key, int value) {
    if (key == "cats:" || key == "trees:") {
        return reqs[key] < value;
    }
    if (key == "pomeranians:" || key == "goldfish:") {
        return reqs[key] > value;
    }
    return reqs[key] == value;
}

int main() {
    for (string& s : handle_inputs("day16")) {
        vector<string> ss = split_str(s, ' ');
        int num = stoi(ss[1]);
        if (ensure(num, ss[2], stoi(ss[3])) && ensure(num, ss[4], stoi(ss[5])) && ensure(num, ss[6], stoi(ss[7]))) {
            cout << num << endl;
        }
        if (ensure2(num, ss[2], stoi(ss[3])) && ensure2(num, ss[4], stoi(ss[5])) && ensure2(num, ss[6], stoi(ss[7]))) {
            cout << num << endl;
        }
    }
}