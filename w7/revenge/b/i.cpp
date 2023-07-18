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
    if( m <= 500 ) {
        // That weird brute forcer on the edges
        vector<vector<tuple<int, int>>> edge_perms = {
            {
                {0, 2}, {1, 4}, {3, 5},
            },
            {
                {0, 2}, {1, 5}, {3, 4},
            },
            {
                {0, 3}, {1, 4}, {2, 5},
            },
            {
                {0, 3}, {1, 5}, {2, 4},
            },
            {
                {0, 4}, {1, 2}, {3, 5},
            },
            {
                {0, 4}, {1, 3}, {2, 5},
            },
            {
                {0, 5}, {1, 2}, {3, 4},
            },
            {
                {0, 5}, {1, 3}, {2, 4},
            }
        };
        for(int i = 0; i < m - 2; i++) {
            for(int j = i + 1; j < m - 1; j ++) {
                for(int k = j + 1; k < m; k++) {
                    bool poss = false;
                    vector<int> rel_nodes = {
                        get<0>(edges[i]),
                        get<1>(edges[i]),
                        get<0>(edges[j]),
                        get<1>(edges[j]),
                        get<0>(edges[k]),
                        get<1>(edges[k]),
                    };
                    set<int> set_nodes;
                    for(int rel_node : rel_nodes) {
                        set_nodes.insert(rel_node);
                    }
                    if(set_nodes.size() < 6) continue;
                    for(auto edge_check : edge_perms) {
                        bool connected = true;
                        for(auto [e1, e2] : edge_check) {
                            if(!adj[rel_nodes[e1]][rel_nodes[e2]]) {
                                connected = false;
                                break;
                            }
                        }
                        if(connected) {
                            cout << edge_check[0][0] << " " << edge_check[0][1] << " " << edge_check[0][0] << " " << edge_check[0][1] << " " << edge_check[0][0] << " " << edge_check[0][1] << " ";
                            poss = true;
                            break;
                        }
                    }

                    if(poss) {
                        for(int rel_node : rel_nodes) {
                            cout << rel_node + 1 << " ";
                        }
                        cout << endl;
                        count = (count + 1) % mod;
                    }
                }
            }
        }
        
    } else {
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
    }

    cout << count << endl;
    return 0;
}