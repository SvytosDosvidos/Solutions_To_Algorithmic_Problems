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

int main()
{
    int n = 10;
    vector<int> v(n);
    for(int i = 0; i < n; i++) {
        cin >> v[i];
    }

    int res = 0;
    int min_n = 1e9;
    vector<int> b(n, 0);
    while(true) {
        int ind = n - 1;
        while(b[ind] == 1) {
            b[ind] = 0;
            ind--;
            if(ind == -1) {
                break;
            }
        }
        if(ind == -1) {
            break;
        }
        b[ind]++;
        int sum = 0;
        for(int i = 0; i < n; i++) {
            sum += v[i] * b[i];
        }

        if(min_n > abs(100 - sum) || min_n == abs(100 - sum) && sum > res) {
            min_n = abs(100 - sum);
            res = sum;
        }
    }

    cout << res << "\n";

    return 0;
}
