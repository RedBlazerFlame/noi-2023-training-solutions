#include <bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin >> n;
    vector<int> v(n);
    for(int &x: v){
        cin >> x;
    }
    vector<int> c(n);
    for(int &x: c){
        cin >> x;
    }
    int nd = accumulate(v.begin(), v.end(), 0);
    sort(c.rbegin(),c.rend());
    if(n < 3) cout << "NO";
    else{
        int can = c[0] + c[1] + c[2];
        if(nd <= can) cout << "YES";
        else cout << "NO";
    }
}