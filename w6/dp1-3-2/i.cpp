/*
This submission solves dp1 exercise 3.2
Time complexity: O(MAX * num_coin_types)
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    const ll MAX = 30000;

    ll coins[5] = {1ll, 5ll, 10ll, 25ll, 50ll};
    ll n = 5;

    vector<vector<ll>> dp;
    dp.reserve(n);

    for(ll i = 0; i < n; i++) {
        vector<ll> row(MAX + 1, 1ll);
        dp.push_back(row);
        
        for(ll j = 1ll; j < MAX + 1; j++) {
            ll cur = 0ll;
            if(i > 0) cur += dp[i - 1][j];
            if(j >= coins[i]) cur += dp[i][j - coins[i]];
            dp[i][j] = cur;
        }
    }

    string line;

    while(getline(cin, line)) {
        ll cur_inp = stoll(line);
        ll ans = dp[n - 1][cur_inp];

        cout << "There " << (ans == 1 ? "is only" : "are") << " " << ans << " way" << (ans == 1 ? "" : "s") << " to produce " << cur_inp << " cents change." << endl;
    }

    return 0;
}