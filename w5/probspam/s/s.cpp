#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int t;
    cin >> t;
    while(t--) {
        int n, d;
        cin >> n >> d;
        vector<int> v(n, 0);
        vector<int> c(n, 0);

        for(int i = 0; i < n; i++) {
            cin >> v[i] >> c[i];
        }

        vector<int> dp(d + 1, 0);

        for(int i = 0; i <= d; i++) {
            int maxv = 0;

            for(int j = 0; j < n; j++) {
                if(i - c[j] < 0) continue;
                maxv = max(maxv, dp[i - c[j]] + v[j]);
            }
            dp[i] = maxv;
        }

        cout << dp[d] << endl;
    } 
    return 0;
}