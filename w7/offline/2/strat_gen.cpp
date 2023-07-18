/*
1 2 3 4 5 6

(6 choose 3) = 20

1 2 3 4 5 6
|
1<(2 3) 4 5 6
or
2<(1 3) 4 5 6
or
3<(1 2) 4 5 6
[1, 2, 3, 4, 5, 6]
[1, 2, 3, 4, 5, 6]

1 5 2 6 3 4
[1, 2, 3, 4, 5, 6]
3 1 4 2 5 6

T if i < j
< i 1 2 3 4 5 6
j
1 / X X X X X X
2 / < X X X X X
3 / < X X X X X
4 / X X X X X X
5 / X X X X X X
6 / X X X X X X

So this is the state so far
We can count the number of permutations
satisfying this
If it's more than 729 / 3^num_queries_so_far, then oof
3^(6 - num_queries_so_far)
=====
Let me rethink the state
Yeah this should work ^^
*/

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef ll inf_grid;

bool inf_at(inf_grid grid, int i, int j) {
    return ((grid >> (i * 6 + j)) & 1) == 1;
}

inf_grid set_at(inf_grid grid, int i, int j, bool nv) {
    return (nv ? grid | (1 << (i * 6 + j)) : grid & (~(1 << (i * 6 + j))));
}

inf_grid set_lightest(inf_grid grid, const int& winner, const tuple<int, int, int>& q) {
   inf_grid res_grid = grid;
   res_grid = set_at(res_grid, winner, get<0>(q), true);
   res_grid = set_at(res_grid, winner, get<1>(q), true);
   res_grid = set_at(res_grid, winner, get<2>(q), true);
   res_grid = set_at(res_grid, winner, winner, false);
   return res_grid;
}

inf_grid set_heaviest(inf_grid grid, const int& winner, const tuple<int, int, int>& q) {
   inf_grid res_grid = grid;
   res_grid = set_at(res_grid, get<0>(q), winner, true);
   res_grid = set_at(res_grid, get<1>(q), winner, true);
   res_grid = set_at(res_grid, get<2>(q), winner, true);
   res_grid = set_at(res_grid, winner, winner, false);
   return res_grid;
}

bool perm_satisfies(inf_grid info, const vector<int>& perm) {
    for(int i = 0; i < 6; i++) {
        for(int j = 0; j < 6; j++) {
            if(inf_at(info, i, j) && perm[i] >= perm[j]) return false;
        }
    }
    return true;
}
    
vector<int> perm_iterator = {0, 1, 2, 3, 4, 5};
int count_satisfying_perms(inf_grid info) {
    int count = 0;
    for(int i = 0; i < 720; i++) {
        if(perm_satisfies(info, perm_iterator)) count++;
        next_permutation(perm_iterator.begin(), perm_iterator.end());
    }

    return count;
}

vector<int> get_satisfying_perm(inf_grid info) {
    sort(perm_iterator.begin(), perm_iterator.end());
    for(int i = 0; i < 720; i++) {
        if(perm_satisfies(info, perm_iterator)) return perm_iterator;
        next_permutation(perm_iterator.begin(), perm_iterator.end());
    }
    return {-1};
}

int powint(int base, int p) {
    if(p == 0) return 1;
    int sqrt = powint(base, p >> 1);
    return (p & 1 ? base : 1) * sqrt * sqrt;
}

// Iterate through all possible first queries
const int MAX_Q = 6;
map<inf_grid, tuple<int, int, int>> next_q;
map<inf_grid, vector<int>> ans_map;
map<ll, bool> memo;
bool gen_strat(inf_grid info, int num_q) {
    ll memo_ind = (info << 3ll) | num_q;
    if(memo.count(memo_ind) == 0) {
        int valid_perm_count = count_satisfying_perms(info);
        if((valid_perm_count == 2 && num_q <= 5) || (valid_perm_count <= 1 && num_q <= 6)) {
            memo[memo_ind] = true;
            ans_map[info] = get_satisfying_perm(info);
            return true;
        }
        if(num_q == 6) {
            memo[memo_ind] = false;
            return false;
        }
        // if(valid_perm_count > powint(3, 6 - num_q)) {
        //     memo[memo_ind] = false;
        //     return false;
        // }
        // if(num_q == 0) {
        //     next_q[info] = {0, 1, 2};
        //     gen_strat(set_lightest(info, 0, {0, 1, 2}), num_q + 1);
        //     gen_strat(set_lightest(info, 1, {0, 1, 2}), num_q + 1);
        //     gen_strat(set_lightest(info, 2, {0, 1, 2}), num_q + 1);
        //     memo[memo_ind] = true;
        //     return true;
        // }
        // if(num_q == 1) {
        //     next_q[info] = {3, 4, 5};
        //     gen_strat(set_lightest(info, 3, {3, 4, 5}), num_q + 1);
        //     gen_strat(set_lightest(info, 4, {3, 4, 5}), num_q + 1);
        //     gen_strat(set_lightest(info, 5, {3, 4, 5}), num_q + 1);
        //     memo[memo_ind] = true;
        //     return true;
        // }

        for(int i = 0; i < 4; i++) {
            for(int j = i + 1; j < 5; j++) {
                for(int k = j + 1; k < 6; k++) {
                    bool b1 = gen_strat(set_lightest(info, i, {i, j, k}), num_q + 1);
                    if(!(b1)) continue;
                    b1 = gen_strat(set_lightest(info, j, {i, j, k}), num_q + 1);
                    if(!(b1)) continue;
                    b1 = gen_strat(set_lightest(info, k, {i, j, k}), num_q + 1);
                    if(!(b1)) continue;
                    next_q[info] = {i, j, k};
                    cout << num_q << endl;
                    memo[memo_ind] = true;
                    return true;
                }
            }
        }

        

        memo[memo_ind] = false;
        return false;
    }
    return memo[(info << 3ll) | num_q];
}

int getLightest(const tuple<int, int, int>& args) {
    auto [a, b, c] = args;
    std::cout << "getLightest " << a + 1 << " " << b + 1 << " " << c + 1 << endl;
    int res;
    std::cin >> res;

    return res - 1;
}

int getMedian(const tuple<int, int, int>& args) {
    auto [a, b, c] = args;
    std::cout << "getMedian " << a + 1 << " " << b + 1 << " " << c + 1 << endl;
    int res;
    std::cin >> res;

    return res - 1;
}

int getHeaviest(const tuple<int, int, int>& args) {
    auto [a, b, c] = args;
    std::cout << "getHeaviest " << a + 1 << " " << b + 1 << " " << c + 1 << endl;
    int res;
    std::cin >> res;

    return res - 1;
}

int answer(const vector<int>& ans) {
    std::cout << "answer";
    for(int v: ans) {
        std::cout << " " << v + 1;
    }
    std::cout << endl;
    int res;
    cin >> res;

    return res;
}

int main() {
    // std::cout << std::bitset<36>(set_lightest(0ll, 0, {0, 1, 2})) << endl;
    // std::cout << std::bitset<36>(set_lightest(0ll, 1, {0, 1, 2})) << endl;
    // std::cout << std::bitset<36>(set_lightest(0ll, 2, {0, 1, 2})) << endl;
    gen_strat(0ll, 0);
    map<inf_grid, tuple<int, int, int>> qmap = next_q;
    std::cout << "Done!" << endl;
    int t;
    cin >> t;
    while(t--) {
        inf_grid info = 0ll;
        while(true) {
            std::cout << bitset<36>(info) << " " << info << endl;
            if(ans_map.count(info) > 0) {
                int res = answer(ans_map[info]);
                if(res == 0) return 0;
                continue;
            }
            tuple<int, int, int> query = next_q[info];
            info = set_lightest(info,  getLightest(query), query);
        }
    }
}