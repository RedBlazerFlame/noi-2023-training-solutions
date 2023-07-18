#include <iostream>
using namespace std;

int main() {
    // const int n = 100;
    // bool isprime[n];
    // for (int i = 2; i < n; i++) isprime[i] = true;
    // for (int i = 2; i < n; i++) {
    //     if (!isprime[i]) continue;
    //     for (int j = i << 1; j < n; j += i) isprime[j] = false;
    // }

    // for(int i = 1; i < n; i++) {
    //     if(isprime[i]) cout << i << endl;
    // }

    const int n = 100;
    bool isprime[n];
    for (int i = 2; i < n; i++) isprime[i] = true;
    for (int i = 2; i < n; i++) {
        if (!isprime[i]) continue;
        for (int j = i << 1; j < n; j += i) if(j/i % i != 0) isprime[j] = false;
    }

    for(int i = 1; i < n; i++) {
        if(isprime[i]) cout << i << endl;
    }
    return 0;
}