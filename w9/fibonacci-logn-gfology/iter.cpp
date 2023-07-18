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

f(0), f(1), f(2), f(3), f(4), ..., f(n - 1)
f(0), f(2), ..., f(2^1 (n - 1))
f(0), f(4), ..., f(2^2 (n - 1))
...
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

ll apply_recur(const vector<ll>& recur, const vector<ll>& inputs) {
    ll res = 0ll;
    for(int i = 0; i < inputs.size(); i++) {
        res = dmod(res - dmod(recur[i + 1] * inputs[i]));
    }
    return res / recur[0];
}

template<typename I1, typename I2>
typename iterator_traits<I1>::value_type apply_recur_iter(I1 recur, I1 recur_end, I2 inputs, I2 inputs_end) {
    ll res = 0ll;

    auto recur_begin = *recur;
    recur = next(recur);


    while(inputs != inputs_end && recur != recur_end) {
        res = dmod(res - dmod((*recur) * (*inputs)));
        inputs = next(inputs);
        recur = next(recur);
    }
    return res / recur_begin;
}

int main() {
    ll l;
    ll n;
    cin >> l >> n;
    ll cur_n = n;

    vector<ll> recur(l + 1, 0);
    recur[0] = 1;
    for(ll i = 1; i <= l; i++) {
        cin >> recur[i];
        recur[i] *= -1;
    }
    vector<ll> base_cases(l, 0);
    for(ll& v : base_cases) {
        cin >> v;
    }

    while(cur_n > 0) {
        for(ll i = 0; i < l; i++) {
            base_cases.push_back(apply_recur_iter<std::vector<ll>::iterator, std::vector<ll>::reverse_iterator>(recur.begin(), recur.end(), base_cases.rbegin(), next(base_cases.rend(), i)));
        }

        ll cur_n_mod_2 = cur_n & 0b1ll;

        for(ll i = 0; i < l; i++) {
            base_cases[i] = base_cases[(i << 1) | cur_n_mod_2];
        }
        base_cases.resize(l);
        cur_n >>= 1;
        recur = next_recur(recur);
    }

    cout << base_cases[0] << endl;
    return 0;
}