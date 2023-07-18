/*
FFT:
Evaluate poly P(x) = ax^(2^n - 1) + ...
at 2^n distinct roots

a0 + a1 x + a2 x^2 + ...

P(x) = (a0 + a2x^2 + a4x^4 + ...) + x(a1 + a3x^2 + ...)
= E(x^2) + xO(x^2)
Let w be this primitive root of unity

P(w^j) = E(w^(2j)) + w^j O(w^2j)

for i in range(j >> 1):
    P(w^i) = E(w^(2i)) + w^i O(w^2i)
    P(w^(i + j >> 1)) = E(w^(2i)) - w^i O(w^2i)

ab == 1 mod p
let q' = -q
ba + q'p = 1
(q' - bk)a' + bp' = 1
q'a' + b(p' - a'k) = 1
b(p' - ka') + q'a' = 1
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void print_vec(const vector<ll>& vec) {
    for(const ll & v : vec) {
        cout << v << " ";
    }
    cout << endl;
}

ll pos_mod(ll n, ll mod) {
    return ((n % mod) + mod) % mod;
}

/*
ab == 1 mod p
ab + pq = 1
(p - ka)b' + aq' = 1
a(q' - kb') + pb' = 1
*/
pair<ll, ll> ex_euclid(ll a, ll p) {
    if(a == 0ll && p == 1ll) return {0ll, 1ll};
    ll k = p / a;
    auto [bp, qp] = ex_euclid(p - k * a, a);
    return {qp - k * bp, bp};
}

ll mod_inv(ll a, ll mod) {
    auto [inv, _] = ex_euclid(a, mod);
    return inv;
}

ll next_largest_pow2(ll n) {
    n--;
    n |= n >> 1ll;
    n |= n >> 2ll;
    n |= n >> 4ll;
    n |= n >> 8ll;
    n |= n >> 16ll;
    n |= n >> 32ll;

    return n + 1ll;
}

ll flog_n(ll n) {
    for(ll i = 63ll; i >= 0ll; i--) {
        if((n >> i) & 0b1) return i;
    }
    return -1ll;
}

// ! In-place
vector<ll>& extend_poly(vector<ll>& poly, ll new_n) {
    ll poly_size = poly.size();
    ll zeros_to_put = new_n - poly_size;

    for(ll i = 0; i < zeros_to_put; i++) {
        poly.push_back(i);
    }

    return poly;
}

// ! In-place
vector<ll>& poly_scalar_mult(vector<ll>& poly, ll scalar) {
    for(ll& v : poly) {
        v *= scalar;
    }

    return poly;
}

vector<ll>& poly_scalar_mod(vector<ll>& poly, ll mod) {
    for(ll& v : poly) {
        v %= mod;
    }

    return poly;
}

vector<ll>& poly_scalar_pos_mod(vector<ll>& poly, ll mod) {
    for(ll& v : poly) {
        v = pos_mod(v, mod);
    }

    return poly;
}


// ! Assumes poly is a power of 2
vector<ll> fft(const vector<ll>& a, ll start, ll skip, ll root, ll mod) {
    if((1 << skip) == a.size()) {
        vector<ll> res;
        res.push_back(a[start]);
        return res;
    }
    ll squared_root = (root * root) % mod;
    ll seq_size = a.size() >> skip;
    ll half_seq_size = seq_size >> 1;
    vector<ll> even = fft(a, start, skip + 1ll, squared_root, mod);
    vector<ll> odd = fft(a, start + (1ll << skip), skip + 1ll, squared_root, mod);
    vector<ll> res(seq_size, 0ll);

    ll cur_wi = 1ll;
    for(ll i = 0ll; i < half_seq_size; i++) {
        res[i] = (even[i] + (cur_wi * odd[i]) % mod) % mod;
        res[i + half_seq_size] = (even[i] - (cur_wi * odd[i]) % mod) % mod;
        cur_wi = (cur_wi * root) % mod;
    }
    return res;
}

int main() {
    const ll MOD = 998244353ll;
    const ll ROOT = 31ll;
    ll actual_root = ROOT;
    const ll ROOT_PERIOD_LOG2 = 23ll;

    vector<ll> poly = {1ll, 2ll, 3ll, 4ll, 3ll, 2ll, 3ll, 2ll};
    extend_poly(poly, next_largest_pow2(poly.size()));

    ll poly_log_size = flog_n(poly.size());
    for(ll i = 0ll; i < ROOT_PERIOD_LOG2 - poly_log_size; i++) {
        actual_root = (actual_root * actual_root) % MOD;
    }

    vector<ll> res = fft(poly, 0, 0, actual_root, MOD);
    vector<ll> fft_inv = fft(res, 0, 0, mod_inv(actual_root, MOD), MOD);
    poly_scalar_mult(fft_inv, mod_inv(poly.size(), MOD));
    poly_scalar_pos_mod(fft_inv, MOD);
    print_vec(fft_inv);

    return 0;
}