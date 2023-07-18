/*
f(x) = 1 / (1 - x - x^2)
(1 - x - x^2)(1 + x - x^2) = (1 - x^2)^2 - x^2 = x^4 - 3x^2 + 1
(1 - 3x^2 + x^4)(1 + 3x^2 + x^4)
(a0 + a1 x + a2 x^2 + a3 x^3 + ...)

(a0 + a1 x + a2 x^2 + a3 x^3 + ...)(a0 - a1 x + a2 x^2 - a3 x^3 + ...)
= (a0 + a2 x^2 + ...)^2 - x^2 (a1 + a3 x^2 + a5 x^4 + ...)^2

2 -> f(0) + f(1) = f(2)
3 -> f(0) + f(1) = f(2) -> f(1) + f(2) = f(3)
4 -> f(0) + f(1) = f(2) -> 3f(2) - f(0) = f(4)
5 -> f(5) = 3f(3) - f(1)
6 -> f(6) = 3f(4) - f(2)

|a| + |b| - 1
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll MOD = 20092010ll;
inline ll mod(ll n, ll q) {
    return ((n % q) + q) % q;
}
inline ll dmod(ll n) {
    return mod(n, MOD);
}

void print_vec(const vector<ll>& v) {
    for(const ll& i : v) {
        cout << i << " ";
    }
    cout << endl;
}

vector<ll> poly_mult(const vector<ll>& a, const vector<ll>& b) {
    vector<ll> prod(a.size() + b.size() - 1, 0);

    for(int i = 0; i < a.size(); i++) {
        for(int j = 0; j < b.size(); j++) {
            prod[i + j] = dmod(prod[i + j] + dmod(a[i] * b[j]));
        }
    }

    return prod;
}

vector<ll> next_recur(const vector<ll>& a) {
    vector<ll> even;
    vector<ll> odd;
    vector<ll> res(a.size(), 0);
    
    for(ll i = 0; i < a.size(); i++) {
        if(i & 1) odd.push_back(a[i]);
        else even.push_back(a[i]);
    }

    vector<ll> even_square = poly_mult(even, even);
    vector<ll> odd_square = poly_mult(odd, odd);

    for(ll i = 0; i < even_square.size(); i++) {
        res[i] = dmod(res[i] + even_square[i]);
    }
    for(ll i = 0; i < odd_square.size(); i++) {
        res[i + 1] = dmod(res[i + 1] - odd_square[i]);
    }
    return res;
}

ll apply_recurrence(const vector<ll>& recur, const vector<ll>& inputs) {
    ll res = 0ll;
    for(int i = 0; i < inputs.size(); i++) {
        res = dmod(res - dmod(recur[i + 1] * inputs[i]));
    }
    return res / recur[0];
}

ll flog2(ll n) {
    for(ll i = 63; i >= 0; i--) {
        if((n >> i) & 1) return i;
    }
    return -1ll;
}

vector<vector<ll>> recur_memo;
vector<ll> get_nth_recur(const vector<ll>& base_recur, ll n) {
    if(n == 0) return base_recur;
    if(n < recur_memo.size()) {
        return recur_memo[n];
    } else {
        vector<ll> res = next_recur(get_nth_recur(base_recur, n - 1));
        recur_memo.push_back(res);
        return res;
    }
}

map<ll, ll> nth_term_memo;
ll _calculate_nth_term(const vector<ll>& base_recur, const vector<ll>& base_cases, ll n) {
    if(n < base_cases.size()) return base_cases[n];
    if(nth_term_memo.count(n) > 0) return nth_term_memo[n];
    ll log_jump_size = flog2(n / (base_recur.size() - 1ll));
    vector<ll> recur_inputs;
    for(ll i = 1; i <= base_recur.size() - 1ll; i++) {
        recur_inputs.push_back(_calculate_nth_term(base_recur, base_cases, n - (1ll << log_jump_size) * i));
    }
    vector<ll> cur_recur = get_nth_recur(base_recur, log_jump_size);
    ll ans = apply_recurrence(cur_recur, recur_inputs);
    nth_term_memo[n] = ans;
    return ans;
}

ll calculate_nth_term(const vector<ll>& base_recur, const vector<ll>& base_cases, ll n) {
    recur_memo.clear();
    nth_term_memo.clear();

    return _calculate_nth_term(base_recur, base_cases, n);
}

int main() {
    ll l;
    cin >> l;
    vector<ll> recur(l + 1, 0ll);
    recur[0ll] = 1ll;
    for(ll i = 1; i <= l; i++) {
        cin >> recur[i];
        recur[i] *= -1ll;
    }
    vector<ll> base_cases(l, 0ll);
    for(ll& v : base_cases) {
        cin >> v;
    }
    ll t;
    cin >> t;
    while(t--) {
        ll n;
        cin >> n;
        cout << calculate_nth_term(recur, base_cases, n) << endl;
    }
    return 0;
}