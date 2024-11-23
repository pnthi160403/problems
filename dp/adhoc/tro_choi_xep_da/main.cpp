#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

const int MOD = (int)1e9 + 7;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n; cin >> n;
    vector<int> dp(2 * n + 1), pre_dp(2 * n + 1);
    pre_dp[1] = 1;
    for(int i = 2; i <= 2 * n; i++) {
        for(int cnt = 1; cnt <= n; cnt++) {
            dp[cnt] += pre_dp[cnt];
            if (i - cnt <= cnt - 1) {
                dp[cnt] += pre_dp[cnt - 1];
            }
            dp[cnt] %= MOD;
        }
        for(int cnt = 1; cnt <= n; cnt++) pre_dp[cnt] = dp[cnt], dp[cnt] = 0;
    }

    cout << pre_dp[n];
    return 0;
}