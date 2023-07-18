/*
This program implements Exercise 2.1
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef short int si;

class Segtree {
    public:
        ll v;
        ll li, ri;

        Segtree* l = nullptr;
        Segtree* r = nullptr;

        Segtree(const vector<ll>& vec, ll a_li, ll a_ri) : li{a_li}, ri{a_ri} {
            if(li == ri) {
                v = vec[li];
            } else {
                ll m = (a_li + a_ri) >> 1;
                l = new Segtree(vec, a_li, m);
                r = new Segtree(vec, m + 1, a_ri);

                v = op(l->v, r->v);
            }
        }

        Segtree(ll initv, ll a_li, ll a_ri) : li{a_li}, ri{a_ri} {
            if(li == ri) {
                v = initv;
            } else {
                ll m = (a_li + a_ri) >> 1;
                l = new Segtree(initv, a_li, m);
                r = new Segtree(initv, m + 1, a_ri);

                v = op(l->v, r->v);
            }
        }

        ll query(ll ql, ll qr) {
            if(ql > qr) return id();
            if(qr < li || ql > ri) return id();
            if(ql == li && qr == ri) return v;
            // TODO determine if something is wrong
            ll m = (li + ri) >> 1;
            return op(l->query(ql, min(m, qr)), r->query(max(m + 1, ql), qr));
        }

        void upd(ll i, ll nv) {
            if(i == li && i == ri) {
                v = nv;
                return;
            } else if(li <= i && i <= ri) {
                l->upd(i, nv);
                r->upd(i, nv);
                v = op(l->v, r->v);
            }
        }

        inline ll id() {
            return 0;
        }

        inline ll op(ll a, ll b) {
            return a + b;
        }
        bool isLeaf() {
            return l == nullptr && r == nullptr;
        }
};

int main() {
    ll n, q;
    cin >> n >> q;

    /*
    Structure: stored in bits
    so 00 -> 0
    01 -> 1
    10 -> 2
    11 -> 3
    */
    vector<si> b(n, 0);
    Segtree tree(0, 0, n - 1);

    /*
    Query structure:
    UPD i
    QRY i j
    */
    while(q--) {
        string qtype;
        cin >> qtype;
        if(qtype == "UPD") {
            ll i;
            cin >> i;
            if(i > 0) {
                b[i - 1] ^= 0b01;
                tree.upd(i - 1, b[i - 1] == 0b01 ? 1ll : 0ll);
            }

            b[i] ^= 0b10;
            tree.upd(i, b[i] == 0b01 ? 1ll : 0ll);

        } else {
            ll i, j;
            cin >> i >> j;

            cout << tree.query(i, j - 1) + ((b[i] & 0b10) > 0ll ? 1ll : 0ll) << endl;
        }
    }

    // for(ll i = 0; i < n; i++) {
    //     cout << i << ": " << b[i] << endl;
    // }

    return 0;
}

/*
Lesson: Don't assume that you know what the order of operations is
In this case, I thought "bitwise and" was done first before
">", but apparently it's the other way around
Because of that, I got off-by-one errors
*/