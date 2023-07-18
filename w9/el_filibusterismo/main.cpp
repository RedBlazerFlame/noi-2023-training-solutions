#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class UnionFind {
    public:
        vector<int> par;
        vector<int> csize;
        int n;
        UnionFind(int a_n): n(a_n) {
            for(int i = 0; i < n; i++) {
                par.push_back(i);
                csize.push_back(1);
            }
        }
        int find(int i) {
            int orig = i;
            while(i != par[i]) {
                i = par[i];
            }
            
            while(orig != par[orig]) {
                int neworig = par[orig];
                par[orig] = i;
                orig = neworig;
            }
            
            return i;
        }
        void unify(int a, int b) {
            int para = find(a), parb = find(b);
            
            if(para == parb) return;
            
            if(csize[para] < csize[parb]) {
                par[para] = parb;
                csize[parb] += csize[para];
            } else {
                par[parb] = para;
                csize[para] += csize[parb];
            }
        }
};

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    
    int n, m, v;
    cin >> n >> m >> v;
    v--;
    
    UnionFind uf(n);
    
    for(int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        uf.unify(a, b);
    }
    
    cout << uf.csize[uf.find(v)] << endl;
    return 0;
}
