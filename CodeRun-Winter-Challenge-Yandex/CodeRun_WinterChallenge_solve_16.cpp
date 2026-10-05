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

ll mod = 1e9 + 7;

struct edge {
    ll cnt;
    vector<pair<ll, ll>> v;
};

ll find_step(ll n, ll cnt) {
    if(cnt == 0) {
        return 1;
    } else if(cnt % 2 == 0) {
        ll a = find_step(n, cnt/2);
        return (a * a) % mod;
    } else {
        return (find_step(n, cnt - 1) * n) % mod;
    }
}

ll dop_find(ll n, ll cnt) {
    if(cnt == 0) {
        return 1;
    } else if(cnt % 2 == 0) {
        ll a = dop_find(n, cnt/2);
        return a * a;
    } else {
        return dop_find(n, cnt - 1) * n;
    }
}

ll find_pow(ll x, ll cnt) {
    if(cnt < 0) {
        cnt = -cnt;
        return pow((double)x, (double)1/cnt);
    } else {
        return pow((double)x, (double)cnt);
    }
}

vector<vector<edge>> find_res(ll q, ll l, ll r) {
    vector<vector<edge>> vv(r - l + 1, vector<edge>(r - l + 1));
    map<int, int> mapf;
    int ind = 0;
    for(int i = l; i <= r; i++) {
        mapf[i] = ind;
        ind++;
    }
    ll full_res = 0;
    for(ll n = l; n <= r; n++) {
        for(ll m = l; m <= r; m++) {
            ll res = 0;
            vector<pair<ll, ll>> v;

            for(ll k = l; k <= r; k++) {
                for(ll s = l; s <= r; s++) {
                    ll a = dop_find(q, 10 + n) - dop_find(q, 10 + m);
                    ll b = dop_find(q, 10 + k) - dop_find(q, 10 + s);
                    if(b == 0) {
                        continue;
                    }
                    if(a == 0 || a % b == 0) {
                        res++;
                        full_res++;
                        v.push_back({k, s});
                    }
                }
            }

            vv[mapf[n]][mapf[m]] = {res, v};
        }
    }

    return vv;
}

ll find_sum_5(int i, int j, ll num_2, ll num_3, ll real_N) {
    ll s = 1;
    ll f = (real_N - num_2 * num_3) % mod;
    ll cnt_5 = (2 * (f + s) * f) % mod;
    cnt_5 *= ((i + 1) * (j + 1) - 2 + mod) % mod;
    cnt_5 %= mod;
    return cnt_5;
}

ll true_find_res(ll q, ll l, ll r) {
    ll new_l = l, new_r = r;
    if(l < 0) {
        new_l = 0, new_r = r - l;
    }

    if(new_l != 0) {
        new_l = 0;
        new_r = r - l;
    }

    ll N = new_r + 1;
    ll real_N = N;
    ll real_r = new_r;
    N %= mod;

    new_r %= mod;
    ll first_sum = N * N;
    first_sum %= mod;
    first_sum *= (N - 1 + mod) % mod;
    ll res = first_sum;

    ll second_sum = N * (N - 1 + mod);
    second_sum %= mod;
    second_sum = (2 * second_sum) % mod;
    res += second_sum;

    if(N > 2) {
        ll sum_3 = new_r * (new_r - 1 + mod);
        sum_3 %= mod;
        sum_3 *= new_r;
        sum_3 %= mod;
        sum_3 *= 4;
        sum_3 %= mod;

        ll sum_4 = (new_r - 1 + mod) * (2 * new_r - 1 + mod);
        sum_4 %= mod;
        sum_4 *= find_step(6, mod - 2);
        sum_4 %= mod;
        sum_4 *= 8;
        sum_4 %= mod;
        sum_4 *= new_r;
        sum_4 %= mod;

        ll res_34 = (sum_3 - sum_4 + mod) % mod;
        res += res_34;
        res %= mod;
    }

    ll cnt_num_2 = 41;
    ll cnt_num_3 = 27;
    ll num_2 = 1;
    bool isa = false;
    for(int i = 0; i <= cnt_num_2; i++) {
        ll num_3 = 1;
        for(int j = 0; j <= cnt_num_3; j++) {
            if(num_2 * num_3 == 1) {
                num_3 *= 3;
                continue;
            }
            if(num_2 * num_3 >= real_N) {
                break;
            }

            ll k = 1;
            if(num_2 * num_3 <= 3) {
                k++;
            }
            while(real_N > num_2 * num_3 * k) {
                if(k % 2 == 0 || k % 3 == 0) {
                    k++;
                    continue;
                }
                ll last_el = (real_N - num_2 * num_3 * k) % mod;
                ll cnt_5 = (2 * (last_el + 1) * last_el) % mod;
                cnt_5 *= ((i + 1) * (j + 1) - 2 + (k != 1) + (k % 2 == 1 && k != 1)) % mod;
                cnt_5 %= mod;

                cout << num_2 * num_3 * k << " " << cnt_5 << "\n";

                res += cnt_5;
                res %= mod;
                k++;
            }

            num_3 *= 3;
        }
        num_2 *= 2;
    }

    return res;
}

ll return_sum(ll a) {
    string s = to_string(a);
    ll sum = 0;
    for(int i = 0; i < s.size(); i++) {
        sum += s[i] - '0';
    }
    return sum;
}

int main() {
    ll n;
    cin >> n;
    string s = to_string(n);
    int cnt = s.size();
    if(n <= 9) {
        cout << 1 << "\n" << 1 << "\n";
    } else if(n % find_pow(10, cnt - 1) == 0) {
        if(n == find_pow(10, cnt - 1)) {
            cout << n - 1 << "\n" << n - 1 << "\n";
        } else {
            cout << n - 1 << "\n" << find_pow(10, cnt) - 1 << "\n";
        }
    } else {
        for(int i = 1; i < cnt; i++) {
            s[i] = '9';
        }
        cout << s << "\n" << find_pow(10, cnt) - 1 << "\n";
    }

    /*ll a, q, l, r;
    cin >> a >> q >> l >> r;
    if(q == 1) {
        cout << 0 << "\n";
    } else if(q > 0) {
        cout << true_find_res(q, l, r) << '\n';
    } else if(q == 0) {
        ll N = (r - l + 1) % mod;
        if(l <= 0 && 0 <= r) {
            cout << (2 * (N + mod - 1) * ((N * N) % mod)) % mod << "\n";
        } else {
            cout << 0 << "\n";
        }
    } else {
        vector<ll> v(10);
        cout << v[20] << "\n";
    }

    for(ll q = 2; q <= 2; q++) {
        for(ll l = -10; l <= -10; l++) {
            for(ll r = 10; r <= 10; r++) {
                vector<vector<edge>> a = find_res(q, l, r);
                ll res_b = true_find_res(q, l, r);
                ll res_a = 0;
                for(int i = 0; i < a.size(); i++) {
                    for(int j = 0; j < a[0].size(); j++) {
                        res_a += a[i][j].cnt;
                    }
                }

                if(res_a != res_b) {
                    cout << q << " " << l << " " << r << " " << res_a << " " << res_b << "\n";
                    /*for(int i = 0; i < a.size(); i++) {
                        for(int j = 0; j < a[0].size(); j++) {
                            cout << i << " " << j << " " << a[i][j].cnt << " " << b[i][j] << "\n";
                            for(int z = 0; z < a[i][j].v.size(); z++) {
                                cout << a[i][j].v[z].first << " " << a[i][j].v[z].second << " | ";
                            }
                            cout << "\n";

                        }
                    }
                }
            }
        }
    }*/

    return 0;
}
