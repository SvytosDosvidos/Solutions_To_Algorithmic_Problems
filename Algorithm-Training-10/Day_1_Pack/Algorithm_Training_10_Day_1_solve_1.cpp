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

    int tt;
    cin >> tt;
    while(tt--) {
        string s;
        cin >> s;

        string t;
        for(int i = 0; i < s.size(); i++) {
            if(i == 0) {
                t.push_back(tolower(s[i]));
            } else if(isupper(s[i])) {
                t.push_back('_');
                t.push_back(tolower(s[i]));
            } else {
                t.push_back(s[i]);
            }
        }

        cout << t << "\n";
    }

    return 0;
}
