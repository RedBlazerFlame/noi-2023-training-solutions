#include<bits/stdc++.h>

using namespace std;
typedef long long ll;

int main() {
    ll n, m;
    cin >> n >> m;
    vector<ll> s1(n, 0ll);
    for(ll& v : s1) {
        cin >> v;
    }
    s1.push_back(0ll);
    s1.push_back(0ll);
    
    vector<ll> s2;

    for(ll i = 0ll; i < n + 2; i ++) {
        for(ll j = i; j < n + 2; j++) {
            s2.push_back(s1[i] + s1[j]);
        }
    }

    ll ans = numeric_limits<ll>::min();

    sort(s2.begin(), s2.end());
    for(ll v : s2) {
        ll l = 0, r = s2.size();

        if(v > m) break;

        while(r - l > 1) {
            ll mid = (l + r) >> 1ll;

            if(v + s2[mid] <= m) l = mid;
            else r = mid;
        }

        ans = max(ans, v + s2[l]);
    }

    cout << ans;

    return 0;
}