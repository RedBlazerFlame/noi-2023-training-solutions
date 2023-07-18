#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ll w, h, n;
    cin >> w >> h >> n;
    vector<vector<short int>> grid;
    for(ll i = 0ll; i < h; i++) {
        vector<short int> row(w, 0);
        grid.push_back(row);
    }
    
    for(ll i = 0ll; i < n; i++) {
        ll x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;

        for(ll j = y1; j < y2; j++) {
            for(ll k = x1; k < x2; k++) {
                grid[j][k] = -1;
            }
        }
    }

    ll num_components = 0ll;
    for(ll i = 0ll; i < h; i++) {
        for(ll j = 0ll; j < w; j++) {
            if(grid[i][j] != 0ll) continue;

            // BFS time
            queue<pair<ll, ll>> q;
            q.push({j, i});

            while(!q.empty()) {
                ll x, y;
                tie(x, y) = q.front();
                q.pop();

                if(grid[y][x] != 0) continue;
                grid[y][x] = 1;
                
                vector<pair<ll, ll>> poss_dirs;
                if(y > 0ll) {
                    poss_dirs.push_back({0ll, -1ll});
                }
                if(x > 0ll) {
                    poss_dirs.push_back({-1ll, 0ll});
                }
                if(y < h - 1ll) {
                    poss_dirs.push_back({0ll, 1ll});
                }
                if(x < w - 1ll) {
                    poss_dirs.push_back({1ll, 0ll});
                }

                for(const pair<ll, ll>& poss_dir : poss_dirs) {
                    ll dirx, diry;
                    tie(dirx, diry) = poss_dir;
                    q.push({dirx + x, diry + y});
                }
            }

            num_components++;
        }
    }

    cout << num_components << endl;

    return 0;
}