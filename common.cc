#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

vector<string> handle_inputs(const string &prefix) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    vector<string> inputs;
    ifstream in(prefix + ".in");
    string str;
    while (in && getline(in, str)) {
        if (str.size() > 0) {
            inputs.push_back(str);
        }        
    }
    in.close();
    return inputs;
}

string handle_input1(const string &prefix) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ifstream in(prefix + ".in");
    stringstream buffer;
    buffer << in.rdbuf();
    return buffer.str();
}

vector<string> split_str(const string &s, char delim) {
  vector<string> ret;
  string t;
  for (char c: s) {
    if (c != delim) {
      t += c;
    } else {
      if (t.length()) ret.push_back(t);
      t.clear();
    }
  }
  if (t.length()) ret.push_back(t);
  return ret;
}