#include<iostream>
#include<vector>
#include<string>
#include<cstring>
#include<set>
#include<map>
#include<math.h>
#include<queue>
#include<cctype>
#include<algorithm>
#include<unordered_map>

using namespace std;

using ull = unsigned long long;
using ll = long long;
using ld = long double;

int main() {
    ll n, k;
    cin >> n >> k;

    map<ll, ll> m;
    for(int i = 0; i < n; i++) {
        ll x;
        cin >> x;
        m[x]++;
    }

    ll res = 0;

    for(auto &it : m) {
        if(it.first * 2 == k) {
            res += it.second - 1;
        }
        else if(it.first * 2 < k) {
            ll num = k - it.first;
            if (m.find(num) != m.end()) {
                res += min(it.second, m[num]);
            }
        }
    }

    cout << res << "\n";

    return 0;
}
