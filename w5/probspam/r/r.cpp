/*
Yet another dp problem
let dp[d] be the minimum number of bullets
required to get a value of at least d
min_i(dp[d - v[i]] + c[i])
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
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
        for(int i = 1; i < d + 1; i++) {
            int minv = std::numeric_limits<int>::max();
            for(int j = 0; j < n; j++) {
                int cur = (i - v[j] < 0 ? c[j] : dp[i - v[j]] + c[j]);
                if(cur < minv) minv = cur;
            }
            dp[i] = minv;
        }

        cout << dp[d] << endl;
    }

    return 0;
}