#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

const ll INF = (ll)1e18;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n; cin >> n;
    vector<ll> pre_sum(n + 1);
    for(int i = 1; i <= n; i++) cin >> pre_sum[i];
    for(int i = 1; i <= n; i++) pre_sum[i] += pre_sum[i - 1];
    vector<vector<ll>> dp(n + 1, vector<ll>(n + 1, -INF));
    auto dq = [&](auto dq, int i, int j) -> ll {
        if (i > j) return 0;
        if (i == j) return pre_sum[i] - pre_sum[i - 1];
        if (dp[i][j] != -INF) return dp[i][j];
        return dp[i][j] = pre_sum[j] - pre_sum[i - 1] - min(dq(dq, i + 1, j), dq(dq, i, j - 1));
    };
    cout << 1ll * 2 * dq(dq, 1, n) - pre_sum[n];
    return 0;
}