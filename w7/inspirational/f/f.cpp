/*
Targets: Subtasks 1 and 2
Idea: Do a dijkstra from the infected cities to
everywhere to get the min distance of each city
to an infected city.
Then, do modified dijkstra to answer queries
Time complexity:
O(Q(N + M) log M), not so great .-.
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
struct edge {
    ll n;
    ll w;
};
typedef vector<vector<edge>> wadjl;
typedef pair<ll, ll> pll;

int main() {
    ll n, m, k, q;
    cin >> n >> m >> k >> q;

    wadjl adj;
    for(ll i = 0ll; i < n; i++) {
        vector<edge> row;
        adj.push_back(row);
    }

    for(ll i = 0ll; i < m; i++) {
        ll a, b, l;
        cin >> a >> b >> l;
        a--; b--;
        adj[a].push_back({b, l});
        adj[b].push_back({a, l});
    }

    vector<ll> infected(k, 0);
    for(ll& v : infected) {
        cin >> v;
        v--;
    }

    // Do dijkstra magic here
    vector<ll> dist(n, -1ll);
    priority_queue<pll, vector<pll>, greater<pll>> pq;
    for(ll city : infected) {
        pq.push({0ll, city});
    }

    while(!pq.empty()) {
        ll curdist, node;
        tie(curdist, node) = pq.top();
        pq.pop();

        if(dist[node] != -1ll) continue;
        dist[node] = curdist;

        for(const edge& e : adj[node]) {
            pq.push({curdist + e.w, e.n});
        }
    }

    // Answer queries here
    while(q--) {
        ll s, t;
        cin >> s >> t;
        s--; t--;

        // Dijkstra state: (maxdist, city)
        vector<bool> vis(n, false);
        priority_queue<pll, vector<pll>, less<pll>> pq;
        pq.push({dist[s], s});

        ll ans = 0;
        while(!pq.empty()) {
            ll curdist, node;
            tie(curdist, node) = pq.top();
            pq.pop();

            if(vis[node]) continue;
            vis[node] = true;

            if(node == t) {
                ans = curdist;
                break;
            }

            for(const edge& e : adj[node]) {
                pq.push({min(curdist, dist[e.n]), e.n});
            }
        }

        cout << ans << endl;
    }
}