#include <functional>
#include <iostream>
#include <unordered_map>
#include <utility>

#include "common.h"

using namespace std;

struct pair_hash {
    template <class T1, class T2>
    std::size_t operator()(const std::pair<T1, T2>& p) const {
        return p.first * 100000 + p.second;
    }
};

class SantaStateMachine {
    pair<long, long> position_;

  public:
    SantaStateMachine() { position_ = make_pair(0l, 0l); }
    pair<long, long> move(char c) {
        switch (c) {
            case '<':
                position_.first -= 1;
                break;
            case '>':
                position_.first += 1;
                break;
            case 'v':
                position_.second += 1;
                break;
            case '^':
                position_.second -= 1;
                break;
            default:
                break;
        }
        return position_;
    }

    int deliver(unordered_map<pair<long, long>, long, pair_hash>& where) {
        if (where[position_] == 0) {
            where[position_] = 1;
            return 1;
        }
        return 0;
    }
};

int main() {
    string s = handle_input1("day3");
    unordered_map<pair<long, long>, long, pair_hash> m1, m2;
    SantaStateMachine a, b, c;
    long cnt1 = 0, cnt2 = 0;
    for (int i = 0; i <= s.length(); i++) {
        cnt1 += a.deliver(m1);
        // double-delivery but we don't care.
        cnt2 += b.deliver(m2);
        cnt2 += c.deliver(m2);
        if (i < s.length()) {
            a.move(s[i]);
            if (i % 2 == 0) {
                b.move(s[i]);
            } else {
                c.move(s[i]);
            }
        }
    }
    cout << cnt1 << endl;
    cout << cnt2 << endl;
    return 0;
}