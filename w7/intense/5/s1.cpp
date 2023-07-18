#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

pair<int, vector<int>> fast_inv(const vector<int>& vec, int l, int r) {
    if(r - l == 1) {
        vector<int> res;
        res.push_back(vec[l]);
        return {0, res};
    }

    int n = r - l;
    int m = (l + r) >> 1;
    auto [linv, lv] = fast_inv(vec, l, m);
    auto [rinv, rv] = fast_inv(vec, m, r);
    int count_inv = linv + rinv;

    vector<int> sorted;
    int pl = 0, pr = 0;
        
    while(pl < (int)lv.size() && pr < (int)rv.size()) {
        if(rv[pr] < lv[pl]) {
            sorted.push_back(rv[pr]);
            pr++;
            count_inv += lv.size() - pl;
        } else {
            sorted.push_back(lv[pl]);
            pl++;
        }
    }

    while(pl < (int)lv.size()) {
        sorted.push_back(lv[pl]);
        pl++;
    }

    while(pr < (int)rv.size()) {
        sorted.push_back(rv[pr]);
        pr++;
    }

    return {count_inv, sorted};
}

int main() {
    int n;
    cin >> n;

    vector<int> a(n, 0);

    for(int& v : a) {
        cin >> v;
    }

    int ans = numeric_limits<int>::max();
    for(int i = 0; i < n - 1; i++) {
        for(int j = i + 1; j < n; j++) {
            swap(a[i], a[j]);
            ans = min(ans, fast_inv(a, 0, n).first);
            swap(a[i], a[j]);
        }
    }

    cout << ans << endl;

    return 0;
}