#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int bsort_count(vector<int> a) {
    int n = a.size();

    int i, j, count = 0;

    for(int i = 0; i < n - 1; i++) {
        for(int j = 0; j < n - 1; j++) {
            if(a[j] > a[j + 1]){
                int x = a[j];
                a[j] = a[j + 1];
                a[j + 1] = x;
                count++;
            }
        }
    }

    return count;
}

int main() {
    int n;
    cin >> n;
    vector<int> a(n, 0);

    for(int& v : a) {
        cin >> v;
    }

    int max_inv = numeric_limits<int>::min();
    int maxi = 0, maxj = 0;
    for(int i = 0; i < n - 1; i++) {
        for(int j = i + 1; j < n; j++) {
            if(a[i] - a[j] > max_inv) {
                max_inv = a[i] - a[j];
                maxi = i;
                maxj = j;
            }
        }
    }

    int x = a[maxj];
    a[maxj] = a[maxi];
    a[maxi] = x;

    cout << bsort_count(a) << endl;

    return 0;
}