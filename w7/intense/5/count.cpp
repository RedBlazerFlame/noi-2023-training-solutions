#include <vector>
#include <iostream>
using namespace std;
typedef long long ll;

ll bsort_count(vector<ll> a) {
    ll n = a.size();

    ll i, j, count = 0ll;

    for(ll i = 0ll; i < n - 1; i++) {
        for(ll j = 0ll; j < n - 1; j++) {
            if(a[j] > a[j + 1]){
                ll x = a[j];
                a[j] = a[j + 1];
                a[j + 1] = x;
                count++;
            }
        }
    }

    return count;
}

int main() {
    ll t;
    cin >> t;
    while(t--) {
        ll n;
        cin >> n;
        vector<ll> v(n, 0);
        for(ll& cv : v) {
            cin >> cv;
            cout << cv << " ";
        }

        cout << " -> " << bsort_count(v) << endl;
    }

    return 0;
}