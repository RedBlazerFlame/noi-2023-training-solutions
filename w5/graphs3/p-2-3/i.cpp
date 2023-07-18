/*
This program solves problem 2.3
using a dynamic segment tree

(This is my first time implementing a dynamic seg tree :D)
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class Segtree {
    public:
        const static ll defv = 0ll;
        ll v;
        ll li, ri;
        Segtree* l = nullptr;
        Segtree* r = nullptr;
        Segtree(ll a_li, ll a_ri) {
            v = id();
            li = a_li;
            ri = a_ri;
        }

        inline ll op(ll a, ll b) {
            return a + b;
        }

        inline ll id() {
            return 0ll;
        }

        void buildl() {
            if(l == nullptr) l = new Segtree(li, (li + ri) >> 1);
        }

        void buildr() {
            if(r == nullptr) r = new Segtree(((li + ri) >> 1) + 1, ri);
        }

        ll leftv() {
            return (l == nullptr ? id() : l->v);
        }

        ll rightv() {
            return (r == nullptr ? id() : r->v);
        }

        ll qleft(ll ql, ll qr) {
            return (l == nullptr ? id() : l->query(ql, qr));
        }

        ll qright(ll ql, ll qr) {
            return (r == nullptr ? id() : r->query(ql, qr));
        }

        ll query(ll ql, ll qr) {
            if(ql > qr) return id();
            if(ql == li && qr == ri) return v;
            if(qr < li || ql > ri) return id();
            ll m = (li + ri) >> 1;

            return op(qleft(ql, min(m, qr)), qright(max(m + 1, ql), qr));
        }

        void upd(ll i, ll inc) {
            if(i == li && i == ri) {
                v += inc;
                return;
            } else {
                ll m = (li + ri) >> 1;
                if(i > m) {
                    // Build right subtree
                    buildr();
                    r->upd(i, inc);
                } else {
                    buildl();
                    l->upd(i, inc);
                }
                v = op(leftv(), rightv());
            }

        }
};

int main() {
    ll n, q;
    cin >> n >> q;
    const ll MAX_AGE = 10000000000ll;
    vector<pair<ll, ll>> extreme_ages;
    extreme_ages.reserve(n);
    for(ll i = 0ll; i < n; i++) {
        ll num_res;
        cin >> num_res;
        vector<ll> ages(num_res, 0);
        for(ll& age : ages) {
            cin >> age;
        }
        
        extreme_ages.push_back({accumulate(ages.begin(), ages.end(), numeric_limits<ll>::max(), [](ll a, ll b) {return min(a, b);}), accumulate(ages.begin(), ages.end(), numeric_limits<ll>::min(), [](ll a, ll b) {return max(a, b);})});
    }

    Segtree tree(0ll, MAX_AGE);
    
    while(q--) {
        /*
        Query format:
        GIFT a g
        QRY i
        */

        string qtype;
        cin >> qtype;

        if(qtype == "GIFT") {
            ll a, g;
            cin >> a >> g;
            tree.upd(a, g);
        } else if(qtype == "QRY") {
            ll i;
            cin >> i;
            cout << tree.query(extreme_ages[i].first, extreme_ages[i].second) << endl;
        }
    }

    return 0;
}