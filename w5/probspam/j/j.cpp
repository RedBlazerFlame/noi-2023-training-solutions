#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    int t;
    cin >> t;

    while(t--) {
        int n;
        cin >> n;

        vector<ll> v(n, 0);

        for(ll& cv : v) {
            cin >> cv;
        }

        ll maxsum = numeric_limits<ll>::min();
        for(int l = 0; l < n; l++) {
            ll cursum = 0;
            ll maxv = numeric_limits<ll>::min();
            for(int r = l; r < n; r++) {
                ll cur = v[r];
                cursum += cur;

                if(cur > maxv) maxv = cur;
                if(cursum - maxv > maxsum) maxsum = cursum - maxv;
            }
        }

        cout << maxsum << endl;
    }
    return 0;
}