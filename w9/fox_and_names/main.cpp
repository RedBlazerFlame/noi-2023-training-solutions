/*
Learnings:
1. When frustrated, take a break
    - I've been trying to solve it a while ago and
    I got very frustrated because I kept getting wrong answer,
    After I took a break, I solved it in 2 minutes
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

pair<char, char> diff(const string& a, const string& b) {
    int maxchar = min(a.size(), b.size());
    for(int i = 0; i < maxchar; i++) {
        if(a[i] != b[i]) return {a[i], b[i]};
    }

    return {'a', 'a'}; // Sentinel value
}

void dfs(int node, const vector<vector<char>>& in_adj, vector<bool>& vis, vector<char>& tpsort) {
    if(vis[node]) return;
    vis[node] = true;
    for(char c : in_adj[node]) {
        dfs((int)c - (int)'a', in_adj, vis, tpsort);
    }
    tpsort.push_back((char)(node + (int)'a'));
}

bool has_cycle(int node, const vector<vector<char>>& in_adj, const vector<vector<char>>& out_adj, vector<bool>& vis, vector<bool>& in_path) {
    stack<int> s;
    s.push(node);

    while(!s.empty()) {
        int cur = s.top();
        s.pop();

        vis[cur] = true;
        in_path[cur] = true;

        for(char i : in_adj[cur]) {
            int i_num = (int)i - (int)'a';

            if(in_path[cur]) return true;
            if(vis[cur]) continue;

            s.push(i_num);
            break;
        }
    }
    return false;
}

string solve(int n, const vector<string>& names) {
    vector<vector<char>> in_adj;
    vector<vector<char>> out_adj;

    for(int i = 0; i < 26; i++) {
        vector<char> in_row;
        in_adj.push_back(in_row);
        vector<char> out_row;
        out_adj.push_back(out_row);
    }

    for(int i = 0; i < n - 1; i++) {
        const string& s1 = names[i];
        const string& s2 = names[i + 1];

        const auto& [c1, c2] = diff(s1, s2);
        if(c1 == c2 && s1.length() > s2.length()) return "Impossible";
        if(c1 == c2) continue;

        in_adj[(int)c2 - (int)'a'].push_back(c1);
        out_adj[(int)c1 - (int)'a'].push_back(c2);
    }

    // vector<bool> vis1a(26, false);

    // for(int i = 0; i < 26; i++) {
    //     vector<bool> in_path(26, false);
    //     if(has_cycle(i, in_adj, out_adj, vis1a, in_path)) return "Impossible";
    // }

    vector<char> tpsort;
    vector<bool> vis2(26, false);

    for(int i = 0; i < 26; i++) {
        dfs(i, in_adj, vis2, tpsort);
    }

    ostringstream strm;
    for(char c : tpsort) {
        strm << c;
    }
    string res = strm.str();
    string mapping = "qwertyuiopasdfghjklzxcvbnm";
    for(int i = 0; i < 26; i++) {
        mapping[(int)res[i] - (int)'a'] = (char)(i + (int)'a');
    }

    // Validate whether the string works 
    for(int i = 0; i < n - 1; i++) {
        string rs1 = names[i];
        string rs2 = names[i + 1];
        ostringstream sstrm1;
        ostringstream sstrm2;

        for(int i = 0; i < rs1.size(); i++) {
            sstrm1 << mapping[(int)rs1[i] - (int)'a'];
        }

        for(int i = 0; i < rs2.size(); i++) {
            sstrm2 << mapping[(int)rs2[i] - (int)'a'];
        }

        if(!(sstrm1.str() < sstrm2.str())) return "Impossible";
    }

    return res;
}

int main() {
    int n;
    cin >> n;

    vector<string> names;
    for(int i = 0; i < n; i++) {
        string s;
        cin >> s;
        names.push_back(s);
    }

    cout << solve(n, names) << endl;

    return 0; 
}