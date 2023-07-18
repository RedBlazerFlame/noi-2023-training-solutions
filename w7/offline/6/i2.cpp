#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const char letters[4] = {'K', 'B', 'H', 'Y'};
const int max_times_retry = 100;

bool check_valid(const vector<int>& a, int n) {

    for(int i = 0; i < n - 2; i++) {
        for(int j = i + 2; j < n; j += 2) {
            int mid = (i + j) >> 1;

            if(a[i] == a[mid] && a[mid] == a[j]) {
                return false;
            }
        }
    }

    return true;
}

int main() {
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;

        if(n == 1) {
            cout << "K" << endl;
            continue;
        }
        if(n == 2) {
            cout << "KK" << endl;
            continue;
        }
        vector<int> sol(n, 0);
        
        int times_retried = 0;
        do {
            for(int i = 0; i < n - 2; i++) {
                for(int j = i + 2; j < n; j += 2) {
                    int mid = (i + j) >> 1;

                    if(sol[i] == sol[mid] && sol[mid] == sol[j]) {
                        if(times_retried % 3 == 0) {
                            sol[j] = (sol[j] + 1) & 0b11;
                        } else if(times_retried % 3 == 1) {
                            sol[mid] = (sol[mid] + 1) & 0b11;
                        } else {
                            sol[i] = (sol[i] + 1) & 0b11;
                        }
                    }
                }
            }

            times_retried++;
        } while((!check_valid(sol, n)) && times_retried > max_times_retry);

        if(!check_valid(sol, n)) {
            cout << "PASS" << endl;
        } else {
            for(int i = 0; i < n; i++) {
                    cout << letters[sol[i]];
                }
                cout << endl;
        }
    }
}