#include <algorithm>
#include <iostream>
#include <unordered_map>

#include "common.h"

using namespace std;

int boss_hp_total, boss_dmg;
int min_cost = 999999;
int bleed = 0;

void spell_it_out(int turn, int player_hp, int boss_hp, int mana, int shield, int poison, int recharge, int total) {
    if (turn == 0 && bleed > 0) {
        player_hp -= bleed;
        if (player_hp == 0) return;
    }
    int def = 0;
    if (poison > 0) {
        boss_hp -= 3;
        poison--;
    }
    if (shield > 0) {
        def = 7;
        shield--;
    }
    if (recharge > 0) {
        mana += 101;
        recharge--;
    }
    if (boss_hp <= 0) {
        if (total < min_cost) min_cost = total;
        return;
    }
    if (total >= min_cost) {
        return;
    }
    if (turn == 1) {
        player_hp -= boss_dmg - def;
        if (player_hp > 0) spell_it_out(!turn, player_hp, boss_hp, mana, shield, poison, recharge, total);
    } else {
        // don't bother with these if we have enough to kill
        if (boss_hp > 4 || mana < 53) {
            if (mana >= 73)
                spell_it_out(!turn, player_hp + 2, boss_hp - 2, mana - 73, shield, poison, recharge, total + 73);
            if (shield == 0 && mana >= 113)
                spell_it_out(!turn, player_hp, boss_hp, mana - 113, 6, poison, recharge, total + 113);
            if (poison == 0 && mana >= 173)
                spell_it_out(!turn, player_hp, boss_hp, mana - 173, shield, 6, recharge, total + 173);
            if (recharge == 0 && mana >= 229)
                spell_it_out(!turn, player_hp, boss_hp, mana - 229, shield, poison, 5, total + 229);
        }
        // cast a magic missile;
        if (mana >= 53) spell_it_out(!turn, player_hp, boss_hp - 4, mana - 53, shield, poison, recharge, total + 53);
    }
}

int main() {
    vector<string> lines = handle_inputs("day22");
    boss_hp_total = stoi(split_str(lines[0], ' ')[2]);
    boss_dmg = stoi(split_str(lines[1], ' ')[1]);
    spell_it_out(0, 50, boss_hp_total, 500, 0, 0, 0, 0);
    cout << min_cost << endl;
    min_cost = 999999;
    bleed = 1;
    spell_it_out(0, 50, boss_hp_total, 500, 0, 0, 0, 0);
    cout << min_cost << endl;
    return 0;
}