/*
-10 -10 -10 -10
The answer is the number of occurences of
the integer that occurs the most
However, if all of it is equal to just that one integer, then the answer is n - 1

Okay, but if 0, 0, 0, 0, the answer is n

Finally, we have to consider the case wherein by updating one of the values,
we introduce a new occurrence
Let the sum of the list be S
Let the element that occurred the most be c
Thus, the target sum of the list must be 2c
To get this target sum, we must add 2c - S to one of the elements

if an element e exists s.t. 2c - S + e = c, we need to add 1
e = S - c
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    int t;
    cin >> t;

    while(t--) {
        ll n;
        cin >> n;
        vector<ll> a(n, 0);
        ll suma = 0;
        for(ll& av : a) {
            cin >> av;
            suma += av;
        }

        sort(a.begin(), a.end());

        ll maxocc = 1;
        ll maxoccvalue = 0;
        ll curocc = 1;
        ll curv = numeric_limits<ll>::max();

        for(ll av : a) {
            if(curv != av) {
                curv = av;
                curocc = 1;
            } else {
                curocc++;
            }
            if(curocc > maxocc) {
                maxocc = curocc;
                maxoccvalue = curv;
            }
        }

        // Post-processing
        if(maxocc == n && maxoccvalue == 0) {
            cout << n << endl;
        } else if(maxocc == n) {
            cout << n - 1 << endl;
        } else {
            ll target_elem = suma - maxoccvalue;

            ll l = 0, r = n - 1;

            while(r - l > 1) {
                ll m = (l + r) >> 1;

                if(a[m] >= target_elem) r = m;
                else l = m;
            }

            if(a[r] == target_elem) cout << maxocc + 1 << endl;
            else cout << maxocc << endl;
        }
    }

    return 0;
}