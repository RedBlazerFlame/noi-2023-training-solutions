#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n, 0);
    for(int& v : a) {
        cin >> v;
    }

    sort(a.begin(), a.end(), std::greater<int>());

    int sum = reduce(a.begin(), a.end(), 0, [](int n1, int n2) {return n1 + n2;});

    int min_req = (sum + 2) >> 1;
    int pref_sum = 0;

    int i;

    for(i = 0; i < n; i++) {
        pref_sum += a[i];
        if(pref_sum >= min_req) break;
    }

    cout << i + 1 << endl;

    return 0;
}