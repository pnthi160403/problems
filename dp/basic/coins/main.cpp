#include <bits/stdc++.h>
#define ll long long
#define endl '\n'
using namespace std;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n;
    cin >> n;
    vector<double> p(n + 1);
    for(int i = 1; i <= n; i++)
        cin >> p[i];
    vector<vector<double>> dp(n + 1, vector<double>(n + 1, 0));
    dp[0][1] = 1 - p[1];
    dp[1][0] = p[1];
    for(int i = 0; i <= n; i++) {
        for(int j = 0; j <= n; j++) {
            if (i - 1 >= 0)
                dp[i][j] += dp[i - 1][j] * p[i + j];
            if (j - 1 >= 0)
                dp[i][j] += dp[i][j - 1] * (1 - p[i + j]);
        }
    }
    double ans = 0;
    for(int i = 0; i <= n; i++) {
        for(int j = 0; j <= n; j++) {
            if (i + j == n && i > j) {
                ans += dp[i][j];
            }
        }
    }
    cout << fixed << setprecision(9) << ans;
    return 0;
}
