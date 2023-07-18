#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int brute_inv(vector<int> v) {
    int n = v.size();

    int ans = 0;

    for(int i = 0; i < n - 1; i++) {
        for(int j = i + 1; j < n; j++) {
            if(v[i] > v[j]) ans++;
        }
    }

    return ans;
}

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
        
    while(pl < lv.size() && pr < rv.size()) {
        if(rv[pr] < lv[pl]) {
            sorted.push_back(rv[pr]);
            pr++;
            count_inv += lv.size() - pl;
        } else {
            sorted.push_back(lv[pl]);
            pl++;
        }
    }

    while(pl < lv.size()) {
        sorted.push_back(lv[pl]);
        pl++;
    }

    while(pr < rv.size()) {
        sorted.push_back(rv[pr]);
        pr++;
    }

    return {count_inv, sorted};
}

int main() {
    vector<int> v = {8, 4, 1, 2};
    cout << brute_inv(v) << endl;
    cout << fast_inv(v, 0, v.size()).first << endl;

    return 0;
}