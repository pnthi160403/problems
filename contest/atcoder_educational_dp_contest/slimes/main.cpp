#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

const ll INF = (ll)1e18;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n; cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) cin >> a[i];
    vector<ll> sum(n + 1);
    for(int i = 1; i <= n; i++) {
        sum[i] = (sum[i - 1] + a[i]);
    }
    vector<vector<ll>> dp(n + 1, vector<ll>(n + 1, -1));
    for(int i = 1; i <= n; i++) dp[i][i] = 0;
    auto dq = [&](auto dq, int i, int j) -> ll {
        if (i >= j) return 0;
        if (dp[i][j] != -1) return dp[i][j];
        ll ans = INF;
        ll sumij = sum[j] - sum[i - 1];
        for(int x = i; x < j; x++) {
            ans = min(ans, dq(dq, i, x) + dq(dq, x + 1, j) + sumij);
        }
        return dp[i][j] = ans;
    };
    cout << dq(dq, 1, n);
    return 0;
}