#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    int n, h;
    cin >> n >> h;
    vector<int> c(n, 0);
    for(int& cc : c) {
        cin >> cc;
    }
    vector<int> dp(h + 1, 0);
    for(int i = 1; i < h + 1; i++) {
        int minv = h;
        for(const int& cc : c) {
            if(i - cc < 0) continue;
            int curv = dp[i - cc] + 1;
            if(curv < minv) minv = curv;
        }
        dp[i] = minv;
    }
    cout << dp[h] << endl;

    return 0;
}