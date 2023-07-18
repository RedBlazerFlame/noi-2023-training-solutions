#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    int a1, b1, c1;
    cin >> a1 >> b1 >> c1;
    int a2, b2, c2;
    cin >> a2 >> b2 >> c2;

    cout << min({a2 / a1, b2 / b1, c2 / c1}) << endl;

    return 0;
}