#include <algorithm>
#include <iostream>
#include <unordered_map>

#include "common.h"

using namespace std;

int boss_hp, boss_dmg, boss_def;
int min_cost = 999999;
int max_cost = 0;

void evaluate(string weapon, string armor, string rings, int cost, int dmg, int def) {
    int player_dps = max(1, dmg - boss_def);
    int boss_dps = max(1, boss_dmg - def);
    int boss_rounds = (100 + boss_dps - 1) / boss_dps;
    int player_rounds = (boss_hp + player_dps - 1) / player_dps;
    if (player_rounds <= boss_rounds && cost < min_cost) {
        min_cost = cost;
        cout << "Player wins with: " << weapon << ", " << armor << ", " << rings << " = " << cost << endl;
        cout << "player dps = " << player_dps << " (" << player_rounds << " rounds)" << endl;
        cout << "boss dps = " << boss_dps << " (" << boss_rounds << " rounds)" << endl;
    }
    if (player_rounds > boss_rounds && cost > max_cost) {
        max_cost = cost;
        cout << "Boss wins with: " << weapon << ", " << armor << ", " << rings << " = " << cost << endl;
        cout << "player dps = " << player_dps << " (" << player_rounds << " rounds)" << endl;
        cout << "boss dps = " << boss_dps << " (" << boss_rounds << " rounds)" << endl;
    }
}

void put_a_ring_on_it(string weapon, string armor, int cost, int dmg, int def) {
    evaluate(weapon, armor, "None", cost, dmg, def);
    evaluate(weapon, armor, "DMG+1", cost+25, dmg+1, def);
    evaluate(weapon, armor, "DMG+2", cost+50, dmg+2, def);
    //evaluate(weapon, armor, "DMG+3", cost+100, dmg+3, def);
    evaluate(weapon, armor, "DMG+1,DMG+2", cost+75, dmg+3, def);
    evaluate(weapon, armor, "DMG+1,DMG+3", cost+125, dmg+4, def);
    evaluate(weapon, armor, "DMG+2,DMG+3", cost+150, dmg+5, def);

    evaluate(weapon, armor, "DEF+1", cost+20, dmg, def+1);
    evaluate(weapon, armor, "DEF+2", cost+40, dmg, def+2);
    //evaluate(weapon, armor, "DEF+3", cost+80, dmg, def+1);
    evaluate(weapon, armor, "DEF+1,DEF+2", cost+60, dmg, def+3);
    evaluate(weapon, armor, "DEF+1,DEF+3", cost+100, dmg, def+4);
    evaluate(weapon, armor, "DEF+2,DEF+3", cost+120, dmg, def+5);

    evaluate(weapon, armor, "DMG+1,DEF+1", cost+45, dmg+1, def+1);
    evaluate(weapon, armor, "DMG+1,DEF+2", cost+65, dmg+1, def+2);
    evaluate(weapon, armor, "DMG+1,DEF+3", cost+105, dmg+1, def+3);

    evaluate(weapon, armor, "DMG+2,DEF+1", cost+70, dmg+2, def+1);
    evaluate(weapon, armor, "DMG+2,DEF+2", cost+90, dmg+2, def+2);
    evaluate(weapon, armor, "DMG+2,DEF+3", cost+130, dmg+2, def+3);

    evaluate(weapon, armor, "DMG+3,DEF+1", cost+120, dmg+3, def+1);
    evaluate(weapon, armor, "DMG+3,DEF+2", cost+140, dmg+3, def+2);
    evaluate(weapon, armor, "DMG+3,DEF+3", cost+180, dmg+3, def+3);
}

void try_on_armor(string weapon, int cost, int dmg) {
    put_a_ring_on_it(weapon, "None", cost, dmg, 0);
    put_a_ring_on_it(weapon, "Leather", cost + 13, dmg, 1);
    put_a_ring_on_it(weapon, "Chainmail", cost + 31, dmg, 2);
    put_a_ring_on_it(weapon, "Splintmail", cost + 53, dmg, 3);
    put_a_ring_on_it(weapon, "Bandedmail", cost + 75, dmg, 4);
    put_a_ring_on_it(weapon, "Platemail", cost + 102, dmg, 5);
}

void you_will_need_a_weapon() {
    try_on_armor("Dagger", 8, 4);
    try_on_armor("Shortsword", 10, 5);
    try_on_armor("Warhammer", 25, 6);
    try_on_armor("Longsword", 40, 7);
    try_on_armor("Greataxe", 74, 8);
}

int main() {
    vector<string> lines = handle_inputs("day21");
    boss_hp = stoi(split_str(lines[0], ' ')[2]);
    boss_dmg = stoi(split_str(lines[1], ' ')[1]);
    boss_def = stoi(split_str(lines[2], ' ')[1]);
    you_will_need_a_weapon();
    cout << min_cost << endl;
    cout << max_cost << endl;
    return 0;
}