#include<bits/stdc++.h>
using namespace std;

struct l {
    int x;
};

int main() {
    l a = {0};
    l b = {1};

    swap(a.x, b.x);
    cout << a.x << endl;

    return 0;
}