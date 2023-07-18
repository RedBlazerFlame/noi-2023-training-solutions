/*
Time complexity: O(N^2 2^N) general case (which should pass 1-2)

Subtask 3
This is a rectangle (wow)
So what it looks like is this:

T---T
-T-T-
--T--
-----
--T--
-T-T-
T---T

T--T
-TT-
----
----
-TT-
T--T

We just have to construct this, essentially

Subtask 4
For this one, we go through every x-coordinate and get the 
smallest Y and largest Y
Well, we can probably sort the values by Y
and then I can keep a set of encountered Xs
// ! Warning: the set may increase the constant factor
if an X has been encountered, then don't bother with it anymore

Now do the same, but going in reverse order of Y
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<bool> solve16(ll n, const vector<tuple<ll, ll>>& pos) {
    vector<ll> xs;
    vector<ll> ys;
    for(const tuple<ll, ll>& tup : pos) {
        ll x, y;
        tie(x, y) = tup;
        xs.push_back(x);
        ys.push_back(y);
    }

    
    for(ll i = 0; i < (1 << n); i++) {
        vector<bool> third_satisfied(n, false);

        ll has_bad_x_coords = false;
        for(ll targx : xs) {
            /*
            TODO count the number of towers with this x
            mark the ones in the middle as "satisfied"
            */

            ll count_towers = 0ll;
            ll min_tower_y = numeric_limits<ll>::max();
            ll max_tower_y = numeric_limits<ll>::min();
            for(ll j = 0ll; j < n; j++) {
                ll x, y;
                tie(x, y) = pos[j];
                if(x == targx) {
                    if((i >> j) & 1) {
                        count_towers++;
                        third_satisfied[j] = true;
                        min_tower_y = min(min_tower_y, y);
                        max_tower_y = max(max_tower_y, y);
                    }
                }
            }
            if(count_towers > 2ll) {
                has_bad_x_coords = true;
                break;
            }

            for(ll j = 0ll; j < n; j++) {
                ll x, y;
                tie(x, y) = pos[j];
                if(x == targx) {
                    if(min_tower_y <= y && y <= max_tower_y) {
                        third_satisfied[j] = true;
                    }
                }
            }
        }
        if(has_bad_x_coords) continue;

        ll has_bad_y_coords = false;
        for(ll targy : ys) {
            /*
            TODO count the number of towers with this y
            mark the ones in the middle as "satisfied"
            */

            ll count_towers = 0ll;
            ll min_tower_x = numeric_limits<ll>::max();
            ll max_tower_x = numeric_limits<ll>::min();
            for(ll j = 0ll; j < n; j++) {
                ll x, y;
                tie(x, y) = pos[j];
                if(y == targy) {
                    if((i >> j) & 1) {
                        count_towers++;
                        third_satisfied[j] = true;
                        min_tower_x = min(min_tower_x, x);
                        max_tower_x = max(max_tower_x, x);
                    }
                }
            }
            if(count_towers > 2ll) {
                has_bad_y_coords = true;
                break;
            }

            for(ll j = 0ll; j < n; j++) {
                ll x, y;
                tie(x, y) = pos[j];
                if(y == targy) {
                    if(min_tower_x <= x && x <= max_tower_x) {
                        third_satisfied[j] = true;
                    }
                }
            }
        }
        if(has_bad_y_coords) continue;

        if(all_of(third_satisfied.begin(), third_satisfied.end(), [](bool v) {return v;})) {
            vector<bool> ans;
            for(ll j = 0ll; j < n; j++) {
                ans.push_back((i >> j) & 1);
            }
            return ans;
        }
    }

    return *(new vector<bool>());
}

vector<bool> solve_subtask_3(ll b, ll a) {
    vector<bool> ans;

    for(ll i = 0ll; i < b; i++) {
        for(ll j = 0ll; j < a; j++) {
            ll ni = (i >= (b >> 1) ? b - i - 1ll : i);
            ll nj = (j >= (a >> 1) ? a - j - 1ll : j);
            ans.push_back(ni == nj);
        }
    }

    return ans;
}

void print_bool_vec(const vector<bool>& vec) {
    for(bool v : vec) {
        cout << v;
    }
    cout << endl;
}

bool satisfies_subtask_3(ll n, vector<tuple<ll, ll>> pos) {
    ll b, a;
    tie(b, a) = pos[n - 1];

    // Check if subtask 3
    if(a * b != n) return false;

    for(ll j = 0ll; j < a; j++) {
        for(ll i = 0ll; i < b; i++) {
            ll curx, cury;
            tie(curx, cury) = pos[i * a + j];
            if(curx != i + 1 || cury != j + 1) return false;
        }
    }

    return true;
}

vector<bool> solve_subtask_4(ll n, const vector<tuple<ll, ll>>& pos) {
    /*
    For this one, we go through every x-coordinate and get the 
    smallest Y and largest Y
    Well, we can probably sort the values by Y
    and then I can keep a set of encountered Xs
    // ! Warning: the set may increase the constant factor
    if an X has been encountered, then don't bother with it anymore

    Now do the same, but going in reverse order of Y
    */
    vector<tuple<ll, ll, ll>> spos;
    vector<bool> ans(n, false);
    spos.reserve(n);
    for(ll i = 0ll; i < n; i++) {
        ll x, y;
        tie(x, y) = pos[i];

        spos.push_back({x, y, i});
    }

    // Phase 1: increasing X
    unordered_set<ll> ys;
    sort(spos.begin(), spos.end(), [](tuple<ll, ll, ll> a, tuple<ll, ll, ll> b) {return get<0>(a) < get<0>(b);});
    for(const tuple<ll, ll, ll> cpos : spos) {
        if(ys.count(get<1>(cpos)) == 0) {
            ans[get<2>(cpos)] = true;
        }
        ys.insert(get<1>(cpos));
    }

    // Phase 2: decreasing X
    ys.clear();
    sort(spos.begin(), spos.end(), [](tuple<ll, ll, ll> a, tuple<ll, ll, ll> b) {return get<0>(a) > get<0>(b);});
    for(const tuple<ll, ll, ll> cpos : spos) {
        if(ys.count(get<1>(cpos)) == 0) {
            ans[get<2>(cpos)] = true;
        }
        ys.insert(get<1>(cpos));
    }

    return ans;
}

int main() {
    ll n;
    cin >> n;

    vector<tuple<ll, ll>> pos;
    for(ll i = 0ll; i < n; i++) {
        ll x, y;
        cin >> x >> y;
        pos.push_back({x, y});
    }

    bool subtask3 = satisfies_subtask_3(n, pos);

    if(subtask3) {
        ll b, a;
        tie(b, a) = pos[n - 1];

        vector<bool> ans = solve_subtask_3(b, a);
        print_bool_vec(ans);
    } else if(n <= 16) {
        vector<bool> ans = solve16(n, pos);
        print_bool_vec(ans);
    } else {
        // Assume subtask 4
        vector<bool> ans = solve_subtask_4(n, pos);
        print_bool_vec(ans);
    }
    
    return 0;
}