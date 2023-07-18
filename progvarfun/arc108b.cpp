#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    list<char> sl;
    for(const char& c : s) {
        sl.push_back(c);
    }

    int i = 0;
    auto it = sl.begin();
    while(i < sl.size() - 2) {
        if(*it == 'f' && *std::next(it, 1) == 'o' && *std::next(it, 2) == 'x') {
            it = sl.erase(it, std::next(it, 3));
            int targ_ind = max(-1, i - 3);
            advance(it, targ_ind - i);
            i = targ_ind;
        }
        it++;
        i++;
    }

    cout << sl.size() << endl;

    return 0;
}