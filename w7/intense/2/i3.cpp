/*
dp(m, n, I) = max(dp(m_minI, n, O), dp(m, n_minI, O)) + (m_minI < m && n_minO < n)

dp(m, n, I) = max(dp(), 1 + dp(m + 1, n, O) if dp)

Okay, so I made a mistake ;-;

What I need to do is to take out the start, not the end

(m, n, I) -> max

 OIOOI
O01201
O02
I1
O2
I3

11 1
IOIOOOOIOIO
I

5 5
OIOOI 
OOIOI
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
        ans = 0;
        if(m > 0) {
            // ans = max(ans, dp(m - 1, n, i));
            if(s[m - 1] == to_io(i)) ans = max(ans, dp(m - 1, n, i ^ 1) + 1);
        }
        if(n > 0) {
            // ans = max(ans, dp(m, n - 1, i));
            if(t[n - 1] == to_io(i)) ans = max(ans, dp(m, n - 1, i ^ 1) + 1);
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
    for(int i = 0; i < M + 1; i++) {
        for(int j = 0; j < N + 1; j++) {
            dp(i, j, 1);
            dp(i, j, 0);
        }
    }
    int ans = 0;

    for(int i = 0; i < M + 1; i++) {
        for(int j = 0; j < N + 1; j++) {
            int curans = memo[i][j][1];
            curans = curans - ((curans & 1) ^ 1);
            curans = max(curans, 0);
            ans = max(ans, curans);
        }
    }

    cout << ans << endl;

    // cout << "DEBUG\n" << endl;
    // cout << "O\n" << endl;
    // for(int i = 0; i < M + 1; i++) {
    //     for(int j = 0; j < N + 1; j++) {
    //         cout << memo[i][j][0] << "\t";
    //     }
    //     cout << "\n";
    // }
    // cout << "I\n" << endl;
    // for(int i = 0; i < M + 1; i++) {
    //     for(int j = 0; j < N + 1; j++) {
    //         cout << memo[i][j][1] << "\t";
    //     }
    //     cout << "\n";
    // }
    return 0;
}