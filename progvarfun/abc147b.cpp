#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;
    int n = s.length();

    int ans = 0;
    for(int i = 0; i < (n >> 1); i++) {
        if(s[i] != s[n - i - 1]) {
            ans += 1;
        }
    }

    cout << ans << endl;
    return 0;
}