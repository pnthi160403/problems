#include <bits/stdc++.h>
#define ll long long
#define endl '\n'
#define ff(i, x, y) for(int i = x; i <= y; i++)
#define fi first
#define se second

using namespace std;

const int MOD = (int)1e9 + 7;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n, m; cin >> n >> m;
    vector<vector<int>> a(n + 1, vector<int>());
    for(int i = 1; i <= n; i++) {
        int k; cin >> k;
        while(k--) {
            int x; cin >> x;
            x--;
            a[i].push_back(x);
        }
    }
    vector<vector<int>> have(n + 2, vector<int>(m, 0));
    for(int i = n; i >= 1; i--) {
        for(int j = 0; j < m; j++) {
            have[i][j] = have[i + 1][j];
        }
        for(int j : a[i]) {
            have[i][j] = 1;
        }
    }
    auto bs = [&](int a, int b) -> int {
        int res = 1;
        while(b) {
            if (b & 1) {
                res *= a;
                res %= MOD;
            }
            b = b / 2;
            a *= a;
            a %= MOD;
        }
        return res;
    };
    auto dq = [&](auto dq, int i, int mask) -> int {
        if (mask == ((1 << m) - 1)) {
            return bs(2, n - i + 1);
        }
        if (i == n + 1) return 0;
        int _mask = mask;
        for(int j : a[i]) {
            if ((mask & (1 << j)) == 0) {
                _mask ^= (1 << j);
            }
        }
        int ans = dq(dq, i + 1, _mask) % MOD;
        bool check = true;
        for(int j = 0; j < m; j++) {
            if (mask & (1 << j)) continue;
            if (have[i + 1][j] == 0) {
                check = false;
                break;
            }
        }
        if (check) ans = (ans + dq(dq, i + 1, mask)) % MOD;
        return ans;
    };
    cout << dq(dq, 1, 0);
    return 0;
}