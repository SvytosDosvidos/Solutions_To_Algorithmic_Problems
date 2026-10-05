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

const long long mod = 1e9 + 7;
const int const_max_n = 2e6 + 1;

ll inv[const_max_n];
ll h[const_max_n];

int main() {
    int m;
    cin >> m;
    vector<ll> a(m);
    ll N = 0;
    int c = -1;
    for(int i = 0; i < m; i++) {
        cin >> a[i];
        if(a[i] > 0) {
            c = i + 1;
        }
        N += a[i];
    }

    int max_n = N;
    inv[1] = 1;
    for(int i = 2; i <= max_n; i++) {
        inv[i] = mod - (mod / i) * inv[mod % i] % mod;
    }
    h[0] = 0;
    for(int i = 1; i <= max_n; i++) {
        h[i] = (h[i - 1] + inv[i]) % mod;
    }

    /*
2
2 0

2
1 1
    */

    ll a_c = a[c-1];
    ll x0 = N - a_c;

    ll S = (h[x0] + h[N - 1] - h[a_c - 1] + mod) % mod;

    ll res = (((N - 1 + mod) % mod) * S) % mod;
    res = (res * inv[2]) % mod;

    cout << res << "\n";

    return 0;
}
