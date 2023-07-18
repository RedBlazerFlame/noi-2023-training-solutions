#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    string t = "";

    int curlen;
    for(char& c : s) {
        string cur_s({c});
        t.append(cur_s);

        curlen = t.length();
        if(curlen >= 3 && t[curlen - 3] == 'f' && t[curlen - 2] == 'o' && t[curlen - 1] == 'x') {
            t.erase(curlen - 3, 3);
        }
    }

    cout << t.length() << endl;
    return 0;
}