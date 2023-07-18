#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll maxn = 5000;

const ll MOD = 1'000'000'007ll;

bool def_access(const vector<bool>& s, ll i) {
    return (i < 0ll || i >= s.size() ? true : s[i]);
}

void convolve(vector<bool>& s) {
    vector<bool> res(s.size() + 2ll, false);
    for(ll i = 0ll; i < (ll)(s.size()) + 2ll; i++) {
        int bitmask = (def_access(s, i - 2ll) ? 4 : 0)
        | (def_access(s, i - 1ll) ? 2 : 0)
        | (def_access(s, i) ? 1 : 0);

        res[i] = bitmask == 0b000 || bitmask == 0b110 || bitmask == 0b111;
    }

    swap(s, res);

    // s.clear();
    // s.reserve(res.size());

    // for(ll v : res) {
    //     s.push_back(v);
    // }
}

// ll fastpow(ll base, ll p, ll m) {
//     ll res = 1;
//     for(ll i = 63ll; i >= 0ll; i--) {
//         res = (res * res) % m;
//         if((base >> i) & 0b1 == 1ll) res = (res * base) % m;
//     }

//     return res;
// }

// ll fastpow(ll base, ll p, ll m) {
//     if(p == 0ll) return 1ll;
//     ll smaller = fastpow(base, p >> 1ll, m);
//     return (((smaller * smaller) % m) * (p & 0b1 ? base : 1ll)) % m;
// }

ll to_mod(const vector<bool>& nums) {
    ll res = 0ll;

    ll len = nums.size();
    ll pow10 = 1ll;

    for(ll i = 0ll; i < len; i++) {
        if(nums[len - i - 1ll]) res = (res + pow10) % MOD;
        pow10 = (pow10 * 10ll) % MOD;
    }

    return res;
}

int main() {
    ll t;
    cin >> t;
    while(t--) {
        ll n;
        cin >> n;
        if(n > maxn) {
            cout << "PASS" << endl;
        } else {
            vector<bool> cur_bits = {true, false, false, false, false, true, false, true, false, true, true, true, true, true, false, false, true, true, true, true, true, false, true, false, false, true, true, true, false, false, true, false, false, false, true, true, false, true, false, true, false, true, false, true, false, true, true, true, true, false, true, false, true, false, true, true, false, true, true, false, false, false, false, false, true, true, false, true, false, true, true, true, true, true, false};
            // vector<bool> cur_bits = {false, false, false, true, false, true, false};
            // ll init_curbit_size = cur_bits.size();

            for(ll i = 0ll; i < n; i++) {
                convolve(cur_bits);
            }

            // for(ll i = n + init_curbit_size; i < cur_bits.size(); i++) {
            //     cout << cur_bits[i];
            // }

            // cout << endl;

            cout << to_mod(cur_bits) << endl;
        }
    }
    return 0;
}