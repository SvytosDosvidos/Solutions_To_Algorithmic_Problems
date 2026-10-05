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

const ll inf = 1e18;

struct object {
    struct edge {
        ll u, rev, cap, w_p;
    };

    vector<vector<edge>> g;
    vector<ll> dist, pot;
    vector<int> prevv, preve;
    int n;

    object(int n) : n(n), g(n), dist(n), pot(n), prevv(n), preve(n) {}

    void add(int v, int u, ll cap, ll w_p) {
        g[v].push_back({u, (int)g[u].size(), cap, w_p});
        g[u].push_back({v, (int)g[v].size() - 1, 0, -w_p});
    }

    ll find_min(int s, int t, ll f) {
        ll res = 0;
        //fill(pot.begin(), pot.end(), 0);

        while(f > 0) {
            fill(dist.begin(), dist.end(), inf);
            dist[s] = 0;
            priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
            pq.push({0, s});

            while(!pq.empty()) {
                auto [d, v] = pq.top();
                pq.pop();
                if(dist[v] < d) {
                    continue;
                }

                for(int i = 0; i < (int)g[v].size(); i++) {
                    edge &e = g[v][i];
                    if (e.cap > 0 && dist[e.u] > d + e.w_p + pot[v] - pot[e.u]) {
                        dist[e.u] = d + e.w_p + pot[v] - pot[e.u];
                        prevv[e.u] = v;
                        preve[e.u] = i;
                        pq.push({dist[e.u], e.u});
                    }
                }
            }

            if (dist[t] == inf) {
                return -1;
            }

            for(int v = 0; v < n; v++) {
                if(dist[v] < inf) {
                    pot[v] += dist[v];
                }
            }

            ll d = f;
            for(int v = t; v != s; v = prevv[v]) {
                d = min(d, g[prevv[v]][preve[v]].cap);
            }

            f -= d;
            res += d * pot[t];

            for(int v = t; v != s; v = prevv[v]) {
                edge &e = g[prevv[v]][preve[v]];
                e.cap -= d;
                g[v][e.rev].cap += d;
            }
        }

        return res;
    }
};

void find_res() {
    int n, m;
    cin >> n >> m;

    vector<ll> a(n);
    vector<ll> b(m);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for(int i = 0; i < m; i++) {
        cin >> b[i];
    }

    int q = n / m;
    int r = n % m;

    int a_num = 0;
    int b_num = 1;
    int elem_start = 2;
    int group_start = elem_start + n;
    int cent_node = group_start + m;
    int cnt = cent_node + 1;

    object obj(cnt);

    for(int j = 0; j < n; j++) {
        obj.add(a_num, elem_start + j, 1, 0);
    }

    for(int j = 0; j < n; j++) {
        for(int i = 0; i < m; i++) {
            ll w = (b[i] - (a[j] % b[i])) % b[i];
            obj.add(elem_start + j, group_start + i, 1, w);
        }
    }

    for(int i = 0; i < m; i++) {
        obj.add(group_start + i, cent_node, 1, 0);
    }

    for(int i = 0; i < m; i++) {
        obj.add(group_start + i, b_num, q, 0);
    }

    obj.add(cent_node, b_num, r, 0);

    ll res = obj.find_min(a_num, b_num, n);
    cout << res << "\n";
}

/*
4
2 2
3 13
5 7
1 1
3
2
4 2
3 11 13 15
5 7
4 3
3 11 13 15
5 6 7

1
2 2
3 13

1
3 11 13 15
5 6 7

3
1
6
4
*/

int main() {
    int tt;
    cin >> tt;

    while(tt--) {
        find_res();
    }

    return 0;
}
