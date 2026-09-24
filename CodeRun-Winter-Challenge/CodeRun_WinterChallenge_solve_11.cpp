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

ll mod = 998244353;
const ll cnt_main = 100;
vector<vector<ll>> find_res(int n, vector<ll> &v) {
    vector<vector<ll>> dp(10, vector<ll>(10));
    for(int i_1 = 1; i_1 < 10; i_1++) {
        for(int i_2 = 0; i_2 < 10; i_2++) {
            for(int i_3 = 0; i_3 < 10; i_3++) {
                if(binary_search(v.begin(), v.end(), i_1 + i_2 + i_3)) {
                    dp[i_2][i_3]++;
                    dp[i_2][i_3] %= mod;
                }
            }
        }
    }

    for(int i = 4; i <= n; i++) {
        vector<vector<ll>> dp_new(10, vector<ll>(10));
        for(int i_1 = 0; i_1 < 10; i_1++) {
            for(int i_2 = 0; i_2 < 10; i_2++) {
                for(int i_3 = 0; i_3 < 10; i_3++) {
                    if(binary_search(v.begin(), v.end(), i_1 + i_2 + i_3)) {
                        dp_new[i_2][i_3] += dp[i_1][i_2];
                        dp_new[i_2][i_3] %= mod;
                    }
                }
            }
        }
        dp = dp_new;
    }

    return dp;
}

string create_s(ll n) {
    ll a = 1;
    ll dop = 0;
    while(dop < 50) {
        a *= 2;
        dop++;
    }

    string s;
    s.resize(dop + 1);

    while(dop >= 0) {
        if(n >= a) {
            n -= a;
            s[dop] = '1';
        } else {
            s[dop] = '0';
        }
        dop--;
        a/=2;
    }

    return s;
}

int main() {
    ll n, m;
    cin >> n >> m;

    vector<ll> v(m);
    for(int i = 0; i < m; i++) {
        cin >> v[i];
    }

    sort(v.begin(), v.end());

    vector<vector<vector<vector<ll>>>> cnts(10, vector<vector<vector<ll>>>(10, vector<vector<ll>>(10, vector<ll>(10))));
    vector<vector<ll>> dp(10, vector<ll>(10));
    for(int i_1 = 0; i_1 < 10; i_1++) {
        for(int i_2 = 0; i_2 < 10; i_2++) {
            dp[i_1][i_2] = 1;
            for(int ind = 1; ind <= cnt_main; ind++) {
                vector<vector<ll>> dp_new(10, vector<ll>(10));
                for(int i_3 = 0; i_3 < 10; i_3++) {
                    for(int i_4 = 0; i_4 < 10; i_4++) {
                        for(int i_5 = 0; i_5 < 10; i_5++) {
                            if(binary_search(v.begin(), v.end(), i_3 + i_4 + i_5)) {
                                dp_new[i_4][i_5] += dp[i_3][i_4];
                                dp_new[i_4][i_5] %= mod;
                            }
                        }
                    }
                }
                dp = dp_new;
            }

            for(int i_3 = 0; i_3 < 10; i_3++) {
                for(int i_4 = 0; i_4 < 10; i_4++) {
                    cnts[i_1][i_2][i_3][i_4] = dp[i_3][i_4];
                    dp[i_3][i_4] = 0;
                }
            }
        }
    }

    vector<vector<ll>> v_nums;
    if(n < 500) {
        v_nums = find_res(n, v);
        ll res = 0;
        for(int i = 0; i < 10; i++) {
            for(int j = 0; j < 10; j++) {
                res += v_nums[i][j];
                res %= mod;
            }
        }

        cout << res << "\n";
    } else {
        v_nums = find_res(cnt_main + n%cnt_main, v);

        vector<vector<vector<vector<ll>>>> cnts_new(10, vector<vector<vector<ll>>>(10, vector<vector<ll>>(10, vector<ll>(10))));
        n -= cnt_main - n%cnt_main;
        n /= cnt_main;

        string s = create_s(n);
        int ind_cp = 0;
        for(int ind = 0; ind < s.size(); ind++) {
            if(s[ind] == '1') {
                ind_cp = ind;
            }
        }

        vector<vector<vector<vector<vector<ll>>>>> cnts_saves(ind_cp + 1);
        cnts_saves[0] = cnts;
        for(int ind = 1; ind <= ind_cp; ind++) {
            for(int i_1 = 0; i_1 < 10; i_1++) {
                for(int j_1 = 0; j_1 < 10; j_1++) {
                    for(int i_2 = 0; i_2 < 10; i_2++) {
                        for(int j_2 = 0; j_2 < 10; j_2++) {
                            for(int i = 0; i < 10; i++) {
                                for(int j = 0; j < 10; j++) {
                                    if(i == 0 && j == 0) {
                                        cnts_new[i_1][j_1][i_2][j_2] = 0;
                                    }
                                    cnts_new[i_1][j_1][i_2][j_2] += cnts[i_1][j_1][i][j] * cnts[i][j][i_2][j_2];
                                    cnts_new[i_1][j_1][i_2][j_2] %= mod;
                                }
                            }
                        }
                    }
                }
            }
            cnts = cnts_new;
            if(s[ind] == '1') {
                cnts_saves[ind] = cnts;
            }
        }

        for(int ind = ind_cp; ind >= 0; ind--) {
            if(s[ind] == '0') {
                continue;
            }

            vector<vector<ll>> v_nums_copy(10, vector<ll>(10));
            for(int i_1 = 0; i_1 < 10; i_1++) {
                for(int j_1 = 0; j_1 < 10; j_1++) {
                    ll res = 0;
                    for(int i_2 = 0; i_2 < 10; i_2++) {
                        for(int j_2 = 0; j_2 < 10; j_2++) {
                            res += cnts_saves[ind][i_2][j_2][i_1][j_1] * v_nums[i_2][j_2];
                            res %= mod;
                        }
                    }
                    v_nums_copy[i_1][j_1] = res;
                }
            }

            v_nums = v_nums_copy;
        }

        ll res = 0;
        for(int i_1 = 0; i_1 < 10; i_1++) {
            for(int j_1 = 0; j_1 < 10; j_1++) {
                res += v_nums[i_1][j_1];
            }
        }

        cout << res % mod << "\n";
    }

    return 0;
}
