#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MOD = (int)1e9 + 7;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int m, k; cin >> m >> k;
    vector<vector<ll>> dp(m + 1, vector<ll>(k, 0));
    dp[0][0] = 1;
    for(int i = 1; i <= m; i++) {
        for(int j = 0; j < k; j++) {
            dp[i][j] += dp[i - 1][j];
            dp[i][j] %= MOD;
            dp[i][j] += dp[i - 1][(j - 1 + k) % k] * 3;
            dp[i][j] %= MOD;
            dp[i][j] += dp[i - 1][(j - 2 + k) % k] * 3;
            dp[i][j] %= MOD;
        }
    }
    cout << (dp[m][0] - 1 + MOD) % MOD;
    return 0;
}