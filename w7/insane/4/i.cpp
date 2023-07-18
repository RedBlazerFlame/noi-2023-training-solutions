#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<vector<vector<ll>>> wgraph;

class CompareVec {
    public:
        bool operator()(vector<ll> a, vector<ll> b) {
            return a[1] > b[1];
        }
};

ll seek(ll qi, ll n, const wgraph& adj, const vector<bool>& has_grape) {
    vector<bool> vis(n, false);
    priority_queue<vector<ll>, vector<vector<ll>>, CompareVec> pq;
    
    vector<ll> s;
    s.push_back(qi);
    s.push_back(0ll);
    pq.push(s);

    while(!pq.empty()) {
        vector<ll> cur = pq.top();
        pq.pop();
        ll curnode = cur[0];
        ll curdist = cur[1];
        
        if(vis[curnode]) continue;
        vis[curnode] = true;

        if(has_grape[curnode]) return curdist;

        for(const vector<ll>& edge : adj[curnode]) {
            vector<ll> new_entry;
            new_entry.push_back(edge[0]);
            new_entry.push_back(edge[1] + curdist);
            pq.push(new_entry);
        }
    }

    return -1;
}

int main() {
    ll n, q;
    cin >> n >> q;
    wgraph adj;
    vector<bool> has_grape(n, false);
    for(ll i = 0ll; i < n; i++) {
        vector<vector<ll>> row;
        adj.push_back(row);
    }

    for(ll i = 0ll; i < n - 1; i++) {
        ll a, b, w;
        cin >> a >> b >> w;
        a--; b--;
        adj[a].push_back({b, w});
        adj[b].push_back({a, w});
    }

    while(q--) {
        ll qtype;
        cin >> qtype;

        if(qtype == 1) {
            // Seek
            ll qi;
            cin >> qi;
            qi--;
            cout << seek(qi, n, adj, has_grape) << endl;

        } else if(qtype == 2) {
            // Soak
            ll u;
            cin >> u;
            u--;
            has_grape[u] = !has_grape[u];
        } else {
            // Anneal
            ll qa, qb, qw;
            cin >> qa >> qb >> qw;
            qa--; qb--;

            for(vector<ll>& edge : adj[qa]) {
                if(edge[0] == qb) {
                    edge[1] = qw;
                }
            }

            for(vector<ll>& edge : adj[qb]) {
                if(edge[0] == qa) {
                    edge[1] = qw;
                }
            }
        }
    }

    return 0;
}