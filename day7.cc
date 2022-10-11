#include <iostream>
#include <unordered_map>

#include "common.h"

using namespace std;

class Gate {
  public:
    virtual ~Gate() {}
    virtual int eval() = 0;
};

class Wire {
    Gate *input = nullptr;
    string name;
    bool cached;
    int value;

  public:
    Wire(int num) : name{to_string(num)}, cached{true}, value{num} {}
    Wire(string label) : name{move(label)}, cached{false} {}
    const string &label() { return name; }
    void connect(Gate *gate) { input = gate; }
    void reset() {
        if (input) cached = false;
    }
    void affix(int num) {
        value = num;
        cached = true;
    }
    int eval() {
        if (!cached && input) {
            value = input->eval();
            cached = true;
        }
        return value;
    }
};

class BinaryGate : public Gate {
    Wire *left, *right;
    string name;

  public:
    BinaryGate(Wire *l, Wire *r, string label) : left{l}, right{r}, name{move(label)} {}
    virtual ~BinaryGate() {}
    virtual int eval() {
        int lv = left->eval();
        int rv = right->eval();
        return op(lv, rv);
    }
    virtual int op(int a, int b) = 0;
};

class AndGate : public BinaryGate {
  public:
    AndGate(Wire *l, Wire *r) : BinaryGate(l, r, "AND"){};
    virtual int op(int a, int b) { return a & b; }
};
class OrGate : public BinaryGate {
  public:
    OrGate(Wire *l, Wire *r) : BinaryGate(l, r, "OR"){};
    virtual int op(int a, int b) { return a | b; }
};
class LshiftGate : public BinaryGate {
  public:
    LshiftGate(Wire *l, Wire *r) : BinaryGate(l, r, "SHL"){};
    virtual int op(int a, int b) { return a << b; }
};
class RshiftGate : public BinaryGate {
  public:
    RshiftGate(Wire *l, Wire *r) : BinaryGate(l, r, "SHR"){};
    virtual int op(int a, int b) { return a >> b; }
};
class NotGate : public Gate {
    Wire *only;

  public:
    NotGate(Wire *one) : only{one} {}
    virtual int eval() { return only->eval() ^ 0xFFFF; }
};
class MovGate : public Gate {
    Wire *only;

  public:
    MovGate(Wire *one) : only{one} {}
    virtual int eval() { return only->eval(); }
};

class Circuit {
    unordered_map<string, Wire *> wires_;

  public:
    Wire *get_wire(string name) {
        if (!wires_[name]) {
            if (isdigit(name[0])) {
                wires_[name] = new Wire(stoi(name));
            } else {
                wires_[name] = new Wire(name);
            }
        }
        return wires_[name];
    }
    void reset() {
        for (auto &it : wires_) {
            it.second->reset();
        }
    }
};

int main() {
    Circuit board;
    for (const string &s : handle_inputs("day7")) {
        vector<string> vs = split_str(s, ' ');
        Wire *left, *right, *out;
        string &op = vs[1];
        if (vs.size() == 3) {  // just assign
            left = right = board.get_wire(vs[0]);
            out = board.get_wire(vs[2]);
            op = "MOV";
        } else if (vs.size() == 4) {  // NOT-like
            left = right = board.get_wire(vs[1]);
            out = board.get_wire(vs[3]);
            op = vs[0];
        } else {
            left = board.get_wire(vs[0]);
            right = board.get_wire(vs[2]);
            out = board.get_wire(vs[4]);
        }
        Gate *gate;
        switch (op[0]) {
            case 'A':
                gate = new AndGate(left, right);
                break;
            case 'O':
                gate = new OrGate(left, right);
                break;
            case 'L':
                gate = new LshiftGate(left, right);
                break;
            case 'R':
                gate = new RshiftGate(left, right);
                break;
            case 'N':
                gate = new NotGate(left);
                break;
            case 'M':
                gate = new MovGate(left);
                break;
        }
        out->connect(gate);
    }
    int val1 = board.get_wire("a")->eval();
    cout << val1 << endl;
    board.reset();
    board.get_wire("b")->affix(val1);
    int val2 = board.get_wire("a")->eval();
    cout << val2 << endl;
}