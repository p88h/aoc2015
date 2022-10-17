#include <algorithm>
#include <iostream>
#include <unordered_map>

#include "common.h"

using namespace std;

struct Op {
    enum { HLF, TPL, INC, JMP, JIE, JIO } instr;
    char reg;
    int value;
};

int execute(const vector<Op> &program, int a_value) {
    int pc = 0;
    unordered_map<char, int> regs;
    regs['a'] = a_value;
    while (pc < program.size()) {
        Op op = program[pc];
        switch (op.instr) {
            case Op::HLF:
                regs[op.reg] /= 2;
                pc++;
                break;
            case Op::TPL:
                regs[op.reg] *= 3;
                pc++;
                break;
            case Op::INC:
                regs[op.reg] += 1;
                pc++;
                break;
            case Op::JMP:
                pc += op.value;
                break;
            case Op::JIE:
                if (regs[op.reg] % 2 == 0)
                    pc += op.value;
                else
                    pc++;
                break;
            case Op::JIO:
                if (regs[op.reg] == 1)
                    pc += op.value;
                else
                    pc++;
                break;
        }
    }
    return regs['b'];
}

int main() {
    vector<Op> program;
    for (string &line : handle_inputs("day23")) {
        vector<string> ss = split_str(line, ' ');
        if (ss[0] == "hlf") program.push_back({Op::HLF, ss[1][0], 0});
        if (ss[0] == "tpl") program.push_back({Op::TPL, ss[1][0], 0});
        if (ss[0] == "inc") program.push_back({Op::INC, ss[1][0], 0});
        if (ss[0] == "jmp") program.push_back({Op::JMP, ' ', stoi(ss[1])});
        if (ss[0] == "jie") program.push_back({Op::JIE, ss[1][0], stoi(ss[2])});
        if (ss[0] == "jio") program.push_back({Op::JIO, ss[1][0], stoi(ss[2])});
    }
    cout << execute(program, 0) << endl;
    cout << execute(program, 1) << endl;
    return 0;
}