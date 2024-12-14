// https://cses.fi/problemset/result/11374694/
#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n, m; cin >> n >> m;
    auto check_sub1 = [&]() -> bool {
        return m <= 20;
    };
    vector<pair<int,int>> edges;
    for(int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        edges.push_back({u, v});
    }
    auto solve_sub1 = [&]() -> void {
        vector<vector<int>> adj(n + 1, vector<int>());
        for(int mask = 0; mask < (1 << m); mask++) {
            for(int i = 1; i <= n; i++) adj[i].clear();
            for(int i = 0; i < m; i++) {
                auto[u, v] = edges[i];
                if (mask & (1 << i)) {
                    adj[u].push_back(v);
                } else {
                    adj[v].push_back(u);
                }
            }
                    vector<int> vis(n + 1, 0);
            bool check = true;
            auto dfs = [&](auto dfs, int u) -> void {
                vis[u] = 1;
                for(int v : adj[u]) {
                    if (vis[v] == 1) {
                        check = false;
                        return;
                    } else if (vis[v] == 0) {
                        dfs(dfs, v);
                    }
                }
                vis[u] = 2;
            };
            for(int i = 1; i <= n; i++) {
                if (vis[i] == 0) {
                    dfs(dfs, i);
                }
            }
            if (check == false) continue;
            for(int i = 0; i < m; i++) {
                auto[u, v] = edges[i];
                if (mask & (1 << i)) {
                    cout << u << ' ' << v << endl;
                } else {
                    cout << v << ' ' << u << endl;
                }
            }
            break;
        }
    };
    auto magic = [&]() -> void {
        for(auto[u, v] : edges) {
            if (u > v) swap(u, v);
            cout << u << ' ' << v << endl;
        }
    };
    if (check_sub1()) {
        solve_sub1();
    } else {
        magic();
    }
    return 0;
}