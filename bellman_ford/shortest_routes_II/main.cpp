// https://cses.fi/problemset/task/1672/
// TLE
#include <bits/stdc++.h>
#define ll long long
#define int ll
#define endl '\n'

using namespace std;

struct Edge {
    int u, v, cost;
};

const ll INF = (ll)1e18;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n, m, q;
    cin >> n >> m >> q;
    vector<Edge> a;
    for(int i = 0; i < m; i++) {
        int u, v, cost;
        cin >> u >> v >> cost;
        a.push_back({u, v, cost});
        a.push_back({v, u, cost});
    }
    auto bellman_ford = [&](int start) -> vector<ll> {
        vector<ll> d(n + 1, INF);
        d[start] = 0;
        for(int i = 1; i <= n - 1; i++)
            for(Edge e : a)
                if (d[e.u] != INF) d[e.v] = min(d[e.v], d[e.u] + e.cost);
        return d;
    };
    vector<vector<ll>> d(n + 1, vector<ll>(n + 1));
    for(int i = 1; i <= n; i++)
        d[i] = bellman_ford(i);
    while(q--) {
        int u, v; cin >> u >> v;
        cout << (d[u][v] == INF ? -1 : d[u][v]) << endl;
    }
    return 0;
}