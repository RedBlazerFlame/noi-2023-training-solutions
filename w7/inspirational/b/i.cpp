/*
dp(pref, lasttaken = 0) = min(
    dp(pref - 1, lasttaken = |t| / 2),
    dp(pref - 1, lasttaken = 1),
    dp(pref - 1, lasttaken = 0),
) + t[pref]

dp(pref, lasttaken) = dp(pref - lasttaken, lasttaken = 0)
if(pref < lasttaken) dp(pref, lasttaken) = 0;

1, 8, 12, 6, 2

SIMPLIFICATION

dp(pref) = min(
    dp(pref - N / 2),
    ...
    dp(pref - 2),
    dp(pref - 1),
) + t[pref]
ans = min(
    dp(|t| - N / 2, lasttaken = 0),
    ...
    dp(|t| - 2, lasttaken = 0),
    dp(|t| - 1, lasttaken = 0),
)
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ll n;
    cin >> n;
    vector<ll> t(n, 0ll);

    for(ll i = 0ll; i < n - 1; i++) {
        cin >> t[i];
    }

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

    return 0;
}