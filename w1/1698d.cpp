#include <bits/stdc++.h>
using namespace std;
/*
1 2 3 4 5
3 2 1 5 4

If a subarray contains
odd within range, then it contains the thing
*/

int query(int l, int r) {
    cout << "? " << l + 1 << " " << r + 1 << endl;
    vector<int> nums(r - l + 1, 0);
    int num_fixed_pts = 0;
    for(int& num : nums) {
        cin >> num;
        num--;

        if(l <= num && num <= r) {
            num_fixed_pts++;
        }
    }

    return num_fixed_pts;
}

int main() {
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;

        int l = 0, r = n - 1, m;
        while(l < r) {
            m = (l + r) >> 1;

            if(query(l, m) & 1) {
                r = m;
            } else {
                l = m + 1;
            }
        }

        cout << "! " << l + 1 << endl;
    }
    return 0;
}