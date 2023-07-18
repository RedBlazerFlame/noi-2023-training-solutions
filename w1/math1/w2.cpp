#include <bits/stdc++.h>
using namespace std;

/*
Time Complexity: O(n log^2 n)
*/

vector<int> psieve(int n) {
    vector<int> biggestPrime(n + 1, 1);
    for(int i = 2; i <= n; i++) {
        if(biggestPrime[i] == 1) {
            for(int j = i; j <= n; j += i) {
                biggestPrime[j] = i;
            }
        }
    }

    return biggestPrime;
}

vector<int> factorize(int n, const vector<int>& biggestPrime) {
    vector<int> res;
    
    while(n > 1) {
        int largestPrimeDivisor = biggestPrime[n];
        res.push_back(largestPrimeDivisor);
        n /= largestPrimeDivisor;
    }

    return res;
}

string factorize_str(int n, const vector<int>& biggestPrime) {
    vector<int> factors = factorize(n, biggestPrime);
    multiset<int> factorset;
    for(int& factor : factors) {
        factorset.insert(factor);
    }

    stringstream strm;

    bool displayTimes = false;
    while(!factorset.empty()) {
        int curFactor = *factorset.begin();
        int count = factorset.count(curFactor);
        factorset.erase(factorset.begin(), next(factorset.begin(), count));
        strm << (displayTimes ? "*" : "") << curFactor << (count > 1 ? "^" : "") << (count > 1 ? to_string(count) : "");
        displayTimes = true;
    }

    return strm.str();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    int largest = 100000;

    
    vector<int> biggestPrime;
    biggestPrime = psieve(largest);
    for(int i = 2; i <= largest; i++) {
        cout << i << " = " << factorize_str(i, biggestPrime) << "\n";
    }

    return 0;
}