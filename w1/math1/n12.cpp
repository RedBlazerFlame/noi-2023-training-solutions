#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll modpow(ll a, ll k, ll n) {
    if(k == 0) return 1;
    if(k & 1) return ((a % n) * modpow(a, k - 1, n)) % n;
    ll sqrt = modpow(a, k >> 1, n);
    return (sqrt * sqrt) % n;
}

int main() {
    // Expected: 64400 (based on python's built-in pow function)
    cout << modpow(37, 100000, 99991) << endl;
    return 0;
}