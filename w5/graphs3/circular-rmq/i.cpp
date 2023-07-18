/*
Even if this is not in the learning guide,
I decided to try to tackle "Circular RMQ",
which involves a lazy-propagating segment tree.

Link to problem: https://codeforces.com/problemset/problem/52/C
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class Segtree {
    public:
        ll v;
        ll li, ri;
        Segtree* l = nullptr;
        Segtree* r = nullptr;
        ll lazy = lazy_id();

        Segtree(const vector<ll>& vec, ll a_li, ll a_ri): li{a_li}, ri{a_ri} {
            if(li == ri) {
                v = vec[li];
            } else {
                ll m = (li + ri) >> 1;
                l = new Segtree(vec, a_li, m);
                r = new Segtree(vec, m + 1, a_ri);
                v = op(l->v, r->v);
            }
        }

        void push_upd() {
            if(lazy == lazy_id()) return;
            if(l != nullptr) {
                l->lazy += lazy;
                l->v += lazy;
            }
            if(r != nullptr) {
                r->lazy += lazy;
                r->v += lazy;
            }
            lazy = lazy_id();
        }

        ll range_q(ll ql, ll qr) {
            if(ql == li && qr == ri) return v;
            if(qr < li || ql > ri) return id();
            push_upd();
            ll m = (li + ri) >> 1;
            return op(l->range_q(ql, min(m, qr)), r->range_q(max(m + 1, ql), qr));
        }

        void range_upd(ll ql, ll qr, ll inc) {
            if(ql == li && qr == ri) {
                lazy += inc;
                v += inc;
                return;
            }
            if(qr < li || ql > ri) return;
            push_upd();
            ll m = (li + ri) >> 1;
            l->range_upd(ql, min(qr, m), inc);
            r->range_upd(max(ql, m + 1), qr, inc);
            v = op(l->v, r->v);
        }

        inline ll op(ll a, ll b) {
            return min(a, b);
        }

        constexpr ll id() {
            return numeric_limits<ll>::max();
        }

        constexpr ll lazy_id() {
            return 0ll;
        }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
 
    ll n;
    cin >> n;
    vector<ll> v(n, 0);
 
    for (auto &vi : v)
    {
        cin >> vi;
    }
 
    ll m;
    cin >> m;
 
    Segtree tree(v, 0, n - 1);
    string curStr;
    std::getline(cin, curStr);
    vector<ll> inps;
    while (m--)
    {
        std::getline(cin, curStr);
        istringstream strm;
        strm.str(curStr);
        string curStrNum;
        inps.clear();
        while (strm)
        {
            strm >> curStrNum;
            inps.push_back(stoi(curStrNum));
        }
 
        if (inps.size() == 3)
        {
            // Query
            ll l = inps[0], r = inps[1];
            if (l > r)
            {
                cout << min(tree.range_q(l, n - 1), tree.range_q(0, r)) << "\n";
            }
            else
            {
                cout << tree.range_q(l, r) << "\n";
            }
        }
        else
        {
            // Increment
            ll l = inps[0], r = inps[1], v = inps[2];
            if (l > r)
            {
                tree.range_upd(l, n - 1, v);
                tree.range_upd(0, r, v);
            }
            else
            {
                tree.range_upd(l, r, v);
            }
        }
    }
}

/*
Lesson: when marking nodes for lazy updates,
we also update the value itself already.

Also, the range update operation may differ from
the range query operation. In this case, there will
be multiple identities.

Finally, it seems like the implementation of the
lazy propagating segment tree that has a low constant factor
and is (relatively) easy to implement is the one that stores
left and right pointers to sub segment trees

I personally like this method of implementation, so
I will stick with it from here on out.
*/