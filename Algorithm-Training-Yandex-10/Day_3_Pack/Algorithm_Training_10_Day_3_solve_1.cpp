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
    int n, m;
    cin >> n >> m;
    vector<vector<char>> vv(n, vector<char>(m));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cin >> vv[i][j];
        }
    }

    vector<vector<int>> res1(n);
    vector<vector<int>> res2(m);
    for(int i = 0; i < n; i++) {
        vv[i].push_back('.');
        int cnt = 0;
        for(int j = 0; j <= m; j++) {
            if(vv[i][j] == '#') {
                cnt++;
            } else {
                if(cnt != 0) {
                    res1[i].push_back(cnt);
                }
                cnt = 0;
            }
        }
        vv[i].pop_back();
    }

    vector<char> v(m);
    for(int i = 0; i < m; i++) {
        v[i] = '.';
    }
    vv.push_back(v);

    for(int j = 0; j < m; j++) {
        int cnt = 0;
        for(int i = 0; i <= n; i++) {
            if(vv[i][j] == '#') {
                cnt++;
            } else {
                if(cnt != 0) {
                    res2[j].push_back(cnt);
                }
                cnt = 0;
            }
        }
    }

    for(int i = 0; i < res1.size(); i++) {
        cout << res1[i].size() << " ";
        for(auto &it : res1[i]) {
            cout << it << " ";
        }
        cout << "\n";
    }

    cout << "\n";
    for(int i = 0; i < res2.size(); i++) {
        cout << res2[i].size() << " ";
        for(auto &it : res2[i]) {
            cout << it << " ";
        }
        cout << "\n";
    }

    return 0;
}
