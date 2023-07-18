#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    vector<vector<vector<ll>>> a;
    for(int i = 0; i < 2000; i++) {
        vector<vector<ll>> a1;
        for(int j = 0; j < 2000; j++) {
            vector<ll> a2;
            for(int k = 0; k < 2; k++) {
                a2.push_back(-1ll);
            }
            a1.push_back(a2);
        }
        a.push_back(a1);
    }

    cout << "Done!" << endl;
    return 0;
}