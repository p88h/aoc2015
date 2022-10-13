#include <cassert>
#include <cstring>
#include <iostream>

#include "common.h"

using namespace std;

struct Node {
    int value;
    string str;
    vector<string> labels;
    vector<Node *> children;
    bool red;
};

void jump_skip_spaces(string str, int *pos, int hop = 1) {
    (*pos) += hop;
    while (str[*pos] == ' ') (*pos)++;
}

string parse_string(string str, int *pos) {
    int start = *pos + 1;
    int end = *pos + 2;
    while (str[end] != '"') end++;
    string t = str.substr(start, end - start);
    *pos = end;
    jump_skip_spaces(str, pos);
    return t;
}

Node *parse(string str, int *pos) {
    Node *tmp = new Node();
    if (str[*pos] == '"') {
        tmp->str = parse_string(str, pos);
        return tmp;
    }
    // array
    if (str[*pos] == '[') {
        while (str[*pos] != ']') {
            jump_skip_spaces(str, pos, true);
            tmp->children.push_back(parse(str, pos));
        }
        jump_skip_spaces(str, pos);
        return tmp;
    }
    // object
    if (str[*pos] == '{') {
        while (str[*pos] != '}') {
            jump_skip_spaces(str, pos);
            tmp->labels.push_back(parse_string(str, pos));
            assert(str[*pos] == ':');
            jump_skip_spaces(str, pos);
            Node *child = parse(str, pos);
            tmp->red = tmp->red || (child->str == "red");
            tmp->children.push_back(child);
        }
        jump_skip_spaces(str, pos);
        return tmp;
    }
    // must be a number then
    char *end;
    tmp->value = strtol(str.c_str() + *pos, &end, 10);
    *pos = end - str.c_str();
    jump_skip_spaces(str, pos, 0);
    return tmp;
}

int sum_numbers(Node *top, bool filter_red) {
    if (filter_red && top->red) return 0;
    int ret = top->value;
    if (top->children.size() > 0) {
        for (Node *child : top->children) {
            ret += sum_numbers(child, filter_red);
        }
    }
    return ret;
}
void print(Node *top, string indent) {
    if (!top->labels.empty()) {
        cout << indent << "OBJECT>  " << endl;
        for (size_t i = 0; i < top->labels.size(); ++i) {
            cout << indent << top->labels[i] << "=" << endl;
            print(top->children[i], indent + "  ");
        }
    } else if (!top->children.empty()) {
        cout << indent << "ARRAY:  " << top->str << endl;
        for (Node *child : top->children) {
            print(child, indent + "  ");
        }
    } else if (!top->str.empty()) {
        cout << indent << "STR:  " << top->str << endl;
    } else {
        cout << indent << "NUM:  " << top->value << endl;
    }
}

int main() {
    string s = handle_input1("day12");
    int p = 0;
    Node *root = parse(s, &p);
    cout << sum_numbers(root, false) << endl;
    cout << sum_numbers(root, true) << endl;
    return 0;
}