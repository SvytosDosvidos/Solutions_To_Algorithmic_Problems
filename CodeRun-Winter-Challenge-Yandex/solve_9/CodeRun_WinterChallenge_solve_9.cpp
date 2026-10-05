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

struct dsu {
    int n;
    vector<int> v;
    vector<int> sizes;
    int max_size;

    void build(int n) {
        v.resize(n + 1);
        sizes.resize(n + 1);
        max_size = 1;

        for(int i = 1; i <= n; i++) {
            v[i] = i;
            sizes[i] = 1;
        }
    }

    int get(int a) {
        if(a == v[a]) {
            return a;
        }
        return a = get(v[a]);
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
        sizes[a] += sizes[b];
        v[b] = a;

        max_size = max(max_size, sizes[a]);
    }
};

int main() {
    int tt;
    cin >> tt;
    while(tt--) {
        int n, m;
        cin >> n >> m;

        vector<pair<int, pair<int, int>>> vp(m);
        for(int i = 0; i < m; i++) {
            cin >> vp[i].second.first;
        }
        for(int i = 0; i < m; i++) {
            cin >> vp[i].second.second;
        }
        for(int i = 0; i < m; i++) {
            cin >> vp[i].first;
        }

        sort(vp.begin(), vp.end());

        vector<int> res(n + 1, 2e9);
        res[1] = 0;

        dsu d;
        d.build(n + 1);
        for(int i = 0; i < m; i++) {
            d.join(vp[i].second.first, vp[i].second.second);
            res[d.max_size] = min(res[d.max_size], vp[i].first);
        }

        int cp = -1;
        for(int i = n; i >= 1; i--) {
            if(res[i] != 2e9) {
                cp = res[i];
            } else {
                res[i] = cp;
            }
        }

        for(int i = 1; i <= n; i++) {
            cout << res[i] << " ";
        }
        cout << "\n";
    }

    return 0;
}
