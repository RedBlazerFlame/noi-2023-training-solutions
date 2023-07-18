#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int memo[4001][4001];
string s;
string t;
int max_suff(int n, int m) {
    int& ans = memo[n][m];
    if(ans == -1) {
        if(min(m, n) == 0) {
            ans = 0;
            return ans;
        }
        ans = (s[n - 1] == t[m - 1] ? max_suff(n - 1, m - 1) + 1 : 0);
    }
    return ans;
}

int main() {
    for(int i = 0; i < 4001; i++) {
        for(int j = 0; j < 4001; j++) {
            memo[i][j] = -1;
        }
    }

    cin >> s >> t;
    int n, m;
    n = s.size();
    m = t.size();

    int ans = 0;
    for(int i = 0; i <= n; i++) {
        for(int j = 0; j <= m; j++) {
            ans = max(ans, max_suff(i, j));
        }
    }

    cout << ans << endl;

    return 0;
}