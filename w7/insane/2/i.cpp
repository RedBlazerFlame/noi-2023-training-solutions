/*
Guess who has a bitmask dp solution
that will work on the first subtask?
Heh, that's right, STARLIGHT ANYA

Also, subtask 2 is cute because you just sort the gyms by X_i
and then find the longest prefix of X that works

All in all, 24 points ^^

I will O(n^2) later ^^
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<ll> x;
vector<ll> l;
ll n;
bool memo[1 << 10] = {false};
bool solved[1 << 10] = {false};
bool poss(int S) {
    bool& ans = memo[S];

    if(!solved[S]) {
        if(S == 0) {
            ans = true;
            return ans;
        }
        ans = false;
        ll sumx = 0;
        for(int i = 0; i < 10; i++) {
            sumx += ((S >> i) & 1 ? x[i] : 0);
        }

        for(int i = 0; i < 10; i++) {
            if((S >> i) & 1) {
                if(poss(S ^ (1 << i)) && (sumx - x[i]) <= l[i]) {
                    ans = true;
                    break;
                }
            }
        }
    }
    solved[S] = true;
    return ans;
}

ll subtask2_solve(vector<ll> x, ll l) {
    sort(x.begin(), x.end());

    ll sum = 0ll;
    ll i = 0ll;
    ll n = x.size();
    while(i < n && sum <= l) {
        sum += x[i];
        i++;
    }
    return i;
}

int main() {
    cin >> n;

    for(ll i = 0ll; i < n; i++) {
        ll cur;
        cin >> cur;
        x.push_back(cur);
    }

    for(ll i = 0ll; i < n; i++) {
        ll cur;
        cin >> cur;
        l.push_back(cur);
    }

    if(n <= 10) {
        poss((1 << n) - 1);

        int ans = 0;

        for(int i = 0; i < (1 << 10); i++) {
            if(memo[i]) {
                ans = max(ans, __popcount(i));
            }
        }

        cout << ans;
    } else {
        // Assume subtask 2 constraints
        cout << subtask2_solve(x, l[0]) << endl;
    }

    return 0;
}