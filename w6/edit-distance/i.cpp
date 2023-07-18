#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    string s1, s2;
    cin >> s1 >> s2;
    int n = s1.size(), m = s2.size();
    vector<int> dp((n + 1) * (m + 1), 0);
    for(int i = 0; i < n + 1; i++) {
        for(int j = 0; j < m + 1; j++) {
            int ans = numeric_limits<int>::max();
            if(i > 0 && j > 0) {
                ans = min(ans, dp[(i - 1) * (m + 1) + j - 1] + (s1[i - 1] == s2[j - 1] ? 0 : 1));
                ans = min(ans, dp[(i - 1) * (m + 1) + j] + 1);
                ans = min(ans, dp[i * (m + 1) + j - 1] + 1);
            }
            else ans = max(i, j);
            dp[i * (m + 1) + j] = ans;
        }
    }

    cout << dp[(n + 1) * (m + 1) - 1] << endl;

    return 0;
}