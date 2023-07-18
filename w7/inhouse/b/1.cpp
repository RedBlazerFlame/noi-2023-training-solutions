/*
Idea: go through all subsets of edges
Check which ones have an odd number of
occurrences
If there's exactly two or zero odds
and if the path is connected, make the answer smaller
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct edge {
    ll u, v, w;
};

class UnionFind {
    public:
        vector<ll> par;
        vector<ll> csize;
        ll comps;
        ll n;

        UnionFind(ll a_n): n(a_n), comps(a_n) {
            for(ll i = 0; i < n; i++) {
                par.push_back(i);
                csize.push_back(1ll);
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

        void unify(ll a, ll b) {
            ll para = find(a);
            ll parb = find(b);
            if(para == parb) return;

            if(csize[para] < csize[parb]) {
                par[para] = parb;
                csize[parb] += csize[para];
            } else {
                par[parb] = para;
                csize[para] += csize[parb];
            }

            comps--;
        }
};

int main() {
    ll n, m;
    cin >> n >> m;
    vector<edge> edges;

    for(ll i = 0; i < m; i++) {
        ll u, v, w;
        cin >> u >> v >> w;
        u--; v--;

        edge e;
        e.u = u;
        e.v = v;
        e.w = w;

        edges.push_back({u, v, w});
    }

    vector<vector<ll>> ans;
    for(ll i = 0; i < n; i++) {
        vector<ll> row(n, 0);
        ans.push_back(row);
    }

    for(ll mask = 1; mask < (1 << m); mask++) {
        vector<edge> cur_edges;
        vector<ll> counts(n, 0);
        for(ll i = 0; i < m; i++) {
            if((mask >> i) & 1ll == 1ll) {
                cur_edges.push_back(edges[i]);
                counts[edges[i].u]++;
                counts[edges[i].v]++;
            }
        }

        vector<ll> odds;
        ll num_nodes = 0;
        
        for(ll i = 0; i < n; i++) {
            if(counts[i] & 1ll == 1ll) {
                odds.push_back(i);
            }
            if(counts[i] > 0ll) {
                num_nodes++;
            }
        }

        if(odds.size() != 0 && odds.size() != 2) continue;
        UnionFind uf(n);

        for(const auto& [u, v, _] : cur_edges) {
            uf.unify(u, v);
        }

        if(uf.comps > n - num_nodes + 1) continue;

        ll maxw = numeric_limits<ll>::min();

        for(ll i = 0; i < (ll)cur_edges.size(); i++) {
            maxw = max(maxw, cur_edges[i].w);
        }

        if(odds.size() == 0) {
            for(ll i = 0; i < n - 1; i++) {
                if(counts[i] > 0) {
                    ans[i][i] = max(ans[i][i], maxw);
                }
            }
        } else if(odds.size() == 2) {
            ans[odds[0]][odds[1]] = max(ans[odds[0]][odds[1]], maxw);
            ans[odds[1]][odds[0]] = max(ans[odds[1]][odds[0]], maxw);
        }
    }

    ll q;
    cin >> q;

    while(q--) {
        ll s, e;
        cin >> s >> e;
        s--; e--;

        cout << ans[s][e] << endl;
    }

    return 0;
}