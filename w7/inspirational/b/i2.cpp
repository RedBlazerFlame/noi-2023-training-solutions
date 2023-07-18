#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// Might be able to memoize this! :O
ll n;
const ll MAXN = 101;
ll memo[MAXN][MAXN][MAXN];
ll cut(const vector<ll>& t, ll i, pair<ll, ll> need) {
    ll& ans = memo[i][need.first][need.second];

    if(ans == -1ll) {
        if(min(need.first, need.second) == 0ll) {
            ans = 0ll;
            return 0ll;
        }
        ans = numeric_limits<ll>::max();
        for(ll j = i + 1; j < n; j++) {
            ll lpiece_size = j - i;
            pair<ll, ll> poss1 = {need.first - lpiece_size, need.second};
            pair<ll, ll> poss2 = {need.first, need.second - lpiece_size};
            if(min(poss1.first, poss1.second) >= 0ll) {
                ans = min(ans, cut(t, j, poss1) + t[j - 1]);
            }
            if(min(poss2.first, poss2.second) >= 0ll) {
                ans = min(ans, cut(t, j, poss2) + t[j - 1]);
            }
        }
    }
    return ans;
}

int main() {
    for(ll i = 0ll; i < MAXN; i++) {
        for(ll j = 0ll; j < MAXN; j++) {
            for(ll k = 0ll; k < MAXN; k++) {
                memo[i][j][k] = -1ll;
            }
        }
    }

    cin >> n;
    vector<ll> t(n - 1, 0ll);

    for(ll i = 0ll; i < n - 1; i++) {
        cin >> t[i];
    }

    cout << cut(t, 0ll, {n >> 1ll, n >> 1ll}) << endl;

    return 0;
}