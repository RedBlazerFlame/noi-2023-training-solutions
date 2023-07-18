#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll find_tri(ll num) {
    ll l = -1, r = num + 1;
    while(r - l > 1) {
        ll m = (l + r) >> 1;

        if(((m * (m + 1)) >> 1) <= num) l = m;
        else r = m;
    }

    return l;
}

char def_access(const vector<vector<char>>& v, ll i, ll j, char def = '.') {
    return (i < 0 || i >= (ll)v.size() || j < 0 || j >= (ll)v[0].size() ? def : v[i][j]);
}

int main () {
    ll t = 0;
    cin >> t;
    while(t--) {
        ll initk = 0;
        cin >> initk;
        ll k = initk;

        ll width = find_tri(initk);
        vector<vector<char>> sol;
        while(k > 0) {
            vector<char> row;
            ll largest_tri_ind = find_tri(k);
            k -= (largest_tri_ind * (largest_tri_ind + 1)) >> 1;
            
            for(ll i = 0; i < width; i++) {
                row.push_back(i < largest_tri_ind ? '#' : '.');
            }
            sol.push_back(row);
            if(k > 0) {
                vector<char> row;
                for(ll i = 0; i < width; i++) {
                    row.push_back('.');
                }
                sol.push_back(row);
            }
        }

        ll n = max(sol.size(),sol[0].size());

        cout << n << endl;
        for(ll i = 0; i < n; i++) {
            for(ll j = 0; j < n; j++) {
                cout << def_access(sol, i, j);
            }
            cout << "\n";
        }
        cout << flush;
    }
    return 0;
}