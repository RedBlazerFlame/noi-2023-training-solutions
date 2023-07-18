#include <bits/stdc++.h>
using namespace std;

int nucleotide_index(char c) {
    switch(c) {
        case 'A':
            return 0b00;
        case 'T':
            return 0b01;
        case 'C':
            return 0b10;
        default:
        case 'G':
            return 0b11;
    }
}

char nucleotides[] = {'A', 'T', 'C', 'G'};

int complement(char c) {
    return nucleotides[nucleotide_index(c) ^ 0b1];
}

int main() {
    int n;
    cin >> n;

    string s;
    cin >> s;

    vector<int> counts(4, 0);

    int ans = 0;
    for(int i = 0; i < n - 1; i++) {
        for(int j = 0; j < 4; j++) {
            counts[j] = 0;
        }
        for(int j = i + 2; j <= n; j += 2) {
            for(int k = j - 2; k < j; k++) {
                counts[nucleotide_index(s[k])]++;
            }

            if(counts[0] == counts[1] && counts[2] == counts[3]) {
                ans++;
            }
        }
    }

    cout << ans << endl;

    return 0;
}