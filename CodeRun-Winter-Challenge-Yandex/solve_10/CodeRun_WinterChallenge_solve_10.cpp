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

ll find_step(ll a, ll cnt) {
    if(cnt == 0) {
        return 1;
    } else if(cnt % 2 == 0) {
        ll d = find_step(a, cnt/2);
        return (d * d) % mod;
    } else {
        return (find_step(a, cnt - 1) * a) % mod;
    }
}

/*
2
4

4
333333357
*/

int main() {
    ll n;
    cin >> n;

    vector<ll> v(n + 1);
    v[1] = 1;
    for(int i = 2; i <= n; i++) {
        v[i] = mod - (mod / i) * v[mod % i] % mod;
    }

    ll e = 0, e_dop = 1;
    ll d = 1, d_dop = 1;

    for(ll k = n - 1; k >= 1; k--) {
        ll new_d = ((n - k) * d + n % mod * d_dop) % mod;
        ll new_d_dop = (k * d_dop) % mod;
        d = new_d;
        d_dop = new_d_dop;

        e = (e * d_dop + d * e_dop) % mod;
        e_dop = (e_dop * d_dop) % mod;
    }

    e = (e + e_dop) % mod;
    ll res = e * find_step(e_dop, mod - 2) % mod;
    cout << res << "\n";

    return 0;
}
