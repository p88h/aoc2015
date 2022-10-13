#include <algorithm>
#include <iostream>
#include <unordered_set>

#include "common.h"

using namespace std;

unordered_set<string> expand_all(const string &molecule, const vector<pair<string, string>> &rules) {
    unordered_set<string> cache;
    for (auto entry: rules) {
        size_t len = entry.first.length();
        size_t pos = 0;
        while ((pos = molecule.find(entry.first, pos)) != string::npos) {
            string product = molecule.substr(0, pos) + entry.second + molecule.substr(pos+len);
            cache.insert(product);
            pos++;
        }
    }
    return cache;
}

string contract_rtl(string &molecule, const vector<pair<string, string>> &rules) {
    for (auto entry: rules) {
        size_t len = entry.second.length();
        size_t pos;
        if ((pos = molecule.rfind(entry.second)) != string::npos) {
            string product = molecule.substr(0, pos) + entry.first + molecule.substr(pos+len);
            return product;
        }
    }
    return "";
}

int main() {
    vector<string> lines = handle_inputs("day19");
    string molecule = lines.back();
    lines.pop_back();
    vector<pair<string, string>> rules;
    for (string &s : lines) {
        vector<string> vs = split_str(s);
        rules.push_back(pair<string, string>(vs[0], vs[2]));
    }
    cout << expand_all(molecule, rules).size() << endl;    
    int steps = 0;
    while (molecule != "" && molecule != "e") {
        molecule = contract_rtl(molecule, rules);
        steps++;
    }
    cout << steps << endl;
}