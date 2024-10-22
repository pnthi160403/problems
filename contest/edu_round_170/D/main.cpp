#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    vector<int> cnt(3 * m, 0);
    for(int &x : a) {
        cin >> x;
        if (x == 0)
            continue;
        cnt[x + m]++;
    }
    vector<vector<int>> dp(m + 1, vector<int>(m + 1, 0));
    vector<vector<int>> pre(m + 1, vector<int>(m + 1, 0));
    int cnt_0 = 0;
    int ans = 0;
    for(int i = 0; i < n; i++) {
        if (a[i] != 0) {
            cnt[a[i] + m]--;
            continue;
        }
        cnt_0++;
        for(int j = 0; j <= cnt_0; j++) {
            int x = j, y = cnt_0 - j;
            if (x - 1 >= 0) {
                dp[x][y] = max(dp[x][y], pre[x - 1][y] + cnt[x + m]);
            }
            if (y - 1 >= 0) {
                dp[x][y] = max(dp[x][y], pre[x][y - 1] + cnt[-y + m]);
            }
            ans = max(ans, dp[x][y]);
        }
        for(int j = 0; j <= cnt_0; j++) {
            int x = j, y = cnt_0 - j;
            pre[x][y] = dp[x][y];
            dp[x][y] = 0;
        }
    }
    cout << ans;
    return 0;
}