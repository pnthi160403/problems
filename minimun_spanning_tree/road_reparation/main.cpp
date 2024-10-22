// https://cses.fi/problemset/task/1675
#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

struct Edge {
    int u, v, cost;
};

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n, m; cin >> n >> m;
    vector<Edge> a;
    for(int i = 0; i < m; i++) {
        int u, v, cost; cin >> u >> v >> cost;
        a.push_back({u, v, cost});
    }
    sort(a.begin(), a.end(), [&](Edge x, Edge y) -> bool {
        if (x.cost != y.cost) return x.cost < y.cost;
        if (x.u != y.u) return x.u < y.u;
        return x.v < y.v;
    });
    vector<int> p(n + 1), sz(n + 1, 1);
    for(int i = 1; i <= n; i++) p[i] = i;
    auto find_p = [&](auto find_p, int u) -> int {
        if (u == p[u]) return u;
        return p[u] = find_p(find_p, p[u]);
    };
    auto union_sets = [&](int u, int v) -> bool {
        u = find_p(find_p, u);
        v = find_p(find_p, v);
        if (v == u) return false;
        if (sz[v] > sz[u]) swap(u, v);
        sz[u] += sz[v];
        p[v] = u;
        return true;
    };
    ll min_cost = 0;
    for(Edge e : a) {
        auto[u, v, cost] = e;
        if (union_sets(u, v)) min_cost += cost;
    }
    int max_size = 0;
    for(int i = 1; i <= n; i++) max_size = max(max_size, sz[find_p(find_p, i)]);
    if (max_size == n) cout << min_cost;
    else cout << "IMPOSSIBLE";
    return 0;
}