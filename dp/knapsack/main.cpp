#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

const int INF = (int)1e9;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n, w;
    cin >> n >> w;
    vector<int> value(n), weight(n);
    for(int i = 0; i < n; i++) {
        cin >> weight[i] >> value[i];
    }
    int sum_value = 0;
    for(int x : value)
        sum_value += x;
    vector<int> dp(sum_value + 1, INF), pre(sum_value + 1, INF);
    pre[0] = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j <= sum_value; j++) {
            dp[j] = min(dp[j], pre[j]);
            if (j - value[i] >= 0)
                dp[j] = min(dp[j], pre[j - value[i]] + weight[i]);
        }
        for(int j = 0; j <= sum_value; j++) {
            pre[j] = dp[j];
            dp[j] = INF;
        }
    }
    int ans = 0;
    for(int i = sum_value; i >= 0; i--) {
        if (pre[i] <= w) {
            ans = i;
            break;
        }
    }
    cout << ans;
    return 0;
}