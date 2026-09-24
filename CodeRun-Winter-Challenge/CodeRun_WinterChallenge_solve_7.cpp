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

const int MAX_n = 700000;
const int MAX_k = 8;
const int INF = 1e9;

int main() {
    ll start = 1;
    vector<vector<int>> vv(MAX_k, vector<int>(MAX_n + 1, INF));
    for(int i = 2; i <= MAX_n; i++) {
        vv[0][i] = i;
    }

    vector<vector<int>> dels(MAX_n + 1);
    for(int i = 2; i <= MAX_n; i++) {
        for(int j = 2; j * j <= i; j++) {
            if(i % j == 0) {
                if(j * j != i) {
                    dels[i].push_back(i/j);
                }
                dels[i].push_back(j);
            }
        }
    }

    for(int ind = 1; ind < MAX_k; ind++) {
        for(int i = 2; i <= MAX_n; i++) {
            for(int j = 0; j < dels[i].size(); j++) {
                int num = dels[i][j];
                if(vv[ind - 1][i/num] == INF || vv[ind - 1][i/num] >= dels[i][j]) {
                    continue;
                }
                vv[ind][i] = min(vv[ind][i], dels[i][j]);
            }
        }
    }

    vector<vector<int>> vv_res(MAX_k + 1, vector<int>(MAX_n + 1));
    for(int ind = 0; ind < MAX_k; ind++) {
        for(int j = 2; j <= MAX_n; j++) {
            if(vv[ind][j] != INF) {
                vv_res[ind][j] = 1;
            }
            vv_res[ind][j] += vv_res[ind][j - 1];
        }
    }


    int q;
    cin >> q;
    while(q--) {
        int k, l, r;
        cin >> k >> l >> r;
        k--;
        if(k >= 8) {
            cout << 0 << "\n";
        } else {
            cout << vv_res[k][r] - vv_res[k][l - 1] << '\n';
        }
    }

    return 0;
}
