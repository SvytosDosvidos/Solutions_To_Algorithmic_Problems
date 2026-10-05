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

int main() {

    string s;
    cin >> s;
    map<int, int> mapf;
    for(int i = 0; i < s.size(); i++) {
        mapf[s[i]]++;
    }

    bool flag = true;
    int dop = 0;
    for(int i = 0; i < 26; i++) {
        if(mapf['a' + i] % 2 == 0) {
            dop += mapf['a' + i];
        } else {
            flag = false;
        }
    }


    int cnt = mapf['>'];
    if(flag && cnt == mapf['<'] && cnt == 2 * mapf['/'] && dop >= cnt) {
        if(cnt == 0) {
            if(dop == 0) {
                cout << "\n";
            } else {
                cout << "Impossible\n";
            }
            return 0;
        }
        cnt/=2;
        vector<string> vn(cnt);
        for(int i = 0; i < cnt; i++) {
            string t;
            for(int j = 0; j < 26; j++) {
                if(mapf['a' + j] > 0) {
                    mapf['a' + j] -= 2;
                    t.push_back('a' + j);
                    break;
                }
            }
            vn[i] = t;
        }

        for(int j = 0; j < 26; j++) {
            while(mapf['a' + j] > 0) {
                mapf['a' + j] -= 2;
                vn[0].push_back('a' + j);
            }
        }


        for(int i = 0; i < vn.size(); i++) {
            string snew = vn[i];
            snew = "<" + snew + ">";
            string snew1 = vn[i];
            snew1 = "</" + snew1 + ">";

            cout << snew + snew1;

        }
        cout << "\n";
    } else {
        cout << "Impossible\n";
    }

    return 0;
}
