// https://oj.vnoi.info/problem/graph_
#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n, m; cin >> n >> m;
    vector<vector<int>> a(n + 1);
    while(m--) {
        int u, v; cin >> u >> v;
        a[u].push_back(v);
        a[v].push_back(u);
    }
    vector<int> low(n + 1, 0), num(n + 1, 0), tail(n + 1, 0);
    int timer = 0;
    int bridge = 0, joint = 0, scc = 0;
    vector<int> jointed(n + 1, 0), st;
    vector<bool> deleted(n + 1, false);
    auto dfs = [&](auto dfs, int u, int p) -> void {
        int num_child = 0;
        low[u] = num[u] = ++timer;
        for(int v : a[u]) {
            if (v == p) continue;
            if (!num[v]) {
                dfs(dfs, v, u);
                low[u] = min(low[u], low[v]);
                if (low[v] == num[v]) bridge++;
                num_child++;
                if (u == p) {
                    if (num_child > 1)
                        jointed[u] = 1;
                } else if (low[v] >= num[u]) jointed[u] = 1;
            } else {
                low[u] = min(low[u], num[v]);
            }
        }
        if (low[u] == num[u]) {
            scc++; // num component
            int v;
            do {
                v = st.back();
                st.pop_back();
                deleted[v] = true;
            }
            while (v != u);
        }
        tail[u] = timer;
    };
    for(int i = 1; i <= n; i++) if (num[i] == 0) dfs(dfs, i, i);
    for(int i = 1; i <= n; i++) joint += jointed[i];
    cout << joint << ' ' << bridge;
    return 0;
}