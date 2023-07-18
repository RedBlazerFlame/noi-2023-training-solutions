/*
               ^p
[ 0 1 0 0 0 0 ] [ f(1) = 1 ]
[ 0 0 1 0 0 0 ] [ f(2) = 1 ]
[ 0 0 0 1 0 0 ] [ f(3) = 1 ]
[ 0 0 0 0 1 0 ] [ f(4) = 2 ]
[ 1 0 0 0 1 0 ] [ f(5) = 2 ]
[ 0 0 0 0 1 1 ] [ S(4) = 5 ]

f(n - 1) + S(n - 2) = S(n - 1)

S(4 + p)
n = 4 + p
p = n - 4
*/



#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll MOD = 1'000'000'007;

vector<vector<ll>> matmulmod(const vector<vector<ll>>& m1, const vector<vector<ll>>& m2, const ll mod) {
    vector<vector<ll>> res;
    ll n = m1[0].size();

    for(ll i = 0ll; i < n; i++) {
        vector<ll> row;
        
        for(ll j = 0ll; j < n; j++) {
            ll dot = 0ll;
            
            for(ll k = 0ll; k < n; k++) {
                dot = (dot + m1[i][k] * m2[k][j]) % mod;
            }

            row.push_back(dot);
        }

        res.push_back(row);
    }

    return res;
}

vector<ll> matvecmulmod(const vector<vector<ll>>& m, const vector<ll>& v, const ll mod) {
    vector<ll> res;
    ll n = v.size();

    for(ll i = 0ll; i < n; i++) {
        ll ans = 0ll;
        for(ll j = 0ll; j < n; j++) {
            ans = (ans + m[i][j] * v[j]) % mod;
        }
        res.push_back(ans);
    }

    return res;
}

vector<vector<ll>> matpowmod(const vector<vector<ll>>& mat, ll p, ll mod) {
    if(p == 1ll) return mat;
    vector<vector<ll>> sqrtmat = matpowmod(mat, p >> 1ll, mod);
    vector<vector<ll>> squaredmat = matmulmod(sqrtmat, sqrtmat, mod);
    if(p & 1ll) return matmulmod(mat, squaredmat, mod);
    else return squaredmat;
}

int main() {
    ll t;
    cin >> t;
    

    ll lookup[] = {0ll, 1ll, 2ll, 3ll, 5ll, 7ll};
    while(t--) {
        ll n;
        cin >> n;
        if(n <= 5) {
            cout << lookup[n] + 2ll << endl;
        } else {
            cout << (matvecmulmod(
                matpowmod(
                    {
                        { 0, 1, 0, 0, 0, 0 },
                        { 0, 0, 1, 0, 0, 0 },
                        { 0, 0, 0, 1, 0, 0 },
                        { 0, 0, 0, 0, 1, 0 },
                        { 1, 0, 0, 0, 1, 0 },
                        { 0, 0, 0, 0, 1, 1 },
                    },
                    n - 4ll,
                    MOD
                ), 
                {1ll, 1ll, 1ll, 2ll, 2ll, 5ll},
                MOD
            )[5] + 2ll) % MOD << endl;
        }
    }
    return 0;
}