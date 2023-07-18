#include <bits/stdc++.h>
using namespace std;
const int N = 2020;
int dp[N * 2][N];
int ans[N * 2][N];
const int mod = 1e9 + 7;
int main(){
    for(int i = 1; i <= 4000; i++){
        for(int j = 1; j <= 2000; j++){
            if(j == 1) dp[i][j] = (i % 2 == 1);
            else if(i % 2 == j % 2){
                dp[i][j] = (dp[i][j] + dp[i - 1][j - 1]);
            }
            dp[i][j] = (dp[i][j] + dp[i - 1][j]) % mod;
        }
    }
    int tt;
    cin >> tt;
    while(tt--){
        int r,s;
        cin >> r >> s;
        cout << dp[s][r] << endl;
    }
}