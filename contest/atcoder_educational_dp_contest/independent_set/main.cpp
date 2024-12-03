#include <bits/stdc++.h>
#define ll long long
#define int ll
#define endl '\n'

using namespace std;

const int MOD = (int)1e9 + 7;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n; cin >> n;
    vector<vector<int>> adj(n + 1, vector<int>());
    for(int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<int> dpw(n + 1), dpb(n + 1);
    auto dfs = [&](auto dfs, int u, int p) -> void {
        int cnt_w = 1, cnt_b = 1;
        for(int v : adj[u]) {
            if (v == p) continue;
            dfs(dfs, v, u);
            cnt_w = (cnt_w * (dpw[v] + dpb[v])) % MOD;
            cnt_b = (cnt_b * dpw[v]) % MOD;
        }
        dpw[u] = cnt_w;
        dpb[u] = cnt_b;
    };
    dfs(dfs, 1, -1);
    cout << (dpw[1] + dpb[1]) % MOD;
    return 0;
}