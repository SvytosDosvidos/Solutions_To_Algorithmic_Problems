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

int main() {

    int n, m;
    cin >> n >> m;

    vector<pair<int, int>> vp(n);
    vector<int> v_x(n);
    vector<int> v_y(n);
    ll res_x = 0, res_y = 0;
    map<int, int> map_x;
    map<int, int> map_y;
    for(int i = 0; i < n; i++) {
        cin >> vp[i].first >> vp[i].second;
        v_x[i] = vp[i].first;
        v_y[i] = vp[i].second;
        res_x += abs(v_x[i]);
        res_y += abs(v_y[i]);
        map_x[v_x[i]]++;
        map_y[v_y[i]]++;
    }

    sort(v_x.begin(), v_x.end());
    sort(v_y.begin(), v_y.end());
    string s;
    cin >> s;

    int x = 0, y = 0;
    for(int i = 0; i < m; i++) {
        if(s[i] == 'N' || s[i] == 'S') {
            int l = 0, r = n;
            while(r > l + 1) {
                int mid = (l + r)/2;
                if(v_y[mid] > y) {
                    r = mid;
                } else {
                    l = mid;
                }
            }
            if(v_y[0] > y) {
                l = -1;
            }
            l++;

            if(s[i] == 'N') {
                res_y += l - (n - l);
            } else {
                res_y += (n - l) - l + 2 * map_y[y];
            }
        } else {
            int l = 0, r = n;
            while(r > l + 1) {
                int mid = (l + r)/2;
                if(v_x[mid] > x) {
                    r = mid;
                } else {
                    l = mid;
                }
            }

            if(v_x[0] > x) {
                l = -1;
            }
            l++;

            if(s[i] == 'E') {
                res_y += l - (n - l);
            } else {
                res_y += (n - l) - l + 2 * map_x[x];
            }
        }

        if(s[i] == 'N') {
            y++;
        } else if(s[i] == 'S') {
            y--;
        } else if(s[i] == 'W') {
            x--;
        } else {
            x++;
        }

        cout << res_x + res_y << "\n";
    }

    return 0;
}
