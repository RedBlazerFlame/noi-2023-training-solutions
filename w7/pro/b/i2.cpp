/*
Idea: Prime factorize the number
floor div the powers by 2
add 1
GG
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll fastpow(ll base, ll p) {
    if(p == 0ll) return 1ll;
    ll sqrtres = fastpow(base, p >> 1ll);
    return (p & 1ll ? base : 1ll) * sqrtres * sqrtres;
}

ll max_sqrt_n = 1'000'003ll;
int main() {
    ll n;
    cin >> n;

    ll sieve_bound = min(n, max_sqrt_n);
    vector<bool> isprime(sieve_bound + 1, true);
    isprime[0] = false;
    isprime[1] = false;
    
    for(ll p = 0; p <= sieve_bound; p++) {
        if(isprime[p]) {
            for(ll mult = 2; mult * p <= sieve_bound; mult++) {
                isprime[mult * p] = false;
            }
        }
    }

    ll ans = 1ll;
    for(ll p = 0; p <= sieve_bound; p++) {
        if(isprime[p]) {
            ll cur_fact_count = 0;
            while(n % p == 0) {
                n /= p;
                cur_fact_count++;
            }

            ans *= fastpow(p, cur_fact_count >> 1ll);
        }
    }

    cout << ans + 1 << endl;
    return 0;
}