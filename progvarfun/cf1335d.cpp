#include <bits/stdc++.h>
using namespace std;

/*
XOO OOO OOO
OOO XOO OOO
OOO OOO XOO

OXO OOO OOO
OOO OXO OOO
OOO OOO OXO

OOX OOO OOO
OOO OOX OOO
OOO OOO OOX
*/


int main() {
    vector<pair<int, int>> coords_list;

    coords_list.push_back(make_pair<int, int>(1 - 1, 1 - 1));
    coords_list.push_back(make_pair<int, int>(4 - 1, 2 - 1));
    coords_list.push_back(make_pair<int, int>(7 - 1, 3 - 1));
    coords_list.push_back(make_pair<int, int>(2 - 1, 4 - 1));
    coords_list.push_back(make_pair<int, int>(5 - 1, 5 - 1));
    coords_list.push_back(make_pair<int, int>(8 - 1, 6 - 1));
    coords_list.push_back(make_pair<int, int>(3 - 1, 7 - 1));
    coords_list.push_back(make_pair<int, int>(6 - 1, 8 - 1));
    coords_list.push_back(make_pair<int, int>(9 - 1, 9 - 1));

    int t;
    cin >> t;
    while(t--) {
        vector<string> grid;

        for(int i = 0; i < 9; i++) {
            string cur;
            cin >> cur;
            grid.push_back(cur);
        }

        for(const pair<int, int>& coords : coords_list) {
            grid[coords.first][coords.second] =  (grid[coords.first][coords.second] == '1' ? '2' : '1');
        }

        for(int i = 0; i < 9; i++) {
            cout << grid[i] << "\n";
        }
    }
    
    return 0;
}