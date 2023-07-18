/*
Time complexity: O(Q + (N + E)log E)
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<vector<tuple<ll, ll>>> adjl_ll;

class CompTuple {
    public:
        bool operator()(tuple<ll, ll> a, tuple<ll, ll> b) {
            return get<1>(a) > get<1>(b);
        }
};

vector<ll> get_min_dists(ll N, ll E, const vector<ll>& voting, const adjl_ll& out_e, const adjl_ll& in_e) {
    vector<bool> vis(N, false);
    priority_queue<tuple<ll, ll>, vector<tuple<ll, ll>>, CompTuple> pq;

    for(const ll& k : voting) {
        pq.push({k, 0ll});
    }

    vector<ll> dists(N, -1ll);
    
    while(!pq.empty()) {
        ll curnode, curdist;
        tie(curnode, curdist) = pq.top();
        pq.pop();

        if(vis[curnode]) continue;
        vis[curnode] = true;
        dists[curnode] = curdist;

        for(const tuple<ll, ll>& edge : in_e[curnode]) {
            pq.push({get<0>(edge), curdist + get<1>(edge)});
        }
    }

    return dists;
}

ll solve(ll N, ll E, const vector<ll>& voting, const adjl_ll& out_e, const adjl_ll& in_e, ll S, const vector<ll>& p) {
    // vector<bool> vis(N, false);
    // priority_queue<tuple<ll, ll>, vector<tuple<ll, ll>>, CompTuple> pq;

    // for(const ll& k : voting) {
    //     pq.push({k, 0ll});
    // }


    // while(!pq.empty()) {
    //     ll curnode, curdist;
    //     tie(curnode, curdist) = pq.top();
    //     pq.pop();

    //     if(vis[curnode]) continue;
    //     vis[curnode] = true;
    // }
    // TODO
    return 0ll;
}

int main() {
    ll N, E, K;
    cin >> N >> E >> K;

    vector<ll> voting(K, 0);
    for(ll& v : voting) {
        cin >> v;
    }
    
    adjl_ll out_e;
    adjl_ll in_e;
    for(ll i = 0ll; i < N; i++) {
        vector<tuple<ll, ll>> adj_out;
        vector<tuple<ll, ll>> adj_in;

        out_e.push_back(adj_out);
        in_e.push_back(adj_in);
    }

    for(ll i = 0ll; i < E; i++) {
        ll u, v, c;
        cin >> u >> v >> c;
        out_e[u].push_back({v, c});
        in_e[v].push_back({u, c});
    }

    ll Q;
    cin >> Q;

    vector<ll> dists = get_min_dists(N, E, voting, out_e, in_e);
    while(Q--) {
        ll S;
        vector<ll> p(5, 0ll);
        cin >> S >> p[0] >> p[1] >> p[2] >> p[3] >> p[4];

        cout << dists[S] << endl;
    }

    return 0;
}