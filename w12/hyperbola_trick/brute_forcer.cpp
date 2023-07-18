#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll f(ll n) {
    return n * n;
}

ll g(ll n) {
    return n * n * n;
}

int main() {
    ll n;
    cin >> n;

    ll ans = 0ll;

    for(ll i = 1; i <= n; i++) {
        ans += f(i) * g(n / i);
    }

    cout << ans << endl;

    return 0;
}