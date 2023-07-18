/*
XXXXXXX   XXX
 XX XX      XXXX
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> vec2;

int main() {
    int t;
    cin >> t;

    while(t--) {
        ll n;
        cin >> n;
        vector<vec2> g;
        g.reserve(n);

        for(ll i = 0; i < n; i++) {
            ll l, r;
            cin >> l >> r;
            g.push_back({l, r});
        }

        sort(g.begin(), g.end(), [](vec2 a, vec2 b) {return a.second < b.second;});

        ll lct = 0;
        ll ans = 0;
        for(ll i = 0; i < n; i++) {
            ll l = g[i].first, r = g[i].second;
            if(l > lct) {
                lct = r;
                ans++;
            } 
        }

        cout << ans << endl;
    }
    return 0;
}