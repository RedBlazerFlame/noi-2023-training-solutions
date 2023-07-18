#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main() {
    map<string, int> counts;
    int n;
    cin >> n;
    for(int i = 0; i < n ; i++) {
        string s;
        cin >> s;

        if(counts.find(s) == counts.end()) {
            counts[s] = 0;
        }
        counts[s]++;
    }
    int k;
    cin >> k;
    int last_day = 0;
    for(int i = 0; i < k; i++) {
        string c;
        cin >> c;
        if(counts[c] <= 0) {
            last_day = i + 1;
            break;
        }
        counts[c]--;
    }
    cout << (last_day == 0 ? "OK" : to_string(last_day)) << endl; 
    return 0;
}