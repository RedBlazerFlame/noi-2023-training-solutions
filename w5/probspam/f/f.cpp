#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef __int128 lll;

/*
Idea: value per credit
Sort by value per credit

a = [p1, v1][]

v1 / p1 [ v2 / p2 [ v3 / p3
v1 * p2 * p3 [ v2 * p3 [ v3 * p2

Okay this seems scary ;-;

What if I...

dp[i] represents the maximum total value Anakin can buy with i galactic credits
if I could compute this quickly, then good

dp[i] = max(dp[i - 1] + v1, dp[i - p2] + v2, dp[i - p3] + v3)
*/

/*
Thank you po Sir Kevin ^^
*/
const lll m1e18 = 1'000'000'000'000'000'000LL;
void print128(lll v) {
    if (v < 0) {
        printf("-");
        print128(-v);
    } else if (v < m1e18) {
        printf("%lld", ll(v));
    } else {
        print128(v / m1e18);
        printf("%018lld", ll(v % m1e18));
    }
}

template<typename T, typename size_t>
T access_def(const vector<T>& v, size_t i, T def) {
    if(i >= 0 && i < v.size()) return v[i];
    else return def;
}

int main() {
    ll q, v1ll, p2ll, v2ll, p3ll, v3ll;
    cin >> q >> p2ll >> p3ll >> v1ll >> v2ll >> v3ll;
    lll v1 = (lll)v1ll, p2 = (lll)p2ll, v2 = (lll)v2ll, p3 = (lll)p3ll, v3 = (lll)v3ll;

    ll MAX = 2000000;
    vector<lll> dp(MAX + 1, 0);

    for(ll i = 1; i < MAX; i++) {
        dp[i] = max(
            {access_def(dp, i - 1, (lll)std::numeric_limits<ll>::min()) + v1, 
            access_def(dp, i - p2, (lll)std::numeric_limits<ll>::min()) + v2, 
            access_def(dp, i - p3, (lll)std::numeric_limits<ll>::min()) + v3}
        );
    }

    while(q--) {
        ll c;
        cin >> c;

        print128(dp[c]);
        cout << endl;
    }

    return 0;
}