#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/*
This problem reduces to the maximum subarray sum problem
How?

Well, define d_a to be the change in the number of 0s if you flip
a certain index
Thus, d_a = 1 if a == 1 else -1
*/

int main() {
    int t;
    cin >> t;

    while(t--) {
        int n;
        string s;
        cin >> n;
        cin >> s;
        int base_ones = 0;
        int delta_zeros = 0;
        int max_delta_zeros = 0;

        for(char& c : s) {
            if(c == '1') {
                delta_zeros ++;
                base_ones++;
            } else {
                delta_zeros --;
            }
            delta_zeros = max(delta_zeros, 0);
            if(delta_zeros > max_delta_zeros) max_delta_zeros = delta_zeros;
        }

        cout << (base_ones == 0 ? 1 : base_ones - max_delta_zeros) << "\n";
    }

    return 0;
}