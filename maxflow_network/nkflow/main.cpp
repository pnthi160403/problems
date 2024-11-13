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

    vector<int> p(n + 1);

    auto dfs = [&](auto dfs, int u) -> void {
        for(int v : a[u]) {
            if (p[v] != 0) continue;
            if (f[u][v] - c[u][v] == 0) continue;
            p[v] = u;
            dfs(dfs, v);
        }
    };

    int max_flow = 0;
    auto incFlow = [&]() -> void {
        int v = t;
        int delta = INF;
        while(v != s) {
            int u = p[v];
            delta = min(delta, c[u][v] - f[u][v]);
            v = u;
        }
        max_flow += delta;
        v = t;
        while(v != s) {
            int u = p[v];
            f[u][v] += delta;
            f[v][u] -= delta;
            v = u;
        }
    };

    do {
        for(int &x : p) x = 0;
        p[s] = -1;
        dfs(dfs, s);
        if (p[t] != 0) incFlow();
    } while(p[t] != 0);

    cout << max_flow;
    return 0;
}