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

ll mod = 998244353;
const int MAXN = 2e5;

ll step(ll n, ll cnt) {
    if(cnt == 0) {
        return 1;
    } else if(cnt % 2 == 0) {
        ll a = step(n, cnt/2);
        return (a * a) % mod;
    } else {
        return (step(n, cnt - 1) * n) % mod;
    }
}

int main() {
    vector<ll> f(MAXN + 1);
    vector<ll> f_dop(MAXN + 1);
    f[0] = 1;
    for(int i = 1; i <= MAXN; i++) {
        f[i] = f[i - 1] * i;
        f[i] %= mod;
    }

    f_dop[MAXN] = step(f[MAXN], mod - 2);
    f_dop[0] = 1;
    for(int i = MAXN - 1; i >= 1; i--) {
        f_dop[i] = f_dop[i + 1] * (i + 1);
        f_dop[i] %= mod;
    }

    int tt;
    cin >> tt;
    while(tt--) {
        ll n, s;
        cin >> n >> s;

        if(n > s) {
            cout << 0 << "\n";
        } else {
            ll a = (f[s] * f_dop[s - n]) % mod;
            a *= s + 1;
            a %= mod;
            if(s == n) {
                cout << a << "\n";
            } else {
                ll b = (f[s - 1] * f_dop[s - n - 1]) % mod;
                b *= s;
                b %= mod;
                cout << (a - b + mod) % mod << "\n";
            }
        }
    }

    return 0;
}
