#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXS = 3001;
short int diff[MAXS][MAXS];
short int grid[MAXS][MAXS];
int main() {

    // Input
    int w, h, n;
    cin >> w >> h >> n;
    for(int i = 0; i < h + 1; i++) {
        for(int j = 0; j < w + 1; j++) {
            diff[i][j] = 0;
        }
    }

    for(int i = 0; i < n; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;

        diff[y1][x1] += 1;
        diff[y2][x2] += 1;
        diff[y2][x1] += -1;
        diff[y1][x2] += -1;
    }

    for(int i = 0; i < h + 1; i++) {
        for(int j = 0; j < w + 1; j++) {
            grid[i][j] = diff[i][j];
            if(i > 0) grid[i][j] += grid[i - 1][j];
            if(j > 0) grid[i][j] += grid[i][j - 1];
            if(i > 0 && j > 0) grid[i][j] -= grid[i - 1][j - 1];
            // cout << (grid[i][j] > 0 ? '#' : '-');
        }
        // cout << endl;
    }

    int num_components = 0;
    for(int i = 0; i < h; i++) {
        for(int j = 0; j < w; j++) {
            if(grid[i][j] != 0) continue;

            // BFS time
            queue<pair<int, int>> q;
            q.push({j, i});

            while(!q.empty()) {
                int x, y;
                tie(x, y) = q.front();
                q.pop();

                if(grid[y][x] != 0) continue;
                grid[y][x] = -1;
                
                if(y > 0) {
                    q.push({x, y - 1});
                }
                if(x > 0) {
                    q.push({x - 1, y});
                }
                if(y < h - 1) {
                    q.push({x, y + 1});
                }
                if(x < w - 1) {
                    q.push({x + 1, y});
                }
            }

            num_components++;
        }
    }

    cout << num_components << endl;

    return 0;
}