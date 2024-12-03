#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

const int MOD = (int)1e9 + 7;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n, k; cin >> n >> k;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) cin >> a[i];
    vector<vector<int>> dp(n + 1, vector<int>(k + 1));
    dp[0][0] = 1;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= k; j++) {
            dp[i - 1][j] = (dp[i - 1][j] + dp[i - 1][j - 1]) % MOD;
        }
        for(int j = 0; j <= k; j++) {
            int l = max(0, j - a[i]);
            int r = j;
            dp[i][j] = (dp[i - 1][r] - (l == 0 ? 0 : dp[i - 1][l - 1]) + MOD) % MOD;
        }
    }
    cout << dp[n][k];
    return 0;
}