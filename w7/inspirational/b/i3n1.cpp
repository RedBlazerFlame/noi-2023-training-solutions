#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// Might be able to memoize this! :O
ll n;
const ll MAXN = 401;
ll memo[MAXN][MAXN];
ll cut(const vector<ll>& t, ll i, ll need) {
    ll& ans = memo[i][need];

    if(ans == -1ll) {
        if(min(need, n - i - need) == 0ll) {
            ans = 0ll;
            return 0ll;
        }
        ans = numeric_limits<ll>::max();
        for(ll j = i + 1; j < n; j++) {
            ll lpiece_size = j - i;
            if(min(need - lpiece_size, n - i - need) >= 0ll) {
                ans = min(ans, cut(t, j, need - lpiece_size) + t[j - 1]);
            }
            if(min(need, n - i - lpiece_size - need) >= 0ll) {
                ans = min(ans, cut(t, j, need) + t[j - 1]);
            }
        }
    }
    return ans;
}

int main() {
    for(ll i = 0ll; i < MAXN; i++) {
        for(ll j = 0ll; j < MAXN; j++) {
            memo[i][j] = -1ll;
        }
    }

    cin >> n;
    vector<ll> t(n - 1, 0ll);

    for(ll i = 0ll; i < n - 1; i++) {
        cin >> t[i];
    }

    if(n >= MAXN) {
        t.push_back(0ll);
        vector<ll> dp(n, 0ll);
        for(ll i = 0ll; i < n; i++) {
            if(i < (n >> 1ll)) dp[i] = t[i];
            else {
                ll minv = numeric_limits<ll>::max();

                for(ll j = 1; j <= (n >> 1ll); j++) {
                    minv = min(minv, dp[i - j]);
                }

                dp[i] = minv + t[i];
            }
        }

        cout << dp[n - 1] << endl;
    } else {
        cout << cut(t, 0ll, n >> 1ll) << endl;
    }

    return 0;
}