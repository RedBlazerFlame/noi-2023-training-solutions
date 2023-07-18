#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const char letters[4] = {'K', 'B', 'H', 'Y'};
const int max_times_retry = 100;

string num_to_str(ll mask, ll n) {
    string s;
    for(ll j = 0ll; j < n; j++) {
        s.append({letters[(mask >> (j << 1ll)) & 0b11]});
    }

    return s;
}

bool check_valid(const vector<int>& a, int n) {

    for(int i = 0; i < n - 2; i++) {
        for(int j = i + 2; j < n; j += 2) {
            int mid = (i + j) >> 1;

            if(a[i] == a[mid] && a[mid] == a[j]) {
                return false;
            }
        }
    }

    return true;
}

int main() {
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;

        if(n == 1) {
            cout << "K" << endl;
            continue;
        }
        if(n == 2) {
            cout << "KK" << endl;
            continue;
        }
        if(n <= 10) {
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
            continue;
        }
        vector<int> sol(n, 0);
        
        int times_retried = 0;
        do {
            for(int i = 0; i < n - 2; i++) {
                for(int j = i + 2; j < n; j += 2) {
                    int mid = (i + j) >> 1;

                    if(sol[i] == sol[mid] && sol[mid] == sol[j]) {
                        if(times_retried % 3 == 0) {
                            sol[j] = (sol[j] + 1) & 0b11;
                        } else if(times_retried % 3 == 1) {
                            sol[mid] = (sol[mid] + 1) & 0b11;
                        } else {
                            sol[i] = (sol[i] + 1) & 0b11;
                        }
                    }
                }
            }

            times_retried++;
        } while((!check_valid(sol, n)) && times_retried > max_times_retry);

        if(!check_valid(sol, n)) {
            cout << "PASS" << endl;
        } else {
            for(int i = 0; i < n; i++) {
                    cout << letters[sol[i]];
                }
                cout << endl;
        }
    }
}