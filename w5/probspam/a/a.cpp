#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int ones_if_flip(int n, string s, int i0, int i1) {
    int ans = 0;
    for(int i = 0; i < n; i++) {
        int c = s[i] - '0';
        int flippedC = c ^ (i0 <= i && i <= i1 ? 0b1 : 0b0);
        if(flippedC == 1) ans++;
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    int t;
    cin >> t;

    while(t--) {
        int n;
        string s;
        cin >> n;
        cin >> s;

        int ans = n;

        for(int i = 0; i < n - 1; i++) {
            for(int j = i; j < n; j++) {
                ans = min(ans, ones_if_flip(n, s, i, j));
            }
        }

        cout << ans << endl;
    }
    return 0;
}