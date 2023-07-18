#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<int> count(int num_change, string s) {
    int num_is = 0;

    vector<int> count_pref = {0, 0, 0};

    for(char c : s) {
        if(c == 'I') {
            num_is += 1;
        }

        if((c == 'I' && num_is <= num_change) || c == 'J') {
            count_pref[0] += 1;
        } else if(c == 'O' && count_pref[0] > 0) {
            count_pref[0] --;
            count_pref[1] ++;
        } else if(c == 'I' && count_pref[1] > 0) {
            count_pref[1] --;
            count_pref[2] ++;
        }
    }

    return count_pref;
}

int main() {
    int n;
    cin >> n;
    string s;
    cin >> s;

    vector<int> base_counts = count(0, s);
    int base_j_count = base_counts[0];
    int base_jo_count = base_counts[1];

    int l = 0, r = n;
    while(r - l > 1) {
        int m = (l + r) >> 1;

        vector<int> pref_counts = count(m, s);

        if(pref_counts[0] == base_j_count && pref_counts[1] == base_jo_count) l = m;
        else r = m;
    }

    cout << count(l, s)[2] << endl;
}