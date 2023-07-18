#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct edge {
    ll u, v, w;
};

class Segtree {
    public:
        ll li;
        ll ri;
        Segtree* l;
        Segtree* r;
        ll v;

        Segtree(const vector<ll>& vals, ll a_li, ll a_ri): li(a_li), ri(a_ri) {
            if(a_li == a_ri) {
                v = vals[a_li];
                l = nullptr;
                r = nullptr;
            } else {
                ll m = (ri + li) >> 1;

                l = new Segtree(vals, li, m);
                r = new Segtree(vals, m + 1, ri);

                v = op(l->v, r->v);
            }
        }

        inline ll op(ll a, ll b) {
            return max(a, b);
        }
        
        constexpr ll id() {
            return numeric_limits<ll>::min();
        }

        ll query(ll ql, ll qr) {
            if(ql == li && qr == ri) {
                return v;
            }

            if(ql > ri || qr < li) {
                return id();
            }

            ll m = (li + ri) >> 1;

            return op(l->query(ql, min(qr, m)), r->query(max(m + 1, ql), qr));
        }
};

int main() {
    ll n, m;
    cin >> n >> m;
    vector<ll> vals(n - 1, 0);

    for(ll i = 0; i < m; i++) {
        ll u, v, w;
        cin >> u >> v >> w;
        u--; v--;

        vals[min(u, v)] = w;
    }
    Segtree tree(vals, 0, n - 2);

    ll q;
    cin >> q;
    while(q--) {
        ll s, e;
        cin >> s >> e;
        s--; e--;

        if(s == e) {
            cout << 0 << endl;
        } else {
            cout << tree.query(min(s, e), max(s, e) - 1) << endl;
        }
    }

    return 0;
}