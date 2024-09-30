#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> a(n, vector<int>());
    vector<int> in(n, 0);
    for(int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--,v--;
        a[u].push_back(v);
        in[v]++;
    }
    vector<int> dp(n, -1);
    auto dfs = [&](auto dfs, int u) -> int {
        int res = 0;
        for(int v : a[u]) {
            if (dp[v] != -1) {
                res = max(res, dp[v] + 1);
            } else {
                res = max(res, dfs(dfs, v) + 1);
            }
        }
        return dp[u] = res;
    };
    int ans = 0;
    for(int i = 0; i < n; i++) {
        if (in[i] == 0) {
            dfs(dfs, i);
            ans = max(ans, dp[i]);
        }
    }
    cout << ans;
    return 0;
}