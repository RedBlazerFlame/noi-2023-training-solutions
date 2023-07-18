#include <bits/stdc++.h>
using namespace std;

/*
Let's think about this a bit

This problem is actually equivalent to finding two
disjoint subarrays such that they maximize the number of
1s flipped and minimize the number of 0s flipped

Here are some cases:
1. '' -> 0
2. '0' -> 0, '1' -> 1
3. Flip none. The answer is the number of 1s
4. Flip one subarray. This is Flip A
5. Flip two subarrays. First apply Flip A,
then, divide and conquer on either side of the subarray 
*/

int ones_if_flip(string s, int i0, int j0, int i1, int j1) {
    int ans = 0;
    
    for(int i = 0; i < s.length(); i++) {
        ans += (int)(s[i] - '0') ^ (i0 <= i && i <= j0 ? 1 : 0) ^ (i1 <= i && i <= j1 ? 1 : 0);
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
        for(int i0 = 0; i0 < n; i0++) {
            for(int j0 = i0; j0 < n; j0++) {
                for(int i1 = i0; i1 < n; i1++) {
                    for(int j1 = i1; j1 < n; j1++) {
                        ans = min(ans, ones_if_flip(s, i0, j0, i1, j1));
                    }
                }
            }
        }

        cout << ans << "\n";
    }
}