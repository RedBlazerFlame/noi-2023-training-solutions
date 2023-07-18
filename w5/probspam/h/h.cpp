/*
Idea: Use Kadane's
Time complexity: O(n^2)
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    int t;
    cin >> t;

    const ll MOD = 998244353;

    while(t--) {
        ll n;
        cin >> n;

        vector<ll> a(n, 0);

        for(ll& av : a) {
            cin >> av;
        }

        ll ans = 0;
        for(ll l = 0; l < n; l++) {
            ll minsum = a[l];
            ll cursum = 0;
            // if(a[l] > 0) ans += a[l];
            for(ll r = l; r < n; r++) {
                cursum += a[r];
                if(cursum > 0) cursum = 0;

                if(cursum < minsum) minsum = cursum;
                ans = ((ans + minsum) % MOD + MOD) % MOD;
            }
        }

        cout << ans << endl;
    }

    return 0;
}