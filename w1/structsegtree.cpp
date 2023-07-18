#include <bits/stdc++.h>
using namespace std;

class Node {
    public:
        int l;
        int r;
        int v;
        Node* left;
        Node* right;

        Node() {
            left = NULL;
            right = NULL;
            l = 0;
            r = 0;
            v = 0;
        }

        ~Node() {
            delete left;
            delete right;
            left = NULL;
            right = NULL;
        }

        inline int op(int a, int b) {
            return ((r - l + 1) & 0b10101010101010101010101010101010 ? a | b : a ^ b);
        }

        inline int id() {
            return 0;
        }

        void build(const vector<int>& arr, int a_l = 0, int a_r = -1) {
            if(a_r == -1) a_r = arr.size() - 1;
            int m = (a_l + a_r) >> 1;
            l = a_l;
            r = a_r;
            if(l == r) {
                v = arr[l];
                return;
            }
            Node* ln = new Node();
            Node* rn = new Node();
            ln->build(arr, a_l, m);
            rn->build(arr, m + 1, a_r);
            v = op(ln->v, rn->v);
            left = ln;
            right = rn;
        }

        int qry(int ql, int qr) {
            ql = max(ql, l);
            qr = min(qr, r);
            if(ql == l && qr == r) {
                return v;
            }

            if(ql > r || qr < l || ql > qr) {
                return id();
            }

            if(l == r) return id();

            return op(left->qry(ql, qr), right->qry(ql, qr));
        }

        void upd(int i, int nv) {
            if(i < l || i > r) {
                return;
            }

            if(l == i && i == r) {
                v = nv;
                return;
            }

            if(l == r) return;

            left->upd(i, nv);
            right->upd(i, nv);

            v = op(left->v, right->v);
        }
};

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> a(1 << n, 0);
    for(int& v : a) {
        cin >> v;
    }
    Node tr;
    tr.build(a);
    while(m--) {
        int p, b;
        p--;
        tr.upd(p, b);
        cout << tr.qry(0, (1 << n) - 1) << endl;
    }
    return 0;
}