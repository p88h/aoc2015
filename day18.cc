#include <algorithm>
#include <iostream>
#include <unordered_map>

#include "common.h"

using namespace std;

int neighbors(const vector<string>& grid, int x, int y) {
    int cnt = 0;
    bool has_up = (y > 0);
    bool has_down = (y < grid.size() - 1);
    bool has_left = (x > 0);
    bool has_right = (x < grid[0].length() - 1);
    if (has_up && has_left && grid[y - 1][x - 1] == '#') cnt++;
    if (has_up && grid[y - 1][x] == '#') cnt++;
    if (has_up && has_right && grid[y - 1][x + 1] == '#') cnt++;
    if (has_left && grid[y][x - 1] == '#') cnt++;
    if (has_right && grid[y][x + 1] == '#') cnt++;
    if (has_down && has_left && grid[y + 1][x - 1] == '#') cnt++;
    if (has_down && grid[y + 1][x] == '#') cnt++;
    if (has_down && has_right && grid[y + 1][x + 1] == '#') cnt++;
    return cnt;
}

vector<string> life(const vector<string>& before) {
    vector<string> after;
    for (int y = 0; y < before.size(); ++y) {
        string tmp = before[y];
        for (int x = 0; x < tmp.length(); x++) {
            int cnt = neighbors(before, x, y);
            if (tmp[x] == '#') {
                if (cnt != 2 && cnt != 3) tmp[x] = '.';
            } else {
                if (cnt == 3) tmp[x] = '#';
            }
        }
        after.emplace_back(tmp);
    }
    return after;
}

int count(const vector<string>& grid) {
    int tot = 0;
    for (int y = 0; y < grid.size(); y++)
        for (int x = 0; x < grid.size(); x++)
            if (grid[y][x] == '#') tot++;
    return tot;
}

int main() {
    vector<string> grid = handle_inputs("day18");
    auto tmp = grid;
    for (int i = 0; i < 100; i++) tmp = life(tmp);
    cout << count(tmp) << endl;
    auto tmp2 = grid;
    tmp2[0][0] = tmp2[99][99] = tmp2[0][99] = tmp2[99][0] = '#';
    for (int i = 0; i < 100; i++) {
        tmp2 = life(tmp2);
        tmp2[0][0] = tmp2[99][99] = tmp2[0][99] = tmp2[99][0] = '#';
    }
    cout << count(tmp2) << endl;
}