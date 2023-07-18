#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void dfs(int node, const vector<vector<int>>& in_adj, vector<bool>& vis, vector<int>& out) {
    if(vis[node]) return;
    vis[node] = true;
    for(int c : in_adj[node]) {
        dfs(c, in_adj, vis, out);
    }
    out.push_back(node);
}

int main() {
    while(true) {
        vector<vector<int>> in_adj;
        vector<vector<int>> out_adj;
        int n, m;
        cin >> n >> m;
        if(n == 0 && m == 0) return 0;
        for(int i = 0; i < n + 1; i++) {
            vector<int> in_row;
            vector<int> out_row;
            in_adj.push_back(in_row);
            out_adj.push_back(out_row);
        }
        for(int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            u--; v--;
            in_adj[v].push_back(u);
            out_adj[u].push_back(v);
        }
        for(int i = 0; i < n; i++) {
            if(out_adj[i].size() == 0) {
                in_adj[n].push_back(i);
                out_adj[i].push_back(n);
            }
        }

        vector<bool> vis(n, false);
        vector<int> toposort;
        dfs(n, in_adj, vis, toposort);

        for(int i = 0; i < n; i++) {
            cout << toposort[i] + 1 << " ";
        }
        cout << endl;
    }
    return 0;
}