#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct vec2 {
    int x;
    int y;
};

struct point {
    int x1;
    int y1;
    int x2;
    int y2;
};


int main() {
    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};

    // Input
    int w, h, n;
    cin >> w >> h >> n;

    map<int, int> x_list;
    map<int, int> y_list;
    vector<point> pts;
    for(int i = 0; i < n; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        x2--; y2--;

        x_list[x1] = 0;
        x_list[x2] = 0;
        x_list[x2 + 1] = 0;
        y_list[y1] = 0;
        y_list[y2] = 0;
        y_list[y2 + 1] = 0;
        pts.push_back({x1, y1, x2, y2});
    }
    x_list[0] = 0;
    x_list[w - 1] = 0;
    y_list[0] = 0;
    y_list[h - 1] = 0;

    // Compress
    int compx = 0;
    for(auto& [key, value] : x_list) {
        value = compx;
        compx++;
    }

    int compy = 0;
    for(auto& [key, value] : y_list) {
        value = compy;
        compy++;
    }

    int maxy = y_list[h - 1] + 1, maxx = x_list[w - 1] + 1;

    vector<vector<int>> grid;
    for(int i = 0; i < maxy + 1; i++) {
        vector<int> row(maxx + 1, 0);
        grid.push_back(row);
    }

    for(auto& [x1, y1, x2, y2] : pts) {
        x1 = x_list[x1];
        x2 = x_list[x2];
        y1 = y_list[y1];
        y2 = y_list[y2];

        grid[y1][x1] --;
        grid[y2 + 1][x2 + 1] --;
        grid[y2 + 1][x1] ++;
        grid[y1][x2 + 1] ++;
    }


    for(int i = 0; i < maxy; i++) {
        for(int j = 0; j < maxx; j++) {
            if(i > 0) grid[i][j] += grid[i - 1][j];
            if(j > 0) grid[i][j] += grid[i][j - 1];
            if(i > 0 && j > 0) grid[i][j] -= grid[i - 1][j - 1];   
        }
    }
    

    int color = 1;
    for(int i = 0; i < maxy; i++) {
        for(int j = 0; j < maxx; j++) {
            if(grid[i][j] == 0) {
                queue<vec2> q;
                q.push({j, i});

                while(!q.empty()) {
                    auto [x, y] = q.front();
                    q.pop();

                    if(x < 0 || y < 0 || x >= maxx || y >= maxy) continue;
                    if(grid[y][x] != 0) continue;
                    grid[y][x] = color;

                    for(int dirind = 0; dirind < 4; dirind++) {
                        q.push({x + dx[dirind], y + dy[dirind]});
                    }
                }

                color ++;
            }
        }
    }

    cout << color - 1 << endl;

    return 0;
}