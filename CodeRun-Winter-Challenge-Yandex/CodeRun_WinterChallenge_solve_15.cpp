#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <queue>
#include <map>
#include <set>
#include <random>
#include <stack>
#include <cmath>

using namespace std;
using ll = long long;
using ld = long double;

const int mod = 998244353;
const int max_n = 3e3 + 5;

vector<vector<int>> v_new;
vector<vector<int>> prefix;

void dop_solve() {
    v_new.assign(max_n, vector<int>(max_n, 0));
    prefix.assign(max_n, vector<int>(max_n, 0));

    v_new[0][0] = 1;
    for(int n = 1; n < max_n; n++) {
        for(int k = 1; k <= n; k++) {
            v_new[n][k] = (v_new[n - 1][k - 1] + ((1LL * (n - 1) * 1LL * v_new[n - 1][k]) % mod)) % mod;
        }
    }

    for(int n = 0; n < max_n; n++) {
        prefix[n][0] = v_new[n][0];
        for(int k = 1; k <= n; k++) {
            prefix[n][k] = (prefix[n][k - 1] + v_new[n][k]) % mod;
        }
    }
}

struct dsu {
    vector<int> v;
    vector<int> sizes;

    dsu(int n) {
        v.resize(n);
        sizes.resize(n);
        for(int i = 0; i < n; i++) {
            v[i] = i;
            sizes[i] = 1;
        }
    }

    int get(int x) {
        if(v[x] != x) {
            v[x] = get(v[x]);
        }
        return v[x];
    }

    bool join(int x, int y) {
        x = get(x);
        y = get(y);
        if(x == y) {
            return false;
        }

        if(sizes[x] < sizes[y]) {
            swap(x, y);
        }
        v[y] = x;
        sizes[x] += sizes[y];
        return true;
    }
};

bool diff(const vector<int>& v) {
    vector<bool> flag(max_n, false);
    for(int x : v) {
        if(flag[x]) {
            return false;
        }
        flag[x] = true;
    }
    return true;
}

int find_res() {
    int n, q, l, r;
    cin >> n >> q >> l >> r;

    vector<int> b(q);
    vector<int> c(q);
    for(int i = 0; i < q; i++) {
        cin >> b[i];
    }

    for(int i = 0; i < q; i++) {
        cin >> c[i];
    }

    if(!diff(b) || !diff(c)) {
        return 0;
    }

    vector<int> a(n + 1, 0);
    vector<int> in(n + 1, 0);
    vector<int> out(n + 1, 0);

    for(int i = 0; i < q; i++) {
        int u = b[i];
        int v = c[i];

        if(a[u] != 0 || in[v] != 0) {
            return 0;
        }

        a[u] = v;
        out[u] = 1;
        in[v] = 1;
    }

    dsu d(n + 1);
    for(int i = 1; i <= n; i++) {
        if(a[i] != 0) {
            d.join(i, a[i]);
        }
    }

    vector<vector<int>> comps(n + 1);
    for(int i = 1; i <= n; i++) {
        comps[d.get(i)].push_back(i);
    }

    vector<int> edgeCount(n + 1, 0);
    for(int i = 1; i <= n; i++) {
        if(a[i] != 0) {
            edgeCount[d.get(i)]++;
        }
    }

    int closed = 0;
    int open = 0;

    for(int i = 1; i <= n; i++) {
        if(d.get(i) == i && !comps[i].empty()) {
            int v_cnt = comps[i].size();
            int e_cnt = edgeCount[i];

            if(e_cnt == v_cnt) {
                closed++;
            } else if(e_cnt < v_cnt) {
                open++;
            }
        }
    }

    int minCycles = closed;
    int maxCycles = closed + open;

    int new_l = max(l, minCycles);
    int new_r = min(r, maxCycles);

    if(new_l > new_r) {
        return 0;
    }

    int needMin = new_l - closed;
    int needMax = new_r - closed;

    needMin = max(needMin, 0);
    needMax = min(open, needMax);
    if(needMin > needMax) {
        return 0;
    }

    ll res = prefix[open][needMax];
    if(needMin > 0) {
        res = (res - prefix[open][needMin - 1] + mod) % mod;
    }

    return res;
}

/*
4
3 2 0 3
1 1
2 2
3 3 0 3
1 2 2
3 2 1
3 3 0 3
3 2 1
2 2 1
5 2 3 4
3 4
4 3

0
0
0
4



4
3 1 0 2
1
2
3 1 2 2
3
1
4 3 0 4
1 2 3
2 1 1
20 5 4 17
4 5 6 12 13
5 6 4 13 14

2
1
0
677226326
*/

int main() {
    dop_solve();

    int tt;
    cin >> tt;

    while(tt--) {
        cout << find_res() << '\n';
    }

    return 0;
}
