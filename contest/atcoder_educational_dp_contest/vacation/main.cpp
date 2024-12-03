#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n; cin >> n;
    vector<vector<int>> a(n + 1, vector<int>(3));
    for(int i = 1; i <= n; i++) {
        for(int j = 0; j < 3; j++) {
            cin >> a[i][j];
        }
    }
    vector<vector<int>> dp(n + 1, vector<int>(3, 0));
    for(int i = 1; i <= n; i++) {
        for(int j = 0; j < 3; j++) {
            for(int k = 0; k < 3; k++) {
                if (k == j) continue;
                dp[i][j] = max(dp[i][j], dp[i - 1][k] + a[i][j]);
            }
        }
    }
    cout << max({dp[n][0], dp[n][1], dp[n][2]});
    return 0;
}