// https://codeforces.com/contest/919/problem/D
#include <bits/stdc++.h>
#define ll long long
#define endl '\n'
#define ff(i, x, y) for(int i = x; i <= y; i++)
#define fi first
#define se second
#define pb push_back

using namespace std;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n, m; cin >> n >> m;
    vector<char> a(n + 1);
    string s; cin >> s;
    ff(i, 1, n) a[i] = s[i - 1];
    
    vector<vector<int>> adj(n + 1, vector<int>());
    vector<vector<int>> re_adj(n + 1, vector<int>());
    while(m--) {
        int u, v; cin >> u >> v;
        adj[u].pb(v);
        re_adj[v].pb(u);
    }

    vector<int> topo;
    vector<int> vis(n + 1, 0);
    auto dfs = [&](auto dfs, int u) -> void {
        vis[u] = 1;
        for(int v : adj[u]) {
            if (vis[v] == 1) {
                cout << -1;
                exit(0);
            }
            if (vis[v] != 0) continue;
            dfs(dfs, v);
        }
        topo.pb(u);
        vis[u] = 2;
    };

    ff(i, 1, n) if (vis[i] == 0) dfs(dfs, i);
    reverse(topo.begin(), topo.end());

    int ans = 0;
    int num_char = (int)('z' - 'a' + 1);
    vector<vector<int>> dp(num_char, vector<int>(n + 1));
    ff(i, 0, num_char - 1) {
        for(int u : topo) {
            for(int v : re_adj[u]) dp[i][u] = max(dp[i][u], dp[i][v]);
            dp[i][u] += (a[u] - 'a' == i);
            ans = max(ans, dp[i][u]);
        }
    }
    cout << ans;
    return 0;
}