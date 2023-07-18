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
    vector<int> c(n, 0);
    for(int i = 1; i < n; i++) {
        cin >> c[i];
        c[i]--;
    }

    vector<int> color(n, 0);
    int ans = 0;
    for(int i = n - 1; i >= 0; i--) {
        if(color[i] == 0) {
            ans++;
            color[c[i]] = 1;
        }
    }

    cout << ans << endl;
    return 0;
}