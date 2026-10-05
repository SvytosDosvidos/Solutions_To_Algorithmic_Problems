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

ll f(ll n, ll m, ll mid, vector<ll>&v) {
    for(int i = 0; i < n; i++) {
        if(mid >= v[i]) {
            continue;
        }

        m -= (v[i] - mid);
    }

    return m >= 0;
}

ll mod = 1e9 + 7;

int main()
{
    ll m, n;
    cin >> m >> n;
    vector<ll> v(n);
    for(int i = 0; i < n; i++) {
        cin >> v[i];
    }

    ll l = 0, r = 2e9;
    while(r > l + 1) {
        ll mid = (l + r)/2;
        if(f(n, m, mid, v)) {
            r = mid;
        } else {
            l = mid;
        }
    }

    sort(v.begin(), v.end());

    for(int i = 0; i < n; i++) {
        if(r >= v[i]) {
            continue;
        } else {
            m -= v[i] - r;
            v[i] = r;
        }
    }

    int ind = n - 1;
    ll s = 0;
    while(m > 0) {
        v[ind]--;
        ind--;
        m--;
    }

    for(int i = 0; i < n; i++) {
        v[i] %= mod;
        s += v[i] * v[i];
        s %= mod;
    }

    cout << s << "\n";

    return 0;
}
