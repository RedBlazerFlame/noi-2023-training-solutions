#include <iostream>
#include <string>
using namespace std;

int main() {
    string t = "hello";
    string s;
    cin >> s;
    int cur_ind = 0;
    
    for(int i = 0 ; i < s.size(); i++ ) {
        if(t[cur_ind] == s[i]) cur_ind++;
        if(cur_ind == t.size()) break;
    }
    
    cout << (cur_ind == t.size() ? "YES" : "NO") << endl;
    
    return 0;
}