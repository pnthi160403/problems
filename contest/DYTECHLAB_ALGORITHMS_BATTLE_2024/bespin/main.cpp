#include <bits/stdc++.h>
#define ll long long
#define endl '\n'
#define ff(i, x, y) for(int i = x; i <= y; i++)
#define fi first
#define se second
#define pb push_back

using namespace std;

const int N = 100 * 16;
map<vector<int>,ll> m[101];

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;
    vector<vector<int>> g(N + 1, vector<int>(N + 1));
    ff(i, 1, N) {
        ff(j, 1, N) {
            g[i][j] = gcd(i, j);
        }
    }
    vector<int> b;
    auto f = [&]() -> ll {
        int res = b[0];
        ff(i, 1, (int)b.size() - 1) res = g[res][b[i]];
        return res;
    };
    auto dq = [&](auto dq, int i) -> ll {
        if (i == n)
            return f();
        if (m[i].find(b) != m[i].end()) return m[i][b];
        ll ans = 0;
        ff(j, 0, (int)b.size() - 1) {
            b[j] += a[i];
            ans += dq(dq, i + 1);
            b[j] -= a[i];
        }
        b.pb(a[i]);
        ans += dq(dq, i + 1);
        b.pop_back();
        return m[i][b] = ans;
    };
    cout << dq(dq, 0);
    return 0;
}