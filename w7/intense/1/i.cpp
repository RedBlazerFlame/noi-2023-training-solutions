/*
Insight 1: including an alternating sequence
in the region to swap is not a good idea
Insight 2: wait what if we just take the longest alternating
sequence and flip it?

0011010001
0010101001
-XXXXXXX--

That doesn't work ;-;
00101010101111111111111111111010101001010101
010101010101

Wait, what if we get the lengths of alternating regions
and then get the largest value of a_i + a_(i + 1)
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

template<typename T>
T get_or_def(const vector<T>& v, int ind, T def) {
    return (ind < 0 || ind >= v.size() ? def : v[ind]);
}

int main() {
    int n;
    cin >> n;
    vector<int> a(n, 0);
    for(int& v : a) {
        cin >> v;
    }
    vector<int> alt_lengths;

    int needed = a[0];
    int curlen = 1;
    for(int i = 1; i < n; i++) {
        int cur = a[i];
        if(cur != needed) {
            curlen ++;
            needed ^= 0b1;
        } else {
            alt_lengths.push_back(curlen);
            curlen = 1;
            needed = cur;
        }
    }
    alt_lengths.push_back(curlen);

    int ans = numeric_limits<int>::min();
    for(int i = 0; i < alt_lengths.size(); i++) {
        int cursum = get_or_def(alt_lengths, i - 1, 0) +
        get_or_def(alt_lengths, i, 0) +
        get_or_def(alt_lengths, i + 1, 0);
        ans = max(ans, cursum);
    }

    cout << ans << endl;

    return 0;
}