#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n; cin >> n;
    vector<double> p(n + 1);
    for(int i = 1; i <= n; i++) cin >> p[i];
    vector<vector<double>> dp(n + 1, vector<double>(n + 1, 0.0));
    double ans = 0.0;
    dp[0][0] = 1;
    for(int i = 1; i <= n; i++) {
        for(int j = 0; j <= i; j++) {
            dp[i][j] += dp[i - 1][j] * (1 - p[i]);
            if (j - 1 >= 0)
                dp[i][j] += dp[i - 1][j - 1] * p[i];
            if (i == n && 2 * j > n) ans += dp[i][j];
        }
    }
    cout << fixed << setprecision(10) << ans;
    return 0;
}