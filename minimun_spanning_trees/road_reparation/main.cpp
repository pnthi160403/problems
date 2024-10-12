// https://cses.fi/problemset/task/1675
#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

struct Road {
    int u, v, cost;
};

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n, m;
    cin >> n >> m;
    vector<Road> a;
    for(int i = 0; i < m; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        u--, v--;
        a.push_back({u, v, c});
    }
    sort(a.begin(), a.end(), [&](const Edge &x, const Edge &y) -> bool {
        return x.cost < y.cost;
    });
    vector<int> par(n, -1);
    for(int i = 0; i < n; i++)  
        par[i] = i;
    auto find_p = [&](auto find_p, int u) -> int {
        if (u == par[u])
            return u;
        return par[u] = find_p(find_p, u);
    };
    vector<int> sz(n, 1);
    auto union_sets = [&](int u, int v) -> bool {
        u = find_p(find_p, u);
        v = find_p(find_p, v);
        if (u == v)
            return false;
        if (sz[u] < sz[v])
            swap(u, v);
        par[v] = u;
        sz[u] += sz[v];
        return true;
    };
    int cnt = 0;
    ll min_cost = 0;
    for(Road road : a) {
        if (union_sets(road.u, road.v)) {
            min_cost += road.cost;
            cnt++;
        }
    }
    if (cnt != n - 1) {
        cout << "IMPOSSIBLE";
    } else {
        cout << min_cost;
    }
    return 0;
}