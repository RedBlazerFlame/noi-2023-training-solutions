#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main () {
    const int mod = 998244353;
    int n, m;
    cin >> n >> m;
    vector<vector<bool>> adj;
    vector<tuple<int, int>> edges;
    for(int i = 0; i < n; i++) {
        vector<bool> row(n, false);
        adj.push_back(row);
    }

    for(int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        adj[u][v] = true;
        adj[v][u] = true;

        edges.push_back({u, v});
    }

    ll count = 0;
    // Brute force
    for(int i1 = 0; i1 < n; i1++) {
        for(int i2 = 0; i2 < n; i2++) {
            if(i2 == i1) continue;
            for(int i3 = 0; i3 < n; i3++) {
                if(i3 == i2 || i3 == i1) continue;
                for(int i4 = 0; i4 < n; i4++) {
                    if(i4 == i3 || i4 == i2 || i4 == i1) continue;
                    for(int i5 = 0; i5 < n; i5++) {
                        if(i5 == i4 || i5 == i3 || i5 == i2 || i5 == i1) continue;
                        for(int i6 = 0; i6 < n; i6++) {
                            if(i6 == i5 || i6 == i4 || i6 == i3 || i6 == i2 || i6 == i1) continue;
                            if(adj[i1][i2] && adj[i2][i3] && adj[i3][i4] && adj[i4][i5] && adj[i5][i6] && adj[i6][i1]) {
                                count = (count + 1) % mod;
                            }
                        }
                    }
                }
            }
        }    
    }

    cout << count << endl;
    return 0;
}