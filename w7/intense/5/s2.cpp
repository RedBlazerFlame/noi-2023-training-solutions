#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pint;

// pair<int, vector<int>> fast_inv(const vector<int>& vec, int l, int r) {
//     if(r - l == 1) {
//         vector<int> res;
//         res.push_back(vec[l]);
//         return {0, res};
//     }

//     int n = r - l;
//     int m = (l + r) >> 1;
//     auto [linv, lv] = fast_inv(vec, l, m);
//     auto [rinv, rv] = fast_inv(vec, m, r);
//     int count_inv = linv + rinv;

//     vector<int> sorted;
//     int pl = 0, pr = 0;
        
//     while(pl < (int)lv.size() && pr < (int)rv.size()) {
//         if(rv[pr] < lv[pl]) {
//             sorted.push_back(rv[pr]);
//             pr++;
//             count_inv += lv.size() - pl;
//         } else {
//             sorted.push_back(lv[pl]);
//             pl++;
//         }
//     }

//     while(pl < (int)lv.size()) {
//         sorted.push_back(lv[pl]);
//         pl++;
//     }

//     while(pr < (int)rv.size()) {
//         sorted.push_back(rv[pr]);
//         pr++;
//     }

//     return {count_inv, sorted};
// }

int main() {
    int n;
    cin >> n;

    vector<vector<int>> grid;
    for(int i = 0; i < n + 1; i++) {
        vector<int> row(n + 1, 0);
        grid.push_back(row);
    }

    vector<int> a(n, 0);
    vector<pint> awp;

    for(int i = 0; i < n; i++) {
        cin >> a[i];
        awp.push_back({a[i], i});
    }

    sort(awp.begin(), awp.end());

    for(int i = 0; i < n; i++) {
        a[awp[i].second] = i;
        grid[i + 1][awp[i].second + 1] = 1;
    }

    for(int i = 0; i < n + 1; i++) {
        for(int j = 0; j < n + 1; j++) {
            if(i > 0) grid[i][j] += grid[i - 1][j];
            if(j > 0) grid[i][j] += grid[i][j - 1];
            if(i > 0 && j > 0) grid[i][j] -= grid[i - 1][j - 1];
            // cout << grid[i][j] << "\t";
        }
        // cout << endl;
    }

    // int base_inv = fast_inv(a, 0, a.size()).first;
    int base_inv = 0;
    for(int i = 0; i < n - 1; i++) {
        for(int j = i + 1; j < n; j++) {
            base_inv += (a[i] > a[j] ? 1 : 0);
        }
    }

    int ans = base_inv;
    for(int i = 0; i < n - 1; i++) {
        for(int j = i + 1; j < n; j++) {
            if(a[i] > a[j]) {
                ans = min(ans, base_inv - 2 * (
                    grid[a[i] + 1][j + 1] + grid[a[j]][i]
                    - grid[a[i] + 1][i] - grid[a[j]][j + 1] - 2
                ) - 1);
            }
        }
    }

    cout << (base_inv == 0 ? 1 : ans) << endl;

    return 0;
}