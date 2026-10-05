#include<iostream>
#include<vector>
#include<string>
#include<set>
#include<map>
#include<math.h>
#include<cctype>
#include<algorithm>
#include<unordered_map>

using namespace std;

using ll = long long;
using ld = long double;

void f() {

}

void solution() {

}

int main() {
    string s;
    string t;
    cin >> s >> t;

    map<int, int> mapT;
    for(auto &it : t) {
        mapT[it]++;
    }

    ll res = 0;
    ll r = 0;
    ll r1 = -1;
    for(ll i = 0; i < s.size(); i++) {
        while(r < s.size()) {
            if(mapT[s[r]] > 0) {
                mapT[s[r]]--;
            } else {
                break;
            }
            r++;
        }

        if(r > 0) {
            res += (r - i) * (r - i + 1)/2;
            if(r1 >= i) {
                res -= (r1 - i) * (r1 - i + 1)/2;
            }
            r1 = r;
        }

        mapT[s[i]]++;
    }

    cout << res << "\n";

    return 0;
}
