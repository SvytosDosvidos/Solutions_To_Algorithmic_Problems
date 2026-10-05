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

ll mod = 1e9 + 7;

/*
5 2
1 5
120/(5) = 24
8 * 3 = 4 * 2

1000000000 1
1

5 5
1 2 3 4 5
*/

int main() {
    ll k, n;
    cin >> n >> k;

    vector<ll> v(k);
    for(int i = 0; i < k; i++) {
        cin >> v[i];
    }

    ll min_n = min(n, (ll)1e6);
    vector<ll> lp(min_n + 1, 0);
    vector<ll> p_cnt(min_n + 1, 0);
    vector<ll> pr;

    for(ll i = 2; i <= min_n; i++) {
        if(lp[i] == 0) {
            lp[i] = i;
            pr.push_back(i);
            ll dop = i;
            while(dop <= n) {
                p_cnt[i] += n/dop;
                dop *= i;
            }
        }

        for(int j = 0; j < (int)pr.size() && pr[j] <= lp[i] && i * pr[j] <= min_n; j++) {
            lp[i * pr[j]] = pr[j];
        }
    }

    for(int i = 0; i < k; i++) {
        while(v[i] > 1) {
            p_cnt[lp[v[i]]]--;
            v[i] /= lp[v[i]];
        }
    }

    ll res = 1;
    for(int i = 2; i <= min_n; i++) {
        p_cnt[i] %= mod;
        res *= (p_cnt[i] + 1);
        res %= mod;
    }

    cout << res << "\n";

    return 0;
}
