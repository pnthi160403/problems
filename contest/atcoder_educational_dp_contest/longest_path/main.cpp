#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n, m; cin >> n >> m;
    vector<vector<int>> adj(n + 1, vector<int>());
    vector<int> in(n + 1);
    for(int i = 1; i <= m; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        in[v]++;
    }
    vector<int> vis(n + 1);
    vector<int> topo;
    auto dfs = [&](auto dfs, int u) -> void {
        vis[u] = 1;
        for(int v : adj[u]) {
            if (vis[v] == 0) {
                dfs(dfs, v);
            }
        }
        vis[u] = 2;
        topo.push_back(u);
    };
    for(int i = 1; i <= n; i++) {
        if (in[i] == 0 && vis[i] == 0) {
            dfs(dfs, i);
        }
    }
    vector<int> dp(n + 1);
    for(int x : topo) {
        dp[x] = 0;
        for(int y : adj[x]) {
            dp[x] = max(dp[x], dp[y] + 1);
        }
    }
    int ans = 0;
    for(int x : dp) ans = max(ans, x);
    cout << ans;
    return 0;
}