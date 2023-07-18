#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pint;

pint rotate90_cc(pint pt) {
    return {-pt.second, pt.first};
}

pint rotate90_c(pint pt) {
    return {pt.second, -pt.first};
}

int main() {
    int n;
    cin >> n;

    set<pint> pts;
    vector<pint> ptsl;

    for(int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        pts.insert({x, y});
        ptsl.push_back({x, y});
    }

    int ans = 0;
    for(int i = 0; i < n - 1; i ++) {
        for(int j = i + 1; j < n; j ++) {
            int x1, y1, x2, y2;
            tie(x1, y1) = ptsl[i];
            tie(x2, y2) = ptsl[j];
            pint posdiff = {x2 - x1, y2 - y1};
            pint posdiffrcc = rotate90_cc(posdiff);
            pint posdiffrc = rotate90_c(posdiff);

            if(
                (
                    pts.count({x2 + posdiffrcc.first, y2 + posdiffrcc.second}) > 0 &&
                    pts.count({x1 + posdiffrcc.first, y1 + posdiffrcc.second}) > 0
                ) ||
                (
                    pts.count({x2 + posdiffrc.first, y2 + posdiffrc.second}) > 0 &&
                    pts.count({x1 + posdiffrc.first, y1 + posdiffrc.second}) > 0
                )
            ) ans = max(ans, posdiff.first * posdiff.first + posdiff.second * posdiff.second);
        }
    }

    cout << ans << endl;

    return 0;
}