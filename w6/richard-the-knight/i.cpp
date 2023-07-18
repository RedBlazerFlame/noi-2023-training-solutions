#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/*
Sample in:
4 4
0 1 2 3 
4 5 6 7
8 9 10 11
12 13 14 15
Implementation Time: 9 minutes, 44 seconds, and 89 milliseconds
*/

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> grid;
    vector<vector<int>> dp;
    for(int i = 0; i < n; i++) {
        vector<int> dprow(m, -1);
        vector<int> row(m, 0);
        for(int& rowv : row) {
            cin >> rowv;
        }
        grid.push_back(row);
        dp.push_back(dprow);
    }

    // Base-case
    dp[0][0] = grid[0][0];

    // Transition
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(i == 0 && j == 0) continue;
            int ans = -1;
            if(i - 1 >= 0 && j - 2 >= 0 && dp[i - 1][j - 2] != -1) ans = max(ans, dp[i - 1][j - 2] + grid[i][j]);
            if(i - 2 >= 0 && j - 1 >= 0 && dp[i - 2][j - 1] != -1) ans = max(ans, dp[i - 2][j - 1] + grid[i][j]);
            dp[i][j] = ans;
        }
    }

    cout << dp[n - 1][m - 1] << endl;

    return 0;
}