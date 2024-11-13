// https://oj.vnoi.info/problem/nkflow
#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

const int INF = (int)1e9;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n, m, s, t; cin >> n >> m >> s >> t;
    vector<vector<int>> c(n + 1, vector<int>(n + 1));
    vector<vector<int>> f(n + 1, vector<int>(n + 1));
    vector<vector<int>> a(n + 1, vector<int>());
    while(m--) {
        int u, v; cin >> u >> v;
        cin >> c[u][v];
        a[u].push_back(v);
        a[v].push_back(u);
    }

    vector<int> d(n + 1);

    auto bfs = [&]() -> void {
        for(int &x : d) x = INF;
        d[s] = 0;
        queue<int> q;
        q.push(s);
        while(q.size()) {
            int u = q.front(); q.pop();
            for(int v : a[u]) {
                if (d[v] != INF) continue;
                if (c[u][v] - f[u][v] == 0) continue;
                d[v] = d[u] + 1;
                q.push(v);
            }
        }
    };

    vector<int> cur_vertex_id(n + 1);
    auto dfs = [&](auto dfs, int u, int cur_delta) -> int {
        if (cur_delta == 0) return 0;
        if (u == t) return cur_delta;
        for(; cur_vertex_id[u] < a[u].size(); cur_vertex_id[u]++) {
            int v = a[u][cur_vertex_id[u]];
            if (d[v] != d[u] + 1) continue;
            if (c[u][v] - f[u][v] == 0) continue;

            int delta = dfs(dfs, v, min(c[u][v] - f[u][v], cur_delta));
            if (delta == 0) continue;
            f[u][v] += delta;
            f[v][u] -= delta;
            return delta;
        }
        return 0;
    };

    int max_flow = 0;
    while(true) {
        bfs();
        if (d[t] == INF) break;
        for(int &x : cur_vertex_id) x = 0;
        while(true) {
            int delta = dfs(dfs, s, INF);
            if (delta != 0) max_flow += delta;
            else break;
        }
    }
    cout << max_flow;
    return 0;
}