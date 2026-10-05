#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <queue>
#include <map>
#include <set>
#include <random>
#include <cmath>

using namespace std;
using ll = long long;
using ld = long double;

//const long long mod = 1e9 + 7;
const ll mod = 998244353;
const int max_bit = 20;

ll find_step(ll n, ll cnt) {
    if(cnt == 0) {
        return 1;
    } else if(cnt % 2 == 0) {
        ll a = find_step(n, cnt/2);
        return (a * a) % mod;
    } else {
        return (find_step(n, cnt - 1) * n) % mod;
    }
}

ll dfs(int i, int len, int m, vector<vector<ll>> &dp, vector<vector<ll>> &lcp, string &s, string &t, vector<ll> &pow2) {
    if(len == 0) {
        return m - i;
    }
    if(i >= m) {
        return 0;
    }

    if(dp[i][len] != -1) {
        return dp[i][len];
    }

    int res = 0;

    for(int block_len = 1; block_len <= len; block_len++) {
        int s_start = len - block_len;

        int common = lcp[s_start][i];

        if(common >= block_len) {
            res += dfs(i + block_len, len - block_len, m, dp, lcp, s, t, pow2);
            res %= mod;
        } else {
            int t_pos = i + common;
            int s_pos = s_start + common;

            if(t_pos >= m) {
                continue;
            }

            if(s_pos >= len) {
                res += m - t_pos;
                res %= mod;
                continue;
            }

            if(s[s_pos] > t[t_pos]) {
                continue;
            }

            ll cnt_t = m - t_pos;
            ll cnt_s = m - t_pos;
            if(len == block_len) {
                cnt_s = 1;
            } else {
                cnt_s = pow2[len - block_len - 1];
            }

            res += (cnt_s * cnt_t) % mod;
            res %= mod;
        }
    }

    return dp[i][len] = res;
}

void f() {
    string s, t;
    cin >> s >> t;

    int n = s.size();
    int m = t.size();

    vector<ll> pow2(n + 1, 1);
    for(int i = 1; i <= n; i++) {
        pow2[i] = 2 * pow2[i - 1];
        pow2[i] %= mod;
    }

    vector<vector<ll>> lcp(n + 1, vector<ll>(m + 1));
    for(int i = n - 1; i >= 0; i--) {
        for(int j = m - 1; j >= 0; j--) {
            if(s[i] == t[j]) {
                lcp[i][j] = 1 + lcp[i + 1][j + 1];
            }
        }
    }

    vector<vector<ll>> dp(m + 1, vector<ll>(n + 1, -1));

    ll res = 0;
    for(int i = 0; i < m; i++) {
        res += dfs(i, n, m, dp, lcp, s, t, pow2);
        res %= mod;
    }

    cout << res << "\n";
}

int main() {
    int tt;
    cin >> tt;
    while(tt--) {
        f();
    }

    return 0;
}
