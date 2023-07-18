/*
def bit(num, j, i):
    return (num >> (j * 5 + i)) & 1

def print_grid(num):
    for i in range(5):
        for j in range(5):
            print("#" if bit(num, i, j) else ".", end="")
        print("")

for i in range(1 << 25):
    count = 0
    for j in range(3):
        for k in range(3):
            corner_dolomite = bit(i, j, k) + bit(i, j + 2, k) + bit(i, j, k + 2) + bit(i, j + 2, k + 2)
            other_dolomite = bit(i, j, k + 1) + bit(i, j + 1, k) + bit(i, j + 1, k + 1) + bit(i, j + 1, k + 2) + bit(i, j + 2, k + 1)
            if(corner_dolomite == 3 and other_dolomite == 0):
                count += 1
    if(count == 4):
        print_grid(i)
        print("")
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int bit(int num, int j, int i, int maxx) {
    return (num >> (j * maxx + i)) & 1;
}

void print_grid(int num, int y, int x) {
    for(int i = 0; i < y; i++) {
        for(int j = 0; j < x; j++) {
            cout << (bit(num, i, j, x) ? "#" : ".");
        }
        cout << endl;
    }
}

int main() {
    int maxy, maxx;
    cin >> maxy >> maxx;
    int max_count = 0;
    for(int i = 0; i < (1 << (maxy * maxx)); i++) {
        int count = 0;
        for(int j = 0; j < maxy - 2; j++) {
            for(int k = 0; k < maxx - 2; k++) {
                int corner_dolomite = bit(i, j, k, maxx) + bit(i, j + 2, k, maxx) + bit(i, j, k + 2, maxx) + bit(i, j + 2, k + 2, maxx);
                int other_dolomite = bit(i, j, k + 1, maxx) + bit(i, j + 1, k, maxx) + bit(i, j + 1, k + 1, maxx) + bit(i, j + 1, k + 2, maxx) + bit(i, j + 2, k + 1, maxx);
                if(corner_dolomite == 3 and other_dolomite == 0) {
                    count += 1;
                }
            }
        }
        if(count > max_count) {
            max_count = count;
            cout << max_count << endl;
            print_grid(i, maxy, maxx);
            cout << endl;
        }
    }
    return 0;
}