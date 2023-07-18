/*
-1 -1 -1 3 -1

So in subtask 5, the goal is to have the 
smallest number of inversions(?)
equivalently, it is to maximize the
length of the longest increasing subsequence
in O(N)

Ok, let's not do that for now, since too difficult

Okay subtask 1
Idea: generate all permutations
check if the permutation is valid
If it is, go through all ks and maximize
congratulations, you have your answer
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void print_vec(const vector<ll>& v) {
    for(const ll& vv : v) {
        cout << vv << " ";
    }
    cout << endl;
}

ll factorial(ll n) {
    ll ans = 1ll;

    for(ll i = 1ll; i <= n; i++) {
        ans *= i;
    }

    return ans;
}

vector<ll> solve_subtask_1(ll n, const vector<ll>& a, const vector<ll>& c) {
    vector<ll> cur_perm;
    for(ll i = 0ll ; i < n; i++) {
        cur_perm.push_back(i);
    }

    ll factn = factorial(n);

    vector<ll> ans(n, numeric_limits<ll>::min());
    for(ll i = 0; i < factn; i++) {
        bool is_valid = true;

        for(ll j = 0; j < n; j++) {
            if(a[j] != -1 && a[j] != cur_perm[j]) is_valid = false;
        }
        if(is_valid) {
            ll maxt = numeric_limits<ll>::min();
            ll cursumcost = 0ll;
            for(ll j = 0; j < n; j++) {
                if(cur_perm[j] > maxt) {
                    maxt = cur_perm[j];
                    cursumcost += c[cur_perm[j]];
                }
                ans[j] = max(ans[j], cursumcost);
            }
        }
        next_permutation(cur_perm.begin(), cur_perm.end());
    }

    return ans;
}

vector<ll> solve_subtask_2(ll n, const vector<ll>& a, const vector<ll>& c) {

    vector<ll> ans(n, 0);

    partial_sum(c.rbegin(), c.rend(), ans.begin(), plus<ll>());
    return ans;
}

int main() {
    ll n;
    cin >> n;

    vector<ll> a(n, 0);
    vector<ll> c(n, 0);

    for(ll& av : a) {
        cin >> av;
        if(av > 0) av--;
    }

    for(ll& cv : c) {
        cin >> cv;
    }

    if(n <= 8) {
        print_vec(solve_subtask_1(n, a, c));
    } else {
        // Assume that subtask 2 holds
        print_vec(solve_subtask_2(n, a, c));
    }

    return 0;
}