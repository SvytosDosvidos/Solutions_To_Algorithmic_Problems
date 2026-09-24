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
/*
1 2 3 4 5 6 7 8 9 10 11 = 0
2 1 4 3 6 5 8 7 10 9 11 = 5
1 2 3 4 5 6 7 8 9 10 11
1 * 3 * 5 * 7 * 9 ** 11
2 1 4 3 6 5 8 7 10 11 9
4
*/
int main() {

    int n;
    cin >> n;
    vector<ll> v_1(n);
    vector<ll> v_2(n);

    for(int i = 0; i < n; i++) {
        cin >> v_1[i];
    }

    for(int i = 0; i < n; i++) {
        v_2[i] = i + 1;
    }

    vector<int> res(n);
    if(n % 2 == 0) {
        for(int i = 0; i < n; i += 2) {
            if(v_1[i] == v_2[i] || v_1[i + 1] == v_2[i + 1]) {
                swap(v_2[i], v_2[i + 1]);
            }
            res[i] = v_2[i];
            res[i + 1] = v_2[i + 1];
        }
    } else {
        bool isa = false;
        for(int i = 0; i < n; i += 2) {
            if(v_1[i] != v_2[i]) {
                for(int j = 0; j < i; j+=2) {
                    res[j] = v_2[j + 1];
                    res[j + 1] = v_2[j];
                }
                res[i] = v_2[i];
                for(int j = i + 1; j < n; j+=2) {
                    if(v_1[j] == v_2[j] || v_1[j + 1] == v_2[j + 1]) {
                        swap(v_2[j], v_2[j + 1]);
                    }
                    res[j] = v_2[j];
                    res[j + 1] = v_2[j + 1];
                }
                isa = true;
                break;
            }
        }
        if(!isa) {
            for(int i = 0; i < n - 3; i+=2) {
                res[i] = v_2[i + 1];
                res[i + 1] = v_2[i];
            }
            res[n - 1] = v_2[n - 3];
            res[n - 2] = v_2[n - 1];
            res[n - 3] = v_2[n - 2];
        }
    }

    for(int i = 0; i < n; i++) {
        cout << res[i] << ' ';
    }
    cout << "\n";

    return 0;
}
