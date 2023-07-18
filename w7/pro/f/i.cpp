#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main(){
    int tt;
    cin >> tt;
    while(tt--){
        ll x, n;
        cin >> x >> n;
        cout << x * n + n * (n + 1)/ 2 - n << endl;
    }
}