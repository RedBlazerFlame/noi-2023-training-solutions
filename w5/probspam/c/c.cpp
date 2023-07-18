#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/*
Wait, what if I...


X/X X|X X|X X

Looks like the halving
approach is not the best

BUT, I can think of a brute force now HAHA

Time complexity is N choose L, which is probably
not going to pass now that I think about it .-.

Unless... what if we binary search the answer?

X/X X X X X X

Could you tell whether the above is possible?
Yes! Just go through left to right and keep cutting ^^
Time complexity: O(L log L), which passes 1-4 likely

Can't we do better though?

Yes!

Let's say that we're checking if the answer is 4
Simple case:
15, how many cuts? (3)
12, how many cuts? (2)
[9, 12] -> 2

(l - 1) // ans cuts required
Time complexity: O(N log max l)
*/

bool poss(const vector<ll>& l, ll c, ll ans) {
    ll cuts = 0;
    for(const ll& curl : l) {
        cuts += (curl - 1) / ans;
        if(cuts > c) return false;
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    int t;
    cin >> t;
    while(t--) {
        ll n, c;
        cin >> n >> c;
        vector<ll> lengths(n, 0);

        int maxl = 0;
        for(ll& v : lengths) {
            cin >> v;
            if(v > maxl) {
                maxl = v;
            }
        }

        ll l = 0, r = maxl;
        while(r - l > 1) {
            ll m = (l + r) >> 1;

            if(poss(lengths, c, m)) r = m;
            else l = m;
        }

        cout << r << "\n";
    }
}