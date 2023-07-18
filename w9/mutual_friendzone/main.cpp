#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    ll t;
    cin >> t;
    cout << t << endl;
    
    while(t--) {
        ll n, e;
        cin >> n >> e;
        vector<vector<ll>> adj;
        for(ll i = 0; i < n; i++) {
            vector<ll> row;
            adj.push_back(row);
        }
        
        for(ll i = 0; i < e; i++) {
            ll u, v;
            cin >> u >> v;
            u--; v--;
            adj[v].push_back(u);
            adj[u].push_back(v);
        }
        
        ll m = 0;
        
        for(ll i = 0; i < n; i++) {
            m += ((adj[i].size()) * (adj[i].size() - 1)) >> 1ll;
        }
        
        cout << n << " " << e << " " << m << endl;
    } 
    return 0;
}
