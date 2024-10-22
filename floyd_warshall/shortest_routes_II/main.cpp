// https://cses.fi/problemset/task/1672/
#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

const ll INF = (ll)1e18;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n, m, q; cin >> n >> m >> q;
    vector<vector<ll>> d(n + 1, vector<ll>(n + 1, INF));
    for(int i = 0; i < m; i++) {
        int u, v, cost; cin >> u >> v >> cost;
        d[u][v] = d[v][u] = min(d[u][v], (ll)cost);
    }
    for(int i = 1; i <= n; i++) d[i][i] = 0;
    for(int k = 1; k <= n; k++)
        for(int i = 1; i <= n; i++) 
            for(int j = 1; j <= n; j++)
                if (d[i][k] != INF && d[k][j] != INF)
                    d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
    while(q--) {
        int u, v; cin >> u >> v;
        cout << (d[u][v] == INF ? -1 : d[u][v]) << endl;
    }
    return 0;
}