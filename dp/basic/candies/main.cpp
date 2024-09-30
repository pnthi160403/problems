#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

const ll MOD = (ll)1e9 + 7;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n, k;
    cin >> n >> k;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++)
        cin >> a[i];
    vector<ll> dp(k + 1, 0);
    vector<ll> prefix_dp(k + 1, 0);
    for(int j = 0; j <= min(k, a[1]); j++) {
        dp[j] = 1;
    }
    for(int i = 2; i <= n; i++) {
        prefix_dp[0] = dp[0];
        for(int j = 1; j <= k; j++) {
            prefix_dp[j] = (prefix_dp[j - 1] + dp[j]) % MOD;
        }
        for(int j = 0; j <= k; j++)
            dp[j] = 0;
        for(int j = 0; j <= k; j++) {
            if (j - a[i] - 1 < 0)
                dp[j] = (dp[j] + prefix_dp[j]) % MOD;
            else
                dp[j] = (dp[j] + prefix_dp[j] - prefix_dp[j - a[i] - 1] + MOD) % MOD;
        }
    }
    cout << dp[k];
    return 0;
}