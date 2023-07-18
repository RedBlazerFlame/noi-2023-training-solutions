/*
Targets: Subtasks 1 and 2
Idea: Do a dijkstra from the infected cities to
everywhere to get the min distance of each city
to an infected city.
Then, do modified dijkstra to answer queries
Time complexity:
O(N(Q + log N) + E), should pass?
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

class UnionFind {
    public:
        vector<ll> par;
        vector<ll> comp_size;
        ll n;
        UnionFind(ll a_n): n(a_n) {
            par.resize(n);
            comp_size.resize(n);
            for(ll i = 0ll; i < n; i++) {
                par[i] = i;
                comp_size[i] = 1ll;
            }
        }
        ll find(ll i) {
            ll orig = i;
            
            while(i != par[i]) {
                i = par[i];
            }

            while(orig != par[orig]) {
                ll neworig = par[orig];
                par[orig] = i;

                orig = neworig;
            }

            return i;
        }
        void unite(ll a, ll b) {
            ll para = find(a), parb = find(b);

            if(comp_size[para] < comp_size[parb]) {
                // Merge a to b
                comp_size[parb] += comp_size[para];
                par[para] = parb;
            } else {
                // Merge b to a
                comp_size[para] += comp_size[parb];
                par[parb] = para;
            }
        }
};

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
    vector<pair<ll, ll>> dist;
    for(ll i = 0ll; i < n; i++) {
        dist.push_back({-1ll, i});
    }
    priority_queue<pll, vector<pll>, greater<pll>> pq;
    for(ll city : infected) {
        pq.push({0ll, city});
    }

    while(!pq.empty()) {
        ll curdist, node;
        tie(curdist, node) = pq.top();
        pq.pop();

        if(dist[node].first != -1ll) continue;
        dist[node].first = curdist;

        for(const edge& e : adj[node]) {
            pq.push({curdist + e.w, e.n});
        }
    }

    // Get queries
    vector<pll> qs;
    vector<ll> answers(q, numeric_limits<ll>::min());

    for(ll i = 0ll; i < q; i++) {
        ll s, t;
        cin >> s >> t;
        s--; t--;

        qs.push_back({s, t});
    }

    // O(N log N) sort
    sort(dist.begin(), dist.end(), [](pll a, pll b) {return a.first > b.first;});
    UnionFind uf(n);
    set<ll> nodes;

    /*
    vector<tuple<ll, ll, ll>> qsp;
    
    */

    for(pll curnode : dist) {
        ll cv, cnode;
        tie(cv, cnode) = curnode;
        nodes.insert(cnode);

        for(edge e : adj[cnode]) {
            if(nodes.count(e.n) > 0) {
                uf.unite(cnode, e.n);
            }
        }

        for(ll i = 0ll; i < q; i++) { // Can I do this faster?
            ll s, t;
            tie(s, t) = qs[i];
            if(uf.find(s) == uf.find(t)) {
                answers[i] = max(answers[i], cv);
            }
        }
    }

    for(ll v : answers) {
        cout << v << endl;
    }

    return 0;
}