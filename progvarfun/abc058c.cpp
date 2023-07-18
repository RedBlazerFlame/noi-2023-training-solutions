#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    multiset<char> acc;
    for(int i = 0; i < 26; i++) {
        for(int j = 0; j < 50; j++) {
            acc.insert((char)(((int)'a') + i));
        }
    }
    multiset<char> cur;
    multiset<char> next_acc;
    string curstr;
    while(n--) {
        cur.clear();
        next_acc.clear();
        cin >> curstr;
        for(const char& c : curstr) {
            cur.insert(c);
        }

        set_intersection(acc.begin(), acc.end(), cur.begin(), cur.end(), inserter(next_acc, next_acc.begin()));
        acc = next_acc;
    }

    for(const char& c : acc) {
        cout << c;
    }
    cout << endl;
    return 0;
}