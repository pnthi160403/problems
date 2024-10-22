#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> a(n + 1, vector<int>());
    while(m--) {
        int u, v; cin >> u >> v;
        a[u].push_back(v);
        a[v].push_back(u);
    }

    vector<int> color(n + 1, -1);
    auto dfs = [&](auto dfs, int u) -> bool {
        if (color[u] == -1) color[u] = 0;
        for(int v : a[u]) {
            if (color[v] == -1) {
                color[v] = 1 - color[u];
                if (!dfs(dfs, v)) return false;
            } else if (color[v] == color[u]) return false;
        }
        return true;
    };
    bool ok = true;
    for(int i = 1; i <= n; i++) {
        if (color[i] == -1) {
            if (!dfs(dfs, i)) {
                ok = false;
                break;
            }
        }
    }
    if (ok == false) cout << "IMPOSSIBLE";
    else for(int i = 1; i <= n; i++) cout << color[i] + 1 << ' ';
    return 0;
}