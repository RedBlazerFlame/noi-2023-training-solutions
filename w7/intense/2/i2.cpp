/*
dp(m, n, I) = max(dp(m_minI, n, O), dp(m, n_minI, O)) + (m_minI < m && n_minO < n)

dp(m, n, I) = max(dp(), 1 + dp(m + 1, n, O) if dp)

Okay, so I made a mistake ;-;

What I need to do is to take out the start, not the end

(m, n, I) -> max
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

inline char to_io(int i) {
    return (i == 0 ? 'O' : 'I');
}

/*
i = 1 -> "I"
i = 0 -> "O"
*/
vector<vector<vector<int>>> memo;
int M, N;
string s, t;
int dp(int m, int n, int i) {
    int& ans = memo[m][n][i];
    if(ans == -1) {
        if(m == M && n == N) return 0;
        if(m < M) {
            ans = max(ans, dp(m + 1, n, i));
            if(s[m] == to_io(i)) ans = max(ans, dp(m + 1, n, i ^ 1) + 1);
        }
        if(n < N) {
            ans = max(ans, dp(m, n + 1, i));
            if(t[n] == to_io(i)) ans = max(ans, dp(m, n + 1, i ^ 1) + 1);
        }
    }
    return ans;
}

int main() {
    cin >> M >> N;
    cin >> s >> t;
    for(int i = 0; i < M + 1; i++) {
        vector<vector<int>> a1;
        for(int j = 0; j < N + 1; j++) {
            vector<int> a2(2, -1);
            a1.push_back(a2);
        }
        memo.push_back(a1);
    }
    int ans = dp(0, 0, 1);
    ans = ans - ((ans & 1) ^ 1);
    ans = max(ans, 0);

    cout << ans << endl;

    return 0;
}