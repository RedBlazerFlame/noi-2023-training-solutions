#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<vector<char>> char_grid;

char_grid make_grid(int w, int h) {
    char_grid res;

    for(int i = 0; i < h; i++) {
        vector<char> row(w, '.');
        res.push_back(row);
    }

    return res;
}

char_grid from_str(string s) {
    char_grid res;
    for(const char& c: s) {
        if(c == '\n') {
            vector<char> row;
            res.push_back(row);
        } else {
            res[res.size() - 1].push_back(c);
        }
    }

    return res;
}

void print_grid(const char_grid& g) {
    for(const auto& row : g) {
        for(const char& c : row) {
            cout << c;
        }
        cout << endl;
    }
}

char_grid rotate(const char_grid& vec) {
    int h = vec.size(), w = vec[0].size();

    char_grid res;

    for(int i = 0; i < w; i++) {
        vector<char> row;
        for(int j = 0; j < h; j++) {
            row.push_back(vec[j][i]);
        }
        res.push_back(row);
    }

    return res;
}

char_grid generate_ans(int w, int h) {
    if(w < h) {
        return rotate(generate_ans(h, w));
    }

    char_grid grid = make_grid(w, h);
    
    if(h == 3) {
        for(int i = 0; i < w; i += 2) {
            grid[0][i] = '#';
        }

        for(int i = 0; i < w; i += 4) {
            grid[2][i] = '#';
        }
    }

    if(h == 4) {
        for(int i = 0; i < w; i += 2) {
            grid[0][i] = '#';
        }
        for(int i = 3; i < w; i += 6) {
            grid[1][i] = '#';
        }

        for(int i = 0; i < w; i += 6) {
            grid[2][i] = '#';
        }

        for(int i = 1; i < w; i += 2) {
            grid[3][i] = '#';
        }
    }

    if(h == 5) {
        for(int i = 0; i < w; i+= 2) {
            grid[0][i] = '#';
            grid[4][i] = '#';
        }

        for(int i = 0; i < w; i += 4) {
            grid[2][i] = '#';
        }
    }

    vector<pair<int, int>> periods;

    if(h == 6) {
        /*
        #-#-#-#
        ---#---
        #-----#
        -#-#-#-
        -------
        -#---#-
        0, 2
        3, 6
        0, 6
        1, 2
        100, 1
        1, 4
        */

        periods = {
            { 0, 2 },
            { 3, 6 },
            { 0, 6 },
            { 1, 2 },
            { 100, 1 },
            { 1, 4 }
        };
    }

    for(int i = 0; i < periods.size(); i++) {
        auto [start, period] = periods[i];
        for(int j = start; j < w; j += period) {
            grid[i][j] = '#';
        }
    }

    return grid;
}

int main() {
    int h, w;
    cin >> h >> w;

    print_grid(generate_ans(w, h));

    return 0;
}