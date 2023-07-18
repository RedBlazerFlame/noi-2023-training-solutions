#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const char letters[4] = {'K', 'B', 'H', 'Y'};
string num_to_str(ll mask, ll n) {
    string s;
    for(ll j = 0ll; j < n; j++) {
        s.append({letters[(mask >> (j << 1ll)) & 0b11]});
    }

    return s;
}

int main() {
    const ll MAX_N = 10;
    ll t;
    cin >> t;
    while(t--) {
        ll n;
        cin >> n;
        if(n > MAX_N) {
            cout << "PASS" << endl;
        } else {
            ll max_score = -1ll;
            vector<ll> best_combos;
            for(ll i = 0 ; i < (1ll << (n << 1ll)); i++) {
                bool valid = true;
                for(ll j = 0; j < n - 1; j++) {
                    for(ll k = j + 2ll; k < n; k += 2ll) {
                        ll mid = (j + k) >> 1ll;

                        if((((i >> (j << 1ll)) & 0b11) == ((i >> (mid << 1ll)) & 0b11))
                        && 
                        (((i >> (j << 1ll)) & 0b11) == ((i >> (k << 1ll)) & 0b11))
                        ) {
                            valid = false;
                            break;
                        }
                    }
                }

                if(valid) {
                    ll cur_score = 0ll;
                    for(ll j = 0ll; j < n; j++) {
                        cur_score += 4ll - ((i >> (j << 1ll)) & 0b11);
                    }

                    if(cur_score > max_score) {
                        max_score = cur_score;
                        best_combos.clear();
                        best_combos.push_back(i);
                    } else if(cur_score == max_score) {
                        best_combos.push_back(i);
                    }
                }
            }

            if(max_score == -1ll) {
                for(ll i = 0ll; i < n; i++) {
                    cout << 'K';
                }
                cout << endl;
            } else {
                for(ll best_combo : best_combos) {
                    for(char c : num_to_str(best_combo, n)) {
                        cout << c;
                    }
                    cout << endl;
                }
            }
        }
    }

    return 0;
}