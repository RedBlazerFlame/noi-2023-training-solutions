#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    int t;
    cin >> t;
    while(t--) {
        int p;
        cin >> p;

        cout << 1000 << endl;

        for(int i = 0; i < 1000; i++) {
            cout << (i % 500) + 1 << (i < 999 ? " " : "");
        }
        cout << endl;
        
        for(int i = 0; i < 1000; i++) {
            for(int j = 0; j < 1000; j++) {
                cout << (i == j ? 0 : 1);
            }
            cout << endl;
        }

        while(p--) {
            int sz;
            cin >> sz;

            while(sz--) {
                int h;
                cin >> h;

                cout << h + (sz & 1 ? 500 : 0) << " ";
            }
            cout << endl;
        }
    }

    return 0;
}