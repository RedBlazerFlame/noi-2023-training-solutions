#include <bits/stdc++.h>
using namespace std;

int gcd(int a, int b) {
    while(a != 0) {
        int r = b % a; b = a; a = r;
    }

    return b;
}

int main() {
    cout << gcd(10, 20) << endl;
    cout << gcd(10, 21) << endl;
    cout << gcd(25, 10) << endl;
    cout << gcd(0, 1) << endl;
    return 0;
}