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

    if(cross1 == 0 || cross2 == 0) {
        return false;
    }

    return (cross1 > 0 && cross2 < 0) || (cross1 < 0 && cross2 > 0);
}

bool lines_intersect(line2 l1, line2 l2) {
    return lines_potentially_intersect(l1, l2) && lines_potentially_intersect(l2, l1);
}

int main() {
    ll t;
    cin >> t;

    for(ll i = 1; i <= t; i++) {
        ll x0, x1, x2, x3, x4, x5, x6, x7;
        cin >> x0 >> x1 >> x2 >> x3 >> x4 >> x5 >> x6 >> x7;
        bool actual;
        cin >> actual;
        bool ans = lines_intersect({{x0, x1}, {x2, x3}}, {{x4, x5}, {x6, x7}});

        cout << "TEST " << i << ": " << (ans == actual ? "RIGHT" : "WRONG") << endl;
    }

    return 0;
}