#include <bits/stdc++.h>
#define ll long long
#define int ll
#define endl '\n'

using namespace std;

const int MOD = (int)1e9 + 7;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while(t--) {
        int n, k, m; cin >> n >> k >> m;
        if (n == 1) {
            cout << 0 << endl;
            continue;
        }
        pair<ll,ll> cur = {1, 1};
        vector<pair<ll,ll>> a;
        auto bs = [&](ll a, int b) -> ll {
            ll res = 1;
            while(b) {
                if (b & 1) {
                    res *= a;
                    res %= MOD;
                }
                b /= 2;
                a *= a;
                a %= MOD;
            }
            return res;
        };
        ll ans = 0;
        while(m--) {
            if (n > k && m >= 1) {
                n -= k;
            } else {
                ans += cur.first * bs(cur.second, MOD - 2) % MOD * 1 * bs(n, MOD - 2) % MOD;
                cur = {n - 1, n};
                n += k;
            }
        }
        cout << ans << endl;
    }
    return 0;
}