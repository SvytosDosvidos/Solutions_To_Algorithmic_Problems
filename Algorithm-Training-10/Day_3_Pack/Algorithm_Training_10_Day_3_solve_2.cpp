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

    int n;
    cin >> n;
    deque<pair<string, int>> vp;
    for(int i = 0; i < n; i++) {
        string s;
        int a;
        cin >> s >> a;
        vp.push_back({s, a});
    }

    int m;
    cin >> m;
    deque<pair<int, pair<string, int>>> vpp;
    for(int i = 0; i < m; i++) {
        string s;
        int a, b;
        cin >> a >> s >> b;
        vpp.push_back({a, {s, b}});
    }

    ll t = 0;
    while(vp.size() + vpp.size() > 0) {
        if(!vp.empty()) {
            for(auto &it : vpp) {
                    if(it.first <= t) {
                        vp.push_front(it.second);
                    } else {
                        break;
                    }
                }

                for(auto &it : vpp) {
                    if(it.first <= t) {
                        vpp.pop_front();
                    } else {
                        break;
                    }
                }

                cout << vp.front().first << " " << t << "\n";
            t += vp.front().second;
            vp.pop_front();
        } else if(!vpp.empty()) {
            vp.push_back(vpp.front().second);
            t = max(t, (ll)vpp.front().first);
            vpp.pop_front();
        }
    }

    return 0;
}
