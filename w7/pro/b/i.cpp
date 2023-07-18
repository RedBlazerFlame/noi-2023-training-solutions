#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main(){
    ll n;
    cin >> n;
    int ans = 0;
    for(ll i = 1; i * i <= n; i++) if(n % i == 0){
        ans++;
        if(i != n / i) ans++;
    }
    cout << ans;
}