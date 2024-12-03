#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

const int INF = (int)1e9;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n, W; cin >> n >> W;
    vector<int> w(n + 1), v(n + 1);
    ll sum_val = 0;
    for(int i = 1; i <= n; i++) {
        cin >> w[i] >> v[i];
        sum_val += v[i];
    }
    vector<vector<ll>> dp(n + 1, vector<ll>(sum_val + 1, INF));
    dp[0][0] = 0;
    for(int i = 1; i <= n; i++) {
        for(int j = 0; j <= sum_val; j++) {
            if (dp[i - 1][j] != INF)
                dp[i][j] = dp[i - 1][j];
            if (j - v[i] >= 0 && dp[i - 1][j - v[i]] != INF) {
                dp[i][j] = min(dp[i][j], dp[i - 1][j - v[i]] + w[i]);
            }
        }
    }
    int ans = 0;
    for(int j = sum_val; j >= 0; j--) {
        if (dp[n][j] <= W) {
            ans = max(ans, j);
        }
    }
    cout << ans;
    return 0;
}