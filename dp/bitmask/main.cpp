#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

const int MOD = (int)1e9 + 7;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n;
    cin >> n;
    if (n == 1) {
        cout << 1;
        return 0;
    }
    vector<vector<int>> a(n, vector<int>(n));
    for(int i = 0; i < n; i++) 
        for(int j = 0; j < n; j++)
            cin >> a[i][j];

    auto calc_dp = [&](vector<vector<int>> &arr) -> vector<int> {
        int n = (int)arr.size();
        int m = (int)arr[0].size();
        vector<int> dp(1 << m), pre_dp(1 << m);
        pre_dp[0] = 1;
        for(int i = 0; i < n; i++) {
            for(int mask = 0; mask < (1 << m); mask++) {
                dp[mask] += pre_dp[mask];
                dp[mask] %= MOD;
                for(int j = 0; j < m; j++) {
                    if ((mask >> (n - j - 1)) & 1 == 1 && a[i][j] == 1) {
                        dp[mask] += pre_dp[mask ^ (1 << (n - j - 1))];
                        dp[mask] %= MOD;
                    }
                }
            }
            for(int mask = 0; mask < (1 << m); mask++) {
                pre_dp[mask] = dp[mask];
                dp[mask] = 0;
            }
        }
        return pre_dp;
    };
    vector<int> dp = calc_dp(a);
    cout << dp[(1 << n) - 1];
    return 0;
}