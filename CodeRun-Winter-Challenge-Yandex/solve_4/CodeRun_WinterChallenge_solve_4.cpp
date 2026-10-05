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

const int max_n = 1e8;

struct dsu
{
    vector<int> v;
    vector<int> sizes;
    void build(int n) {
        v.resize(n);
        sizes.resize(n, 1);
        for(int i = 0; i < n; i++) {
            v[i] = i;
        }
    }

    int get(int a) {
        if(v[a] == a) {
            return a;
        }
        return v[a] = get(v[a]);
    }

    void join(int a, int b) {
        a = get(a);
        b = get(b);
        if(a == b) {
            return;
        }
        if(sizes[b] > sizes[a]) {
            swap(a, b);
        }
        v[b] = a;
        sizes[a] += sizes[b];
    }
};

/*
5
13 -16 -16
10 -16 -16
9 -5 -2
18 -5 18
-2 -2 -6
*/

int main() {
    int n;
    cin >> n;

    vector<vector<ll>> vv(n, vector<ll>(3));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < 3; j++) {
            cin >> vv[i][j];
        }
    }

    vector<pair<ll, ll>> vp_x(n);
    vector<pair<ll, ll>> vp_y(n);
    vector<pair<ll, ll>> vp_z(n);

    vector<ll> v_x(n);
    vector<ll> v_y(n);
    vector<ll> v_z(n);

    for(int i = 0; i < n; i++) {
        vp_x[i] = {vv[i][0], i};
        vp_y[i] = {vv[i][1], i};
        vp_z[i] = {vv[i][2], i};

        v_x[i] = vv[i][0];
        v_y[i] = vv[i][1];
        v_z[i] = vv[i][2];
    }

    sort(vp_x.begin(), vp_x.end());
    sort(vp_y.begin(), vp_y.end());
    sort(vp_z.begin(), vp_z.end());

    set<pair<int, int>> s;
    for(int i = 0; i < n - 1; i++) {
        s.insert({min(vp_x[i].second, vp_x[i + 1].second), max(vp_x[i].second, vp_x[i + 1].second)});
        s.insert({min(vp_y[i].second, vp_y[i + 1].second), max(vp_y[i].second, vp_y[i + 1].second)});
        s.insert({min(vp_z[i].second, vp_z[i + 1].second), max(vp_z[i].second, vp_z[i + 1].second)});
    }

    vector<pair<ll, pair<int, int>>> vv_new;
    for(auto &it : s) {
        int a = it.first;
        int b = it.second;
        ll l = min(abs(v_x[a] - v_x[b]), min(abs(v_y[a] - v_y[b]), abs(v_z[a] - v_z[b])));
        vv_new.push_back({l, {a, b}});
    }

    dsu d;
    d.build(n);
    ll res = 0;
    sort(vv_new.begin(), vv_new.end());
    for(int i = 0; i < vv_new.size(); i++) {
        int a = vv_new[i].second.first, b = vv_new[i].second.second;
        if(d.get(a) != d.get(b)) {
            d.join(a, b);
            res += vv_new[i].first;
        }
    }

    cout << res << "\n";

    return 0;
}
