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

    ll a, b;
    cin >> a >> b;

    if(b > a) {
        swap(a, b);
    }

    ll cnt = 0;
    while(true) {
        cnt += a/b;
        a %= b;
        if(a == 0) {
            break;
        }
        swap(a, b);
    }

    cout << cnt << "\n";

    return 0;
}
