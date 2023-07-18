/*
State: (X, Y, dir)
Nodes: 2K
Time Complexity: O(K log K)
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct edge {
    ll n;
    ll w;
};

class CompTuple {
    public:
        bool operator()(tuple<ll, ll> a, tuple<ll, ll> b) {
            return get<1>(a) > get<1>(b);
        }
};

int main() {
    ll m, n, k;
    cin >> m >> n >> k;
    vector<vector<edge>> adj;
    const ll total_nodes = 2ll * k + 2ll;
    for(ll i = 0ll; i < total_nodes; i++) {
        vector<edge> row;
        adj.push_back(row);
    }
    
    vector<tuple<ll, ll, ll>> rooms;
    for(ll i = 0ll; i < k; i++) {
        ll x, y;
        cin >> x >> y;
        rooms.push_back({x, y, i});
    }

    /*
    TODO sorted room index
    consider adjacent items in the list
    consider the edges to and from the starting and ending nodes
    */
    // Vertical connection
    // Also connections between switches
    // For state i = 0
    std::sort(rooms.begin(), rooms.end(), [](tuple<ll, ll, ll> a, tuple<ll, ll, ll> b) {
        return (get<0>(a) < get<0>(b)) || (get<0>(a) == get<0>(b) && get<1>(a) < get<1>(b));
    });
    for(ll sorti = 0ll; sorti < k; sorti++) {
        ll x1, y1, i1;
        tie(x1, y1, i1) = rooms[sorti];
        if(sorti < k - 1) {
            ll x2, y2, i2;
            tie(x2, y2, i2) = rooms[sorti + 1ll];

            if(x1 == x2) {
                ll dist = y2 - y1;
                adj[i1 << 1ll].push_back({i2 << 1ll, dist});
                adj[i2 << 1ll].push_back({i1 << 1ll, dist});
            }
        }
        adj[i1 << 1ll].push_back({(i1 << 1ll) | 1ll, 1ll});
        adj[(i1 << 1ll) | 1ll].push_back({i1 << 1ll, 1ll});
    }

    // Vertical connection with the start
    {
        ll scvx, scvy, scvi;
        tie(scvx, scvy, scvi) = rooms[0];

        if(scvx == 1) {
            adj[scvi << 1ll].push_back({total_nodes - 2ll, scvy - 1ll});
            adj[total_nodes - 2ll].push_back({scvi << 1ll, scvy - 1ll});
        }
    }

    // Vertical connection with the end
    {
        ll ecvx, ecvy, ecvi;
        tie(ecvx, ecvy, ecvi) = rooms[k - 1];

        if(ecvx == m) {
            adj[ecvi << 1ll].push_back({total_nodes - 1ll, n - ecvy});
            adj[total_nodes - 1ll].push_back({ecvi << 1ll, n - ecvy});
        }
    }

    // Horizontal connection
    // For state i = 1
    std::sort(rooms.begin(), rooms.end(), [](tuple<ll, ll, ll> a, tuple<ll, ll, ll> b) {
        return (get<1>(a) < get<1>(b)) || (get<1>(a) == get<1>(b) && get<0>(a) < get<0>(b));
    });
    for(ll sorti = 0ll; sorti < k - 1; sorti++) {
        ll x1, y1, i1;
        tie(x1, y1, i1) = rooms[sorti];
        ll x2, y2, i2;
        tie(x2, y2, i2) = rooms[sorti + 1ll];

        if(y1 == y2) {
            ll dist = x2 - x1;
            adj[(i1 << 1ll) | 1ll].push_back({(i2 << 1ll) | 1ll, dist});
            adj[(i2 << 1ll) | 1ll].push_back({(i1 << 1ll) | 1ll, dist});
        }
    }

    // Horizontal connection with the end
    {
        ll echx, echy, echi;
        tie(echx, echy, echi) = rooms[k - 1];

        if(echy == n) {
            adj[(echi << 1ll) | 1ll].push_back({total_nodes - 1ll, m - echx});
            adj[total_nodes - 1ll].push_back({(echi << 1ll) | 1ll, m - echx});
        }
    }

    // Dijkstra Time
    vector<ll> dists(total_nodes, -1ll);
    priority_queue<tuple<ll, ll>, vector<tuple<ll, ll>>, CompTuple> pq;
    pq.push({total_nodes - 2ll, 0ll});

    while(!pq.empty()) {
        ll node, dist;
        tie(node, dist) = pq.top();
        pq.pop();

        if(dists[node] != -1ll) continue;
        dists[node] = dist;

        for(const edge& e : adj[node]) {
            pq.push({e.n, e.w + dist});
        }
    }

    cout << dists[total_nodes - 1ll] << endl;

    return 0;
}