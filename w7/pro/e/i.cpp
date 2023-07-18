#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class UnionFind {
    public:
        vector<ll> comp_size;
        ll comps;
        vector<ll> par;
        ll n;

        UnionFind(ll a_n): n(a_n), comps(a_n), par(a_n, 0ll), comp_size(a_n, 1ll) {
            for(ll i = 0; i < n; i++) {
                par[i] = i;
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

            if(comp_size[para] < comp_size[parb]) {
                par[para] = parb;
                comp_size[parb] += comp_size[para];
            } else {
                par[parb] = para;
                comp_size[para] += comp_size[parb];
            }

            comps--;
        }
};

bool int_line(ll x1, ll x2, ll x3, ll x4) {
    return !(x2 < x3 || x1 > x4);
}

bool intersects(ll x1, ll y1, ll x2, ll y2, ll x3, ll y3, ll x4, ll y4) {
    return int_line(x1, x2, x3, x4) && int_line(y1, y2, y3, y4);
}

int main() {
    int n, l, h;
    cin >> n >> l >> h;
    vector<pair<int, int>> coords;
    for(int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        coords.push_back({x, y});
    }
    sort(coords.begin(), coords.end());

    UnionFind uf(n);

    for(ll i = 0; i <= 16ll; i++) {
        ll jump_size = (1 << i);
        for(ll j = 0; j < n - jump_size; j++) {
            if(
                intersects(
                    coords[i].first,
                    coords[i].second,
                    coords[i].first + l,
                    coords[i].second + h,
                    coords[j].first,
                    coords[j].second,
                    coords[j].first + l,
                    coords[j].second + h
                )
            ) {
                uf.unify(i, j);
            }
        }
    }

    cout << uf.comps << endl;

    return 0;
}