#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main() {
    ll n;
    cin >> n;
    ll n_mod = n % 35;
    cout << n - n_mod + 3 + (n_mod <= 3 ? 0 : 35);
    return 0;
}