#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <cstdint>

using namespace std;

using ld = double;
using ll = long long;
using Pt = pair<ld, ld>;

const ld EPS = 1e-9;
const ld SQRT3 = sqrt(ld(3.0));

ld dist2(ld x1, ld y1, ld x2, ld y2) {
    ld dx = x1 - x2, dy = y1 - y2;
    return dx * dx + dy * dy;
}

ld dist2(const Pt &a, const Pt &b) {
    return dist2(a.first, a.second, b.first, b.second);
}

ld modPos(ld a, ld m) {
    a = fmod(a, m);
    if (a < 0) a += m;
    return a;
}

static inline uint64_t splitmix64(uint64_t &x) {
    x += 0x9e3779b97f4a7c15ULL;
    uint64_t z = x;
    z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9ULL;
    z = (z ^ (z >> 27)) * 0x94d049bb133111ebULL;
    return z ^ (z >> 31);
}

bool findCoverCenters(const vector<Pt> &points, ld tx, ld ty, vector<Pt> &centers) {
    centers.clear();
    tx = modPos(tx, 2.0);
    ty = modPos(ty, SQRT3);

    for (const auto &[x, y] : points) {
        bool found = false;
        Pt best{0, 0};

        ld jj = (y - ty) / SQRT3;
        ll j0 = (ll)round(jj);

        for (ll j = j0 - 2; j <= j0 + 2 && !found; j++) {
            ld cy = ty + (ld)j * SQRT3;
            ld dy = y - cy;
            ld dy2 = dy * dy;

            if (dy2 > 1.0 + EPS) continue;

            int parity = (int)(j & 1LL);
            ld xrel = x - tx - (ld)parity;
            ll i0 = (ll)round(xrel / 2.0);

            for (ll i = i0 - 2; i <= i0 + 2; i++) {
                ld cx = tx + (ld)parity + 2.0 * (ld)i;
                ld dx = x - cx;
                ld d2 = dx * dx + dy2;

                if (d2 <= 1.0 + EPS) {
                    best = {cx, cy};
                    found = true;
                    break;
                }
            }
        }

        if (!found) return false;

        bool duplicated = false;
        for (const auto &c : centers) {
            if (dist2(c, best) <= EPS * EPS) {
                duplicated = true;
                break;
            }
        }

        if (!duplicated) centers.push_back(best);

        if (centers.size() > points.size()) return false;
    }

    return true;
}

uint64_t seed = 3101199815021996ULL;

void solve() {
    int n;
    cin >> n;
    vector<Pt> points(n);

    for (auto &[x, y] : points) {
        cin >> x >> y;
    }

    vector<Pt> centers, answer;
    bool ok = false;

    vector<Pt> shifts;
    shifts.reserve(512);

    shifts.push_back({0.0, 0.0});
    shifts.push_back({1.0, 0.0});
    shifts.push_back({0.0, SQRT3 * 0.5});
    shifts.push_back({1.0, SQRT3 * 0.5});

    for (const auto &[x, y] : points) {
        ld tx = modPos(x, 2.0);
        ld ty = modPos(y, SQRT3);
        shifts.push_back({tx, ty});
    }

    for (int it = 0; it < 400; it++) {
        uint64_t a = splitmix64(seed);
        uint64_t b = splitmix64(seed);
        ld tx = (ld)(a >> 11) * (1.0 / (ld)(1ULL << 53)) * 2.0;
        ld ty = (ld)(b >> 11) * (1.0 / (ld)(1ULL << 53)) * SQRT3;
        shifts.emplace_back(tx, ty);
    }

    for (const auto &[tx, ty] : shifts) {
        if (findCoverCenters(points, tx, ty, centers)) {
            answer = centers;
            ok = true;
            break;
        }
    }

    if (ok) {
        cout << "YES\n";
        cout << answer.size() << "\n";
        for (const auto &[x, y] : answer) {
            cout << fixed << setprecision(12) << x << " " << y << "\n";
        }
    } else {
        cout << "NO\n";
    }
}

int main() {
    int tt;
    cin >> tt;
    while(tt--) {
        solve();
    }

    return 0;
}
