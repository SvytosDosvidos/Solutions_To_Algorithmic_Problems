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

ll find_res(vector<ll> &v) {
    sort(v.begin(), v.end());

    ll sum_p = 0, sum_m = 0;
    ll cnt_p = 0, cnt_m = 0;
    ll full_s = 0;
    ll n = v.size();
    for(int i = 0; i < n; i++) {
        if(v[i] >= 0) {
            sum_p += v[i];
            cnt_p++;
        } else {
            sum_m += v[i];
            cnt_m++;
        }
        full_s += v[i];
    }

    ll min_res = 1e18;
    ll s = 0;
    for(ll i = 0; i < n; i++) {
        ll cnt = abs(i * v[i] - s) + abs(full_s - s - (n - i) * v[i]);
        min_res = min(min_res, cnt);
        s += v[i];
    }

    return min_res;
}

int main() {

    ll n, k;
    cin >> n >> k;
    vector<ll> v(n);
    for(int i = 0; i < n; i++) {
        cin >> v[i];
    }

    vector<ll> v1 = v;
    vector<ll> v2 = v;
    vector<ll> v3 = v;
    vector<ll> v4 = v;
    for(int i = 0; i < n; i++) {
        if(i % 2 == 0) {
            v1[i] -= k;
            v2[i] += k;
        } else {
            v3[i] -= k;
            v4[i] += k;
        }
    }

    cout << min(min(find_res(v1), find_res(v2)), min(find_res(v3), find_res(v4)));

    return 0;
}
