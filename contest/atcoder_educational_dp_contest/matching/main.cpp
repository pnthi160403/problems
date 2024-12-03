#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

const int MOD = (int)1e9 + 7;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n; cin >> n;
    vector<vector<int>> a(n + 1, vector<int>(n + 1));
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            cin >> a[i][j];
        }
    }
    vector<vector<int>> dp(n + 1, vector<int>(1 << n, -1));
    auto dq = [&](auto dq, int i, int mask) -> int {
        if (i == 0) return 1;
        if (dp[i][mask] != -1) return dp[i][mask];
        int ans = 0;
        for(int j = 0; j < n; j++) {
            if (((mask >> j) & 1) == 1 && a[i][j + 1] == 1) {
                ans += dq(dq, i - 1, mask ^ (1 << j));
                ans %= MOD;
            }
        }
        return dp[i][mask] = ans;
    };
    cout << dq(dq, n, (1 << n) - 1);
    return 0;
}