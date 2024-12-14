#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

const int MOD = (int)1e7 + 7;
const int BASE = 311;

int cnt[MOD];

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n, s; cin >> n >> s;
    vector<pair<int,int>> a;
    s = 2 * s;
    for(int i = 1; i <= s; i++) {
        if (s % i == 0) a.push_back({i, s / i});
    }
    vector<pair<int,int>> b;
    int offset = (int)1e5;
    for(int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        b.push_back({x, y});
        x += offset;
        y += offset;
        int hash = (x * BASE + y) % MOD;
        cnt[hash]++;
    }
    ll ans = 0;
    for(auto[_a, _b] : a) {
        for(auto[x, y] : b) {
            int x1 = _b + x;
            int x2 = - _b + x;
            int y1 = _a + y;
            int y2 = - _a + y;
            vector<int> xs, ys;
            if (x1 >= - offset && x1 <= offset) xs.push_back(x1);
            if (x2 >= - offset && x2 <= offset) xs.push_back(x2);
            if (y1 >= - offset && y1 <= offset) ys.push_back(y1);
            if (y2 >= - offset && y2 <= offset) ys.push_back(y2);
            for(int _x : xs) {
                for(int _y : ys) {
                    int hashx_y = ((x + offset) * BASE + _y + offset) % MOD;
                    int hash_xy = ((_x + offset) * BASE + y + offset) % MOD;
                    ans += 1ll * cnt[hashx_y] * cnt[hash_xy];
                    if (_y == y) ans -= cnt[hash_xy];
                    if (_x == x) ans -= cnt[hashx_y];
                }
            }
        }
    }
    cout << ans;
    return 0;
}