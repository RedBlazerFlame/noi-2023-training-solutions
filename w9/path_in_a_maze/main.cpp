#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    pair<int, int> s;
    pair<int, int> t;

    vector<vector<char>> grid;
    for(int i = 0; i < n; i++) {
        vector<char> row;
        string row_str;
        cin >> row_str;
        for(int j = 0; j < m; j++) {

            
            if(row_str[j] == 'S') {
                s = {i, j};
                row.push_back('.');
            }
            else if(row_str[j] == 'T') {
                t = {i, j};
                row.push_back('.');
            }
            else row.push_back(row_str[j]);
        }

        grid.push_back(row);
    }

    queue<tuple<int, int, int>> q;
    q.push({s.first, s.second, 0});

    int dist_to_end = numeric_limits<int>::max();

    while(!q.empty()) {
        auto [x, y, d] = q.front();
        q.pop();

        if(grid[x][y] == '#') continue;
        if(x == t.first && y == t.second) {
            dist_to_end = d;
            break;
        }

        grid[x][y] = '#';

        if(x > 0) q.push({x - 1, y, d + 1});

        if(y > 0) q.push({x, y - 1, d + 1});

        if(x < n - 1) q.push({x + 1, y, d + 1});

        if(y < m - 1) q.push({x, y + 1, d + 1});

    }

    cout << (dist_to_end == numeric_limits<int>::max() ? "DOOMED" : to_string(dist_to_end)) << endl;

    return 0;
}