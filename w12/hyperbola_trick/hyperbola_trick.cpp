/*
Compute: S = sum_x f(x)g(n // x) from x in [1, n]
S = sum g(v) (sum (f(x)) for x s.t. n // x == v) for v in {n // x}

So, given v, we need to find all x s.t. floor(n / x) = v
Clearly, n >= vx if floor(n / x) >= v
Also, if floor(n / x) < v + 1, we have n < (v + 1)x.
Implication: floor(n / (v + 1)) < x <= floor(n / v)

So if f_int(x) is the antiderivative of f (in the calculus of sequences), then:
(sum (f(x)) for x s.t. n // x == v) = f_int(floor(n / v)) - f_int(floor(n / (v + 1)))

S = sum g(v) (f_int(floor(n / v)) - f_int(floor(n / (v + 1)))) for v in {n // x}

This example program computes sum_{1, n} x^2 floor(n / x)^3

n / floor(sqrt(n)) generates everything gte ceil(sqrt(n))
n / ceil(sqrt(n)) onwards generates everything lte floor(sqrt(n))
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll f(ll n) {
    return n * n;
}

ll f_int(ll n) {
    return n * (n + 1ll) * ((n << 1ll) + 1ll) / 6ll;
}

ll g(ll n) {
    return n * n * n;
}

ll floor_sqrt(ll n) {
    ll l = 0ll, r = n;

    while(r - l > 1ll) {
        ll m = (l + r) >> 1ll;

        if(m * m > n) r = m;
        else l = m;
    }

    return l;
}

ll ceil_sqrt(ll n) {
    ll l = 0ll, r = n;

    while(r - l > 1ll) {
        ll m = (l + r) >> 1ll;

        if(m * m >= n) r = m;
        else l = m;
    }

    return r;
}

int main() {
    ll n;
    cin >> n;

    ll ans = 0ll;
    ll sqrtn = floor_sqrt(n);
    ll ceil_sqrtn = ceil_sqrt(n);

    // For x <= sqrt(n)
    for(ll i = 1; i <= sqrtn; i++) {
        ans += f(i) * g(n / i);
    }

    // Iterating through floor(n / x) == v
    ll maxv = n / ceil_sqrtn;

    for(ll i = 1; i <= maxv; i++) {
        ans += g(i) * (f_int(n / i) - f_int(n / (i + 1)));
    }

    // Accounting for when n is a square
    if(sqrtn * sqrtn == n) {
        ans -= f(sqrtn) * g(sqrtn);
    }

    cout << ans << endl;

    return 0;
}