#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll gcd(ll a, ll b) {
    while(a != 0) {
        ll r = b % a; b = a; a = r;
    }

    return b;
}

int main() {
    cout << gcd(69, 1337) << endl;
    cout << 420420420 % gcd(69, 1337) << endl;
    return 0;
}