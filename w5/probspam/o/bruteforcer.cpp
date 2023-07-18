/*
Insights: The thing is always a tree, with 1 as the root
So we go in reverse order
Let 2 mean destroyed
1 mean warned
and 0 mean processing
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> c(n, -1);
    for(int i = 1; i < n; i++) {
        cin >> c[i];
        c[i]--;
    }

    int ans = 0;
    for(int i = 0; i < (1 << n); i++) {
        bool valid = true;
        for(int j = 1; j < n; j++) {
            int other = c[j];
            if(((i >> j) & 1) && (i >> other) & 1) valid = false;
        }

        if(valid) ans = max(ans, __popcount(i));
    }

    cout << ans << endl;
    return 0;
}