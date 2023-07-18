#include <bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(int &x: a){
        cin >> x;
    }
    for(int i = 1; i <= n; i++){
        int cur = i;
        while(cur != 1 && a[cur - 1] < a[cur / 2 - 1]){
            swap(a[cur - 1], a[cur / 2 - 1]);
            cur /= 2;
        }
    }
    vector<int> pref(n + 1);
    for(int i = 1; i <= n; i++){
        pref[i] = pref[i - 1] + a[i - 1];
    }
    int q;
    cin >> q;
    while(q--){
        int l,r;
        cin >> l >> r, l--;
        cout << pref[r] - pref[l] << endl;
    }
}