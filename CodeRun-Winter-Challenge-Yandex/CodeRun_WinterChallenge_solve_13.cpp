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

ll find_res(ll q, ll l, ll r) {
    ll full_res = 0;
    for(ll n = l; n <= r; n++) {
        for(ll m = l; m <= r; m++) {
            for(ll k = l; k <= r; k++) {
                for(ll s = l; s <= r; s++) {
                    ll a = dop_find(q, 10 + n) - dop_find(q, 10 + m);
                    ll b = dop_find(q, 10 + k) - dop_find(q, 10 + s);
                    if(b == 0) {
                        continue;
                    }
                    if(a == 0 || a % b == 0) {
                        full_res++;
                    }
                }
            }
        }
    }

    return full_res;
}

ll find_res_plus(ll l, ll r) {
    ll res = 0;
    r = r - l;

    for(ll i = 1; i <= r; i++) {
        ll k = 0;
        for(ll j = 1; j * j <= i; j++) {
            if(i % j == 0) {
                if(j * j != i) {
                    k++;
                }
                k++;
            }
        }

        ll cnt = (2 * k) % mod;
        cnt *= (((1 + (r - i + 1)) % mod) * ((r - i + 1) % mod)) % mod;
        cnt %= mod;
        res += cnt;
        res %= mod;
    }

    ll dop_res = (r + 1) % mod;
    dop_res *= (r + 1) % mod;
    dop_res %= mod;
    dop_res *= r % mod;
    dop_res %= mod;
    return (res + dop_res) % mod;
}

ll find_floor(ll x) {
    if(x >= 0) {
        return x / 2;
    } else {
        return (x - 1) / 2;
    }
}

ll find_sum_1(ll n) {
    if(n == 0) {
        return 0;
    }
    ll sqrt_n = sqrt(n);
    ll ans = 0;
    for(ll k = 1; k <= sqrt_n; k++) {
        ans += n / k;
    }
    ans = 2 * ans - sqrt_n * sqrt_n;
    return ((ans % mod) + mod) % mod;
}

ll find_sum_2(ll n) {
    if(n == 0) {
        return 0;
    }
    ll sqrt_n = sqrt(n);
    ll S = 0;

    ll inv2 = find_step(2, mod - 2);
    for(ll d = 1; d <= sqrt_n; d++) {
        ll q = n / d;
        ll term = (((d % mod) * (q % mod)) % mod) * ((((q + 1) % mod) * inv2) % mod);
        term %= mod;
        S = (S + term) % mod;
    }

    ll q_max = n / (sqrt_n + 1);
    for(ll q = 1; q <= q_max; q++) {
        ll d_max = n / q;
        ll d_min = n / (q + 1) + 1;
        if(d_min <= sqrt_n) {
            d_min = sqrt_n + 1;
        }
        if(d_min > d_max) {
            continue;
        }
        ll num = (d_min + d_max) % mod;
        ll cnt = (d_max - d_min + 1) % mod;
        ll sum_d = (((num * cnt) % mod) * inv2) % mod;
        ll term = (((sum_d * (q % mod)) % mod) * (((((q + 1) % mod) % mod) * inv2) % mod)) % mod;
        S = (S + term) % mod;
    }
    return S;
}

ll find_sum_3(ll n) {
    if(n == 0) {
        return 0;
    }
    ll sqrt_n = sqrt(n);
    ll S = 0;

    ll inv6 = find_step(6, mod - 2);
    for(ll d = 1; d <= sqrt_n; d++) {
        ll q = n / d;
        ll term = (((d % mod) * (d % mod) % mod) * (((q % mod) * ((q + 1) % mod) % mod) % mod))% mod;
        term *= (((2 * q + 1) % mod) * inv6) % mod;
        term %= mod;
        S = (S + term) % mod;
    }

    ll q_max = n / (sqrt_n + 1);
    for(ll q = 1; q <= q_max; q++) {
        ll d_max = n / q;
        ll d_min = n / (q + 1) + 1;
        if(d_min <= sqrt_n) {
            d_min = sqrt_n + 1;
        }
        if(d_min > d_max) {
            continue;
        }
        ll a = d_min, b = d_max;
        ll sum_d2 = ((b % mod) * ((b + 1) % mod) % mod * ((2 * b + 1) % mod) % mod -
                     ((a - 1) % mod) * (a % mod) % mod * ((2 * a - 1) % mod) % mod) % mod;
        sum_d2 = (sum_d2 + mod) % mod;
        sum_d2 = (sum_d2 * inv6) % mod;
        ll term = sum_d2 * (q % mod) % mod * ((q + 1) % mod) % mod *
                  ((2 * q + 1) % mod) % mod * inv6 % mod;
        S = (S + term) % mod;
    }
    return S;
}

ll dop_main(ll a, ll q, ll l, ll r) {
    if(a == 0) {
        return 0;
    } else if(q == 1) {
        return 0;
    }

    ll N = r - l + 1;
    ll N_mod = ((N % mod) + mod) % mod;

    if(q == -1) {
        ll cnt_1 = find_floor(r) - find_floor(l - 1);
        ll cnt_2 = N - cnt_1;
        ll cnt_1_mod = ((cnt_1 % mod) + mod) % mod;
        ll cnt_2_mod = ((cnt_2 % mod) + mod) % mod;
        ll res = (((((2 * N_mod) % mod) * N_mod) % mod) * ((cnt_1_mod * cnt_2_mod) % mod)) % mod;
        return res;
    }

    ll M = r - l;
    if(M == 0) {
        return 0;
    }

    ll sum_1 = find_sum_1(M);
    ll sum_2 = find_sum_2(M);
    ll sum_3 = find_sum_3(M);

    ll sum = (sum_3 - ((((2 * N_mod + 1) % mod) * sum_2) % mod) + mod) % mod;
    sum += ((((N_mod * N_mod) % mod + N_mod) % mod) * sum_1) % mod;
    sum = (sum * find_step(2, mod - 2)) % mod;

    ll case_1 = (((N_mod * N_mod) % mod) * ((N_mod - 1 + mod) % mod)) % mod;
    ll case_2 = (4 * sum) % mod;
    ll res = (case_1 + case_2) % mod;

    return res;
}

ll a_n(ll n) {
    if(n == 1 || n == 2) {
        return 0;
    }
    if(n % 2 == 0) {
        ll k = n / 2;
        k %= mod;
        ll a = (k * k) % mod;
        a *= 8;
        a %= mod;

        ll b = (14 * k) % mod;
        return (((((k - 1 + mod) % mod) * ((a + b + 12) % mod)) % mod) * find_step(3, mod - 2)) % mod;
    } else {
        ll k = (n - 1) / 2;
        k %= mod;
        ll a = (k * k) % mod;
        a *= (8 * k) % mod;
        a %= mod;
        ll b = (k * k) % mod;
        b *= 18;
        b %= mod;
        ll c = (10 * k) % mod;
        return (((a + b + c - 12 + mod) % mod) * find_step(3, mod - 2)) % mod;
    }
}

ll dop_main_1(ll a, ll q, ll l, ll r) {
    ll res = dop_main(a, q, l, r);
    if(q == -2) {
        res += a_n(r - l + 1);
    }

    return res % mod;
}

int main() {
    /*vector<ll> v_1(20);
    vector<ll> v_2(20);
    for(int i = 0; i < 20; i++) {
        v_1[i] = find_res(-2, 0, i);
    }

    for(int i = 0; i < 20; i++) {
        v_2[i] = find_res(-3, 0, i);
    }

    vector<ll> v_3(20);
    for(int i = 0; i < 20; i++) {
        v_3[i] = v_1[i] - v_2[i];
    }

    vector<ll> v_4(19);
    for(int i = 0; i < 19; i++) {
        v_4[i] = v_3[i + 1] - v_3[i];
    }

    for(int i = 0; i < 20; i++) {
        cout << v_1[i] << " ";
    }
    cout << "\n";
    for(int i = 0; i < 20; i++) {
        cout << v_2[i] << " ";
    }
    cout << "\n";
    for(int i = 0; i < 20; i++) {
        cout << v_3[i] << " ";
    }
    cout << "\n";
    for(int i = 0; i < 19; i++) {
        cout << v_4[i] << " ";
    }
    cout << "\n";*/

    ll a, q, l, r;
    cin >> a >> q >> l >> r;
    cout << dop_main_1(a, q, l, r) << "\n";

    /*cout << find_res(2, 0, 5) << "\n";
    cout << find_res(2, 0, 5) << "\n";
    cout << find_res(2, 1, 6) << "\n";
    cout << dop_main_1(1, 2, -5, 0) << "\n";
    cout << dop_main_1(1, 2, 0, 5) << "\n";
    cout << dop_main_1(1, 2, 1, 6) << "\n";
    cout << dop_main_1(1, -2, 1, 6) << "\n";
    cout << dop_main_1(1, -2, -5, 0) << "\n";
    cout << dop_main_1(1, -2, 0, 5) << "\n";
    cout << find_res(2, 1, 6) << "\n";
    cout << "\n";


    for(int q = -4; q <= 4; q++) {
        if(q == 0) {
            continue;
        }
        for(int l = -10; l <= 10; l++) {
            for(int r = l; r <= 10; r++) {
                ll a = dop_main_1(1, q, l, r);
                ll b = find_res(q, l, r);
                if(a != b) {
                    cout << q << " " << l << " " << r << "\n";
                }
            }
        }
    }


    if(a == 0) {
        cout << 0 << "\n";
    } else if(q == 0) {
        cout << 0 << "\n";
    } else if(q == 1) {
        ll N = (r - l + 1) % mod;
        if(l <= 0 && 0 <= r) {
            cout << (2 * (N + mod - 1) * ((N * N) % mod)) % mod << "\n";
        } else {
            cout << 0 << "\n";
        }
    } else {
        if(q > 0) {
        }
    }*/

    return 0;
}
