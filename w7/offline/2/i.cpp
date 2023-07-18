#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int getLightest(int ia, int ib, int ic) {
    cout << "getLightest " << ia << " " << ib << " " << ic << endl;
    int res;
    cin >> res;
    return res;
}

int getMedian(int ia, int ib, int ic) {
    cout << "getMedian " << ia << " " << ib << " " << ic << endl;
    int res;
    cin >> res;
    return res;
}

int getHeaviest(int ia, int ib, int ic) {
    cout << "getHeaviest " << ia << " " << ib << " " << ic << endl;
    int res;
    cin >> res;
    return res;
}

int getNextLightest(int ia, int ib, int ic, int id) {
    cout << "getNextLightest " << ia << " " << ib << " " << ic << " " << id << endl;
    int res;
    cin >> res;
    return res;
}

vector<int> order_three(tuple<int, int, int> nums) {
    int light1 = getLightest(get<0>(nums), get<1>(nums), get<2>(nums));
    int median1 = getMedian(get<0>(nums), get<1>(nums), get<2>(nums));
    set<int> poss_heavy_1 = {get<0>(nums), get<1>(nums), get<2>(nums)};
    poss_heavy_1.erase(light1);
    poss_heavy_1.erase(median1);
    int heavy1 = *poss_heavy_1.begin();

    return {light1, median1, heavy1};
}

bool is_less(int a, int b, int c) {
    int lightest = getLightest(a, b, c);

    return lightest == a;
}
bool is_greater(int a, int b, int c) {
    int heaviest = getHeaviest(a, b, c);

    return heaviest == a;
}

int answer(vector<int> ans) {
    cout << "answer";

    for(int v : ans) {
        cout << " " << v;
    }

    cout << endl;

    int res;
    cin >> res;
    return res;
}

int main() {
    int t;
    cin >> t;
    while(t--) {
        vector<int> ord1 = order_three({1, 2, 3});
        vector<int> ord2 = order_three({4, 5, 6});
        int i1 = 0, i2 = 0;
        vector<int> sorted;

        while(3 - i1 > 0 && 3 - i2 > 0 && 6 - i1 - i2 > 2) {
            if(is_less(ord1[i1], ord2[i2], (3 - i1 >= 2 ? ord1[i1 + 1] : ord2[i2 + 1]))) {
                sorted.push_back(ord1[i1]);
                i1++;
            } else {
                sorted.push_back(ord2[i2]);
                i2++;
            }
        }

        if(3 - i1 == 1 && 3 - i2 == 1) {
            if(is_greater(ord1[i1], ord2[i2], ord1[0])) {
                sorted.push_back(ord2[i2]);
                sorted.push_back(ord1[i1]);
            } else {
                sorted.push_back(ord1[i1]);
                sorted.push_back(ord2[i2]);
            }
            i1++; i2++;
        }

        while(3 - i1 > 0) {
            sorted.push_back(ord1[i1]);
            i1++;
        }

        while(3 - i2 > 0) {
            sorted.push_back(ord2[i2]);
            i2++;
        }

        int res = answer(sorted);

        if(res == 0) {
            break;
        }
    }

    return 0;
}