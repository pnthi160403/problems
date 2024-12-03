#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n, W; cin >> n >> W;
    vector<int> w(n + 1), v(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> w[i] >> v[i];
    }
    vector<vector<ll>> dp(n + 1, vector<ll>(W + 1));
    for(int i = 1; i <= n; i++) {
        for(int j = 0; j <= W; j++) {
            dp[i][j] = dp[i - 1][j];
            if (j - w[i] >= 0) {
                dp[i][j] = max(dp[i][j], dp[i - 1][j - w[i]] + v[i]);
            }
        }
    }
    ll ans = 0;
    for(int j = 0; j <= W; j++) ans = max(ans, dp[n][j]);
    cout << ans;
    return 0;
}