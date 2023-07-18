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
    if(a == 0ll) return {0ll, 1ll};
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
        poly.push_back(0ll);
    }

    return poly;
}

vector<ll> extend_poly_pure(vector<ll> poly, ll new_n) {
    ll poly_size = poly.size();
    ll zeros_to_put = new_n - poly_size;

    for(ll i = 0; i < zeros_to_put; i++) {
        poly.push_back(0ll);
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

vector<ll>& poly_num_mult_inv(vector<ll>& poly, ll mod) {
    for(ll& v : poly) {
        v = mod_inv(v, mod);
    }

    return poly;
}

vector<ll> poly_num_mult_inv_pure(vector<ll> poly, ll mod) {
    for(ll& v : poly) {
        v = mod_inv(v, mod);
    }

    return poly;
}

vector<ll> hadamard_prod(const vector<ll>& a, const vector<ll>& b) {
    vector<ll> res(a.size(), 0ll);
    
    for(ll i = 0; i < a.size(); i++) {
        res[i] = a[i] * b[i];
    }

    return res;
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

ll reduce_root_period(ll root, ll plog2, ll poly_size, ll MOD) {
    ll reduction_amount = plog2 - flog_n(poly_size);
    for(ll i = 0ll; i < reduction_amount; i++) {
        root = (root * root) % MOD;
    }
    return root;
}

vector<ll> convolve(const vector<ll> a, const vector<ll>& b, ll ROOT, ll ROOT_PERIOD_LOG2, ll MOD) {
    const ll conv_size = a.size() + b.size() - 1ll;
    const ll conv_size_padded = next_largest_pow2(conv_size);
    ll actual_root = reduce_root_period(ROOT, ROOT_PERIOD_LOG2, conv_size_padded, MOD);

    vector<ll> padded_a = extend_poly_pure(a, conv_size_padded);
    vector<ll> padded_b = extend_poly_pure(b, conv_size_padded);

    vector<ll> a_fft = fft(padded_a, 0, 0, actual_root, MOD);
    vector<ll> b_fft = fft(padded_b, 0, 0, actual_root, MOD);
    vector<ll> fft_inv = fft(hadamard_prod(a_fft, b_fft), 0, 0, mod_inv(actual_root, MOD), MOD);
    poly_scalar_mult(fft_inv, mod_inv(conv_size_padded, MOD));

    fft_inv.resize(conv_size);
    return fft_inv;
}

/*
A / B = Q

A = BQ
F(A) = F(B) dot F(Q)
F(Q) = F(A) / F(B)
*/

/*
F(c) = F(a) * F(b)^-1
*/
vector<ll> deconvolve(const vector<ll> a, const vector<ll>& b, ll ROOT, ll ROOT_PERIOD_LOG2, ll MOD) {
    const ll conv_size = a.size() + b.size() - 1ll;
    const ll conv_size_padded = next_largest_pow2(conv_size);
    ll actual_root = reduce_root_period(ROOT, ROOT_PERIOD_LOG2, conv_size_padded, MOD);

    vector<ll> padded_a = extend_poly_pure(a, conv_size_padded);
    vector<ll> padded_b = extend_poly_pure(b, conv_size_padded);

    vector<ll> a_fft = fft(padded_a, 0, 0, actual_root, MOD);
    vector<ll> b_fft = fft(padded_b, 0, 0, actual_root, MOD);
    vector<ll> fft_inv = fft(hadamard_prod(a_fft, poly_num_mult_inv_pure(b_fft, MOD)), 0, 0, mod_inv(actual_root, MOD), MOD);
    poly_scalar_mult(fft_inv, mod_inv(conv_size_padded, MOD));

    return fft_inv;
}

int main() {
    const ll MOD = 998244353ll;
    const ll ROOT = 31ll;
    const ll ROOT_PERIOD_LOG2 = 23ll;

    vector<ll> p1 = {1ll, 2ll, 4ll, 8ll};
    vector<ll> p2 = {1ll, 2ll};

    vector<ll> p12div = deconvolve(p1, p2, ROOT, ROOT_PERIOD_LOG2, MOD);

    poly_scalar_pos_mod(p12div, MOD);

    print_vec(p12div);

    return 0;
}