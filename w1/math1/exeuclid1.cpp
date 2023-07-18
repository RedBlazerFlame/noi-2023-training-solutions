#include<bits/stdc++.h>
using namespace std;

/*
Finds a solution to ax + by = gcd(a, b)

ax + by = gcd(a, b)
(b mod a)x' + ay' = gcd(b mod a, a) = gcd(a, b)
b = aq + b mod a
b mod a = b - aq
(b - aq)x' + ay' = gcd(a, b)
a(y' - qx') + bx' = gcd(a, b)
*/
pair<int, int> exeuclid1(int a, int b) {
    if(a == 0) return {0, 1};

    int xp, yp;
    tie(xp, yp) = exeuclid1(b % a, a);
    int q = b / a;
    return {yp - q * xp, xp};
}

pair<int, int> exeuclid2(int a, int b, int c) {
    int x, y;
    tie(x, y) = exeuclid1(a, b);
    int mult = c / gcd(a, b);
    return {mult * x, mult * y};
}

int gcd(int a, int b) {
    while(a != 0) {
        int r = b % a; b = a; a = r;
    }

    return b;
}

int main() {
    // Find a solution to 2x + 3y = 6
    int x, y;
    tie(x, y) = exeuclid2(2, 3, 6);
    cout << x << " " << y << endl;

    return 0;
}