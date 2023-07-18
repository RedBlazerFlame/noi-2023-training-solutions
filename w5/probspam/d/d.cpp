#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ll n;
    cin >> n;

    vector<ll> gs = {0};
    vector<ll> hs = {0};

    for(ll i = 0; i < n; i++) {
        ll gv;
        cin >> gv;

        gs.push_back(gs[i] + gv);
    }

    for(ll i = 0; i < n; i++) {
        ll hv;
        cin >> hv;

        hs.push_back(hs[i] + hv);
    }

    ll final_ans = 0;

    for(ll k = 1; k <= (n << 1); k++) {
        ll ans = 0;

        /*
        j <= n;
        k - j <= n;
        j >= k - n
        */
        for(ll j = max(0ll, k - n); j <= min(k, n); j++) {
            ll cur = gs[j] + hs[k - j];

            if(cur > ans) ans = cur;
        }

        final_ans ^= ans;
    }
    
    cout << final_ans << endl;
    return 0;
}