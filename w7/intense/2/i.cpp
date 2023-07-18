/*
OIOOI
OOIOI

-1467
2-3-5

IOI
IIO

-25
134

I found a counter:
IOIIO
OI
How to do this?

What if I dp this?

dp(m, n, I) = max(dp(m_minI, n, O), dp(m, n_minI, O))
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    int m, n;
    cin >> m >> n;
    string s, t;
    cin >> s >> t;

    char target = 'I';

    int curs = 0, curt = 0, nextso = 0, nextsi = 0, nextto = 0, nextti = 0;

    int ans = 0;
    while(curs < m || curt < n) {
        while(nextso < m && s[nextso] != 'O') nextso++;
        if(!(nextso < m)) nextso = numeric_limits<int>::max() - 20000;
        while(nextsi < m && s[nextsi] != 'I') nextsi++;
        if(!(nextsi < m)) nextsi = numeric_limits<int>::max() - 20000;
        while(nextto < n && t[nextto] != 'O') nextto++;
        if(!(nextto < n)) nextto = numeric_limits<int>::max() - 20000;
        while(nextti < n && t[nextti] != 'I') nextti++;
        if(!(nextti < n)) nextti = numeric_limits<int>::max() - 20000;

        if(target == 'I') {
            char optimal = '?';
            int s_score = nextsi - curs;
            int t_score = nextti - curt;
            if(s_score > 2000 && t_score > 2000) break;
            if(s_score < t_score) {
                if(nextsi < m) ans++;
                curs = nextsi + 1;
                nextsi = curs;
                nextso = curs;
            } else {
                if(nextti < n) ans++;
                curt = nextti + 1;
                nextti = curt;
                nextto = curt;
            }
            target = 'O';
        } else {
            int s_score = nextso - curs;
            int t_score = nextto - curt;
            if(s_score > 2000 && t_score > 2000) break;
            if(s_score < t_score) {
                if(nextso < m) ans++;
                curs = nextso + 1;
                nextsi = curs;
                nextso = curs;
            } else {
                if(nextto < n) ans++;
                curt = nextto + 1;
                nextti = curt;
                nextto = curt;
            }
            target = 'I';
        }
    }

    ans = ans - ((ans & 0b1) ^ 0b1);
    ans = max(ans, 0);

    cout << ans << endl;
    return 0;
}