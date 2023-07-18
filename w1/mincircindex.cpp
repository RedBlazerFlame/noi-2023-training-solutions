#include <bits/stdc++.h>
using namespace std;

double dist(pair<double, double> a, pair<double, double> b) {
    return sqrt(pow(a.first - b.first, 2.0) + pow(a.second - b.second, 2.0));
}

bool good(const vector<pair<double, double>>& pts, double R) {
    int n = pts.size();
    vector<bool> visited(n, false);
    queue<int> q;
    q.push(0);

    int num_visit = 0;
    while(!q.empty()) {
        int cur = q.front();
        q.pop();

        if(visited[cur]) continue;
        visited[cur] = true;
        num_visit ++;

        for(int i = 0; i < n; i++) {
            if(i != cur && dist(pts[cur], pts[i]) <= 2.0 * R) {
                q.push(i);
            }
        }
    }

    return num_visit == n;
}

int main() {
    int n;
    cin >> n;
    vector<pair<double, double>> pts(n, make_pair<>(0.0, 0.0));
    for(auto& pt : pts) {
        double x, y;
        cin >> x >> y;
        pt = make_pair<>(x, y);
    }

    double l = 0, r = 65536.0, m;

    for(int i = 0; i < 50; i++) {
        m = (l + r) / 2.0;

        if(good(pts, m)) r = m;
        else l = m;
    }

    cout << r << endl;

    return 0;
}