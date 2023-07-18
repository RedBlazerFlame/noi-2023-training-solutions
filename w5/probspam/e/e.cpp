#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    int t;
    cin >> t;

    while(t--) {
        ll n, k;
        cin >> n >> k;
        vector<ll> bs = {0};
        vector<ll> ds = {0};

        for(ll i = 0; i < n; i++) {
            ll bv;
            cin >> bv;
            bs.push_back(bs[i] + bv);
        }

        for(ll i = 0; i < n; i++) {
            ll dv;
            cin >> dv;
            ds.push_back(ds[i] + dv);
        }

        ll ans = 0;

        /*
        bs[j] + ds[k - j]
        j <= n
        k - j <= n -> j >= k - n
        j >= k - j
        2j >= k
        j >= (k + 1) // 2    
        */
        for(ll j = max({0ll, (k + 1) >> 1, k - n}); j <= min(n, k); j++) {
            ll cur = bs[j] + ds[k - j];

            if(cur > ans) ans = cur;
        }


        cout << ans << endl;
    }

    return 0;
}