/*
opt(u, S) is the optimal solution
to go through everything through S
starting at u

opt(u, S) = min_v in S path(u, v) + opt(v, S - {v})
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

const ll MAX_N = 20;

ll memo[MAX_N + 1][1 << MAX_N];
ll opt(const vector<ll>& shortest, ll node, ull s, ll n) {
    ll& ans = memo[node][s];
    if(ans == -1) {
        if(s == 0) return 0;
    
        ll minv = numeric_limits<ll>::max();
        for(ll i = 0; i < n; i++) {
            if((s >> i) & 0b1) minv = min(minv, shortest[node * n + i] + opt(shortest, i, s & ~(1 << i), n));
        }

        ans = minv;
    }
    return ans;
}

int main() {
    for(int i = 0; i < MAX_N + 1; i++) {
        for(int j = 0; j < (1 << MAX_N); j++) {
            memo[i][j] = -1;
        }
    }

    ll n;
    cin >> n;
    vector<ll> grid(n * n, 0ll);
    for(ll i = 0ll; i < n; i++) {
        for(ll j = 0ll; j < n; j++) {
            cin >> grid[i * n + j];
        }
    }

    for(ll k = 0ll; k < n; k++) {
        for(ll i = 0ll; i < n - 1; i++) {
            for(ll j = i + 1ll; j < n; j++) {
                grid[i * n + j] = min(grid[i * n + j], grid[i * n + k] + grid[k * n + j]);
            }
        }
    }

    ll ans = numeric_limits<ll>::max();
    for(ll i = 0ll; i < n; i++) {
        ans = min(ans, opt(grid, i, ((1ll << n) - 1ll) ^ (1ll << i), n));
    }
    cout << ans << endl;
    return 0;
}