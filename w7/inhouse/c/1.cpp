#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct vec2 {
    ll x;
    ll y;
    vec2 operator+(vec2 other) {
        return {x + other.x , y + other.y};
    }
    vec2 operator-(vec2 other) {
        return {x - other.x , y - other.y};
    }
};

struct line1 {
    ll x1, x2;
};

struct line2 {
    vec2 v1;
    vec2 v2;
};

inline ll square(ll a) {
    return a * a;
}

ll dot_prod(const vec2& a, const vec2& b) {
    return a.x * b.x + a.y * b.y;
}

vec2 rotate90_cc(const vec2& a) {
    return {-a.y, a.x};
}

ll cross_prod(const vec2& a, const vec2& b) {
    return dot_prod(rotate90_cc(a), b);
}

ll lines_intersect_1d(line1 l1, line1 l2) {
    if(l1.x1 > l1.x2) {
        swap(l1.x1, l1.x2);
    }
    if(l2.x1 > l2.x2) {
        swap(l2.x1, l2.x2);
    }
    return !(l1.x2 <= l2.x1 || l1.x1 >= l2.x2);
}

bool bounding_boxes_intersect(vec2 v1, vec2 v2, vec2 v3, vec2 v4) {
    ll minx1 = min(v1.x, v2.x);
    ll maxx1 = max(v1.x, v2.x);
    ll miny1 = min(v1.y, v2.y);
    ll maxy1 = max(v1.y, v2.y);
    ll minx2 = min(v3.x, v4.x);
    ll maxx2 = max(v3.x, v4.x);
    ll miny2 = min(v3.y, v4.y);
    ll maxy2 = max(v3.y, v4.y);

    ll dx1 = maxx1 - minx1;
    ll dy1 = maxy1 - miny1;
    ll dx2 = maxx2 - minx2;
    ll dy2 = maxy2 - miny2;

    if(dx1 == 0 && dx2 == 0) {
        return lines_intersect_1d({miny1, maxy1}, {miny2, maxy2});
    }

    if(dy1 == 0 && dy2 == 0) {
        return lines_intersect_1d({minx1, maxx1}, {minx2, maxx2});
    }

    return lines_intersect_1d({minx1, maxx1}, {minx2, maxx2}) && lines_intersect_1d({miny1, maxy1}, {miny2, maxy2});
}

bool lines_potentially_intersect(line2 l1, line2 l2) {
    vec2 e1t = l1.v2 - l1.v1;
    vec2 s2t = l2.v1 - l1.v1;
    vec2 e2t = l2.v2 - l1.v1;

    ll cross1 = cross_prod(e1t, s2t);
    ll cross2 = cross_prod(e1t, e2t);

    if(cross1 == 0 && cross2 == 0) {
        return bounding_boxes_intersect({0, 0}, e1t, s2t, e2t);
    }

    if(cross1 == 0) {
        return 0 < dot_prod(e1t, s2t) && dot_prod(e1t, s2t) < (square(e1t.x) + square(e1t.y));
    }

    if(cross2 == 0) {
        return 0 < dot_prod(e1t, e2t) && dot_prod(e1t, e2t) < (square(e1t.x) + square(e1t.y));
    }

    return (cross1 > 0 && cross2 < 0) || (cross1 < 0 && cross2 > 0);
}

bool lines_intersect(line2 l1, line2 l2) {
    return lines_potentially_intersect(l1, l2) && lines_potentially_intersect(l2, l1);
}

int main() {
    ll t;
    cin >> t;

    const ll mod = 998244353;
    while(t--) {
        ll n;
        cin >> n;
        vector<vec2> pts;
        for(ll i = 0; i < n; i++) {
            ll x, y;
            cin >> x >> y;
            pts.push_back({x, y});
        }

        ll mincost = numeric_limits<ll>::max();

        vector<ll> cur_perm;
        for(ll i = 0; i < n; i++) {
            cur_perm.push_back(i);
        }
        while(true) {
            vector<ll> par(n, 0);

            while(true) {
                if(par[0] > 0) break;
                bool valid = true;

                for(ll i = 1; i < n - 1; i++) {
                    for(ll j = i + 1; j < n; j++) {
                        if(lines_intersect(
                            {pts[cur_perm[i]], pts[cur_perm[par[i]]]},
                            {pts[cur_perm[j]], pts[cur_perm[par[j]]]}
                        )) {
                            valid = false;
                            break;
                        }
                    }
                }

                if(valid) {
                    ll cur_cost = 0;
                    for(ll i = n - 1; i > 0; i--) {
                        cur_cost = (cur_cost + square(pts[cur_perm[i]].x - pts[cur_perm[par[i]]].x)) % mod;
                        cur_cost = (cur_cost + square(pts[cur_perm[i]].y - pts[cur_perm[par[i]]].y)) % mod;
                    }
                    mincost = min(mincost, cur_cost);
                }
                par[n - 1]++;
                for(ll i = n - 1; i > 0; i--) {
                    if(par[i] >= i) {
                        par[i] = 0;
                        par[i - 1]++;
                    }
                }
            }

            if(is_sorted(cur_perm.begin(), cur_perm.end(), greater<ll>())) break;
            next_permutation(cur_perm.begin(), cur_perm.end());
        }

        cout << mincost << endl;
    }

    return 0;
}