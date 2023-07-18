#include <bits/stdc++.h>
using namespace std;
using ll = long long;
vector<vector<int>> a;

int di[] = {-1,1,0,0};
int dj[] = {0,0,-1,1};
int n;

vector<vector<int>> vis;



int canEnd(int ci,int cj){
    vector<vector<int>> viss = vis;
    vector<pair<int,int>> stk;
    stk.emplace_back(ci, cj);
    viss[ci][cj] = 1;
    while(stk.size()){
        auto [i,j] = stk.back(); stk.pop_back();
        if(i == n - 1 && j == n - 1) return 1;
        for(int k = 0; k < 4; k++){
            int ni = i + di[k], nj = j + dj[k];
            if(0 <= min(ni,nj) && max(ni,nj) < n && !viss[ni][nj] && !vis[ni][nj]){
                stk.emplace_back(ni, nj);
                viss[ni][nj] = 1;
            }
        }
    }
    return 0;
}

vector<pair<int,int>> nei(int i,int j){
    vector<pair<int,int>> res;
    for(int k = 0; k < 4; k++){
        int ni = i + di[k], nj = j + dj[k];
        if(0 <= min(ni,nj) && max(ni,nj) < n && !vis[ni][nj] && canEnd(ni, nj)){
            res.emplace_back(ni, nj);
        }
    }
    cout << "ASDASDSADSADSAD" << endl;
    return res;
}

int main(){
    cin >> n;
    a = vector<vector<int>>(n, vector<int>(n));
    for(auto &x: a){
        for(int &y: x){
            cin >> y;
        }
    }
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    vis = vector<vector<int>>(n, vector<int>(n));
    int i = 0, j = 0;
    ll ths = a[0][0];
    vis[0][0] = 1;
    while(i != n - 1 || j != n - 1){
        cout << i << " " << j << endl;
        vector<pair<int,int>> can = nei(i, j);
        cout << can.size() << " ASD " << endl;
        shuffle(can.begin(), can.end(), rng);
        cout << can.size() << "ASDS" << endl;
        auto [ni,nj] = can[0];
        cout << ni << " " << nj << endl;
        ths += a[ni][nj];
        i = ni, j = nj;
        cout << i << " " << j << endl;
        vis[ni][nj] = 1;
    }
    cout << ths;
}