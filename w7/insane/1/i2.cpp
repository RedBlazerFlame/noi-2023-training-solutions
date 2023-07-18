/*
Notes
1. Use 1LL instead of 1ll
2. When doing arithmetic, no need to put the LL
3. Set a convention for nodes: i, j
4. When initializing distances, use infinity
5. Use structured binding
6. Be careful when initializing vectors: I initialized v_cities with a certain number of 0s and push_back ed at the end
    6a. Kevin: Stick to one style: Either push_back or initialize with a certain value. Both of them are usually as efficient as one another
7. Consider adding extra state per node to your graph. It may help in harder problems ^^
8. If you're using a certain bitwise operation (or any operation, really) a lot, try extracting that logic into a function
    8a. For instance, I had an operator ind(i, tickets) = (i << num_tickets) | tickets. I should extract that into a function next time.
9. Instead of doing if(dist[i] != sentinel_value) continue;, do if(dist[i] < curd) continue;. This new code says to skip if the distance doesn't improve.
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;

struct node {
    ll i;
    ll S;
    ll ind() {
        return (i << 5ll) | S;
    }
};

node node_from_ind(ll ind) {
    node e = {ind >> 5ll, ind & 0b11111};
    return e;
}

int main() {
    ll n, e, k;
    cin >> n >> e >> k;
    const ll num_tickets = 5ll;
    const ll ticket_combs = 1ll << num_tickets;

    vector<vector<pll>> out_adj;
    vector<vector<pll>> in_adj;
    out_adj.reserve(n * ticket_combs);
    in_adj.reserve(n * ticket_combs);
    for(ll i = 0ll; i < n * ticket_combs; i++) {
        vector<pll> out_row;
        vector<pll> in_row;
        out_adj.push_back(out_row);
        in_adj.push_back(in_row);
    }

    vector<ll> v_cities;
    for(ll i = 0; i < k; i++) {
        ll curcity;
        cin >> curcity;
        curcity <<= num_tickets;
        for(ll j = 0ll; j < ticket_combs; j++) {
            v_cities.push_back(curcity | j);
        }
    }

    // Build the graph
    for(ll i = 0; i < e; i++) {
        ll u, v, c;
        cin >> u >> v >> c;

        for(ll tickets = 0; tickets < ticket_combs; tickets++) {
            out_adj[(u << num_tickets) | tickets].push_back({(v << num_tickets) | tickets, c});
            in_adj[(v << num_tickets) | tickets].push_back({(u << num_tickets) | tickets, c});

            for(ll bitpos = 0; bitpos < 5; bitpos++) {
                if((tickets >> bitpos) & 0b1) {
                    out_adj[(u << num_tickets) | tickets].push_back({(v << num_tickets) | (tickets ^ (1ll << bitpos)), (c / 10) * (10 - bitpos - 1)});
                    in_adj[(v << num_tickets) | (tickets ^ (1ll << bitpos))].push_back({(u << num_tickets) | tickets, (c / 10) * (10 - bitpos - 1)});
                }
            }
        }
    }

    // Dijkstra from the cities
    vector<ll> dist(n * ticket_combs, -1ll);
    // Kevin: vector<ll> dist(n * ticket_combs, numeric_limits<ll>::max());
    priority_queue<pll, vector<pll>, greater<pll>> pq;
    
    for(ll v_city : v_cities) {
        pq.push({0ll, v_city});
    }

    while(!pq.empty()) {
        ll curd, i;
        tie(curd, i) = pq.top();
        // Kevin: auto [curd, i] = pq.top();
        // Kevin: pq.pop();

        if(dist[i] != -1ll) continue;
        // Kevin: if (dist[i] <= curd) continue;
        // Kevin: dist[i] = curd;

        for(pll e : in_adj[i]) {
            pq.push({curd + e.second, e.first});
        }
        // Kevin: for(auto [d, j] : in_adj[i]) {
        // Kevin:     pq.push({curd + d, j});
        // Kevin: }
    }

    // for(ll i = 0ll; i < n * ticket_combs; i++) {
    //     std::cout << "DEBUG: dist[" << i << "] = " << dist[i] << endl;
    // }

    ll q;
    cin >> q;

    while(q--) {
        ll s;
        vector<ll> p(5ll, 0ll);
        cin >> s >> p[0] >> p[1] >> p[2] >> p[3] >> p[4];

        ll ans = numeric_limits<ll>::max();

        for(ll i = 0ll; i < ticket_combs; i++) {
            bool valid = true;
            ll total_ticket_price = 0ll;
            for(ll bitpos = 0ll; bitpos < num_tickets; bitpos++) {
                if(((i >> bitpos) & 1ll)) {
                    ll ticket_price = p[bitpos];
                    if(ticket_price == -1ll) {
                        valid = false;
                        break;
                    }
                    total_ticket_price += ticket_price;
                }
            }

            if(valid) {
                ans = min(ans, total_ticket_price + dist[(s << num_tickets) | i]);
            }
        }

        std::cout << ans << endl;
    }

    return 0;
}