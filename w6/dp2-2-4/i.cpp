/*
Given a weighted DAG, this program calculates the
longest path.
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<vector<pair<ll, ll>>> dag_adj_list;

vector<ll> memo;
ll longest_path(const dag_adj_list& adj, ll node) {
    ll& ans = memo[node];
    if(ans == -1ll) {
        ans = numeric_limits<ll>::min();
        if(adj[node].size() == 0ll) ans = 0ll;
        for(auto& [u, w] : adj[node]) ans = max(ans, w + longest_path(adj, u));
    }
    return ans;
}

int main() {
    ll n, m;
    cin >> n >> m;
    memo.reserve(n);
    for(ll i = 0ll; i < n; i++) {
        memo.push_back(-1ll);
    }
    dag_adj_list in_nodes;
    dag_adj_list out_nodes;
    for(ll i = 0ll; i < n; i++) {
        vector<pair<ll, ll>> row1;
        vector<pair<ll, ll>> row2;
        in_nodes.push_back(row1);
        out_nodes.push_back(row2);
    }
    
    for(ll i = 0ll; i < m; i++) {
        ll u, v, w;
        cin >> u >> v >> w;
        u--; v--;
        in_nodes[v].push_back({u, w});
        out_nodes[u].push_back({v, w});
    }

    ll last_node = 0ll;

    for(ll i = 0ll; i < n; i++) {
        if(out_nodes[i].size() == 0ll) {
            last_node = i;
            break;
        }
    }

    cout << longest_path(in_nodes, last_node) << endl;

    return 0;
}