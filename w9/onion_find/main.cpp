#include <bits/stdc++.h>
using namespace std;

template<typename A, typename B>
A reduce_poly(const vector<B>& v, A init, function<A(A, B)> fn) {
    A res = init;
    for(const B& c : v) {
        res = fn(res, c);
    }

    return res;
}

class UnionFind {
    public:
        int n;
        vector<int> par;
        vector<int> csize;
        vector<int> onions;
        UnionFind(int a_n, const vector<char>& v): n(a_n) {
            for(int i = 0; i < n; i++) {
                par.push_back(i);
                csize.push_back(1);
                onions.push_back(v[i] == 'O' ? 1 : 0);
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
                onions[parb] += onions[para];
            } else {
                par[parb] = para;
                csize[para] += csize[parb];
                onions[para] += onions[parb];
            }
        }
};

inline int ind(int i, int j, int c) {
    return i * c + j;
}

int main() {
    int t;
    cin >> t;

    while(t--) {
        int r, c;
        cin >> r >> c;

        vector<char> grid(r * c, ' ');

        int sind;

        for(int i = 0; i < r; i++) {
            for(int j = 0; j < c; j++) {
                char& cur = grid[ind(i, j, c)];
                cin >> cur;
                if(cur == 'S') {
                    cur = '.';
                    sind = ind(i, j, c);
                }
            }
        }

        UnionFind uf(r * c, grid);


        for(int i = 0; i < r; i++) {
            for(int j = 0; j < c; j++) {
                if(i > 0 && grid[ind(i, j, c)] != '#' && grid[ind(i - 1, j, c)] != '#') uf.unify(ind(i, j, c), ind(i - 1, j, c));
                if(j > 0 && grid[ind(i, j, c)] != '#' && grid[ind(i, j - 1, c)] != '#') uf.unify(ind(i, j, c), ind(i, j - 1, c));
            }
        }

        int sc = uf.find(sind);
        
        int ans_l2 = 0;
        for(int i = 0; i < r; i++) {
            for(int j = 0; j < c; j++) {
                if(grid[ind(i, j, c)] == '#') {
                    vector<int> adj;
                    if(i > 0) adj.push_back(ind(i - 1, j, c));
                    if(j > 0) adj.push_back(ind(i, j - 1, c));
                    if(i < r - 1) adj.push_back(ind(i + 1, j, c));
                    if(j < c - 1) adj.push_back(ind(i, j + 1, c));

                    if(reduce_poly<bool, int>(adj, false, [&uf, sc](bool acc, int cur_ind) { return acc || (uf.find(cur_ind) == sc); })) {
                        set<int> comps;
                        vector<int> comps_vec;
                        for(int ind : adj) comps.insert(uf.find(ind));
                        for(int comp : comps) comps_vec.push_back(comp);
                        ans_l2 = max(ans_l2, reduce_poly<int, int>(comps_vec, 0, [&uf](int acc, int cur) {
                            return acc + uf.onions[uf.find(cur)];
                        }));
                    }
                }
            }
        }

        cout << uf.onions[sc] << " " << max(ans_l2, uf.onions[sc]) << endl;
    }

    return 0;
}