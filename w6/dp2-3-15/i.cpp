/*
This program solves exercise 3.15 in DP2

I think the complexity is:
O(base * log(n) * [log(n) + log(log[base] + log[log(n)])])
If we take base to be constant, the complexity simplifies to:
O(log^2 (n))

But I may be wrong .-.
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// Time Complexity: O(base * log^2 n)
const ll MAX_DIGITS = 18;
const ll MAX_DIGIT_SUM = 9ll * MAX_DIGITS;
ll memo[MAX_DIGITS + 2ll][MAX_DIGIT_SUM + 1ll];
ll num_equal(ll digits, ll s) {
    ll max_sum = digits * 9ll;
    if(digits == 0ll) return (s == 0ll ? 1ll : 0ll);
    if(s > max_sum) return 0ll;
    if(s < 0ll) return 0ll;
    ll& ans = memo[digits][s];
    if(ans == -1ll) {
        ans = 0ll;
        for(ll i = 0ll; i < 10ll; i++) {
            ans += num_equal(digits - 1ll, s - i);
        }
    }
    return ans;
}

// Time Complexity: O(log n)
vector<ll> base10(ll n) {
    vector<ll> digits;

    for(ll i = 0ll; i < MAX_DIGITS + 1ll; i++) {
        digits.push_back(n % 10ll);
        n /= 10ll;
    }

    return digits;
}

// Time Complexity: O(n log log n)
vector<ll> gen_primes(ll n) {
    vector<bool> isprime(n, true);
    vector<ll> primes;
    isprime[0ll] = false;
    isprime[1ll] = false;

    for(ll i = 2ll; i <= n; i++) {
        if(!isprime[i]) continue;
        ll j = 2ll;
        while(i * j <= n) {
            isprime[i * j] = false;
            j++;
        }
        primes.push_back(i);
    }

    return primes;
}

// Time complexity: O(base * log n)
ll num_nice(const vector<ll>& target_sums, const vector<ll>& digits, ll acc_digit_sum, ll num_digits) {
    // Base-case: 0 digits
    if(num_digits == 0ll) {
        // Time Complexity: O(log(n / ln n)) = O(log n - log ln n) = O(log n)
        // If the accumulated sum is prime, then return 1, else return 0.
        ll l = -1ll, r = target_sums.size();
        while(r - l > 1ll) {
            ll m = (l + r) >> 1ll;
            if(target_sums[m] >= acc_digit_sum) r = m;
            else l = m;
        }

        return (target_sums[r] == acc_digit_sum ? 1ll : 0ll);
    }

    ll cur_digit = digits[num_digits - 1ll];

    ll res = 0ll;
    
    // Time complexity of for loop: O(base)
    for(ll i = 0ll; i < cur_digit; i++) {
        ll cur_digit_sum = i + acc_digit_sum;

        for(const ll& target_sum : target_sums) {
            // This is now an O(1) operation because the results can be preprocessed
            res += num_equal(num_digits - 1ll, target_sum - cur_digit_sum);
        }
    }

    res += num_nice(target_sums, digits, acc_digit_sum + cur_digit, num_digits - 1ll);

    return res;
}

int main() {
    for(ll i = 0ll; i < MAX_DIGITS + 1ll; i++) {
        for(ll j = 0ll; j < MAX_DIGIT_SUM; j++) {
            memo[i][j] = -1ll;
        }
    }

    ll l, r;
    cin >> l >> r;

    vector<ll> primes = gen_primes(MAX_DIGIT_SUM);

    cout << num_nice(primes, base10(r), 0ll, MAX_DIGITS + 1ll) - num_nice(primes, base10(l - 1ll), 0ll, MAX_DIGITS + 1ll) << endl;

    return 0;
}

/*
Lessons:
1. The compiler is smart, it does the moving of local variables for us. In the primes function, I didn't have to wrap the return value in std::move.
2. Be careful of off-by-one errors in the "invariant-based" implementation of binary search. Make sure that the initial values of l and r are outside the range of consideration.
*/