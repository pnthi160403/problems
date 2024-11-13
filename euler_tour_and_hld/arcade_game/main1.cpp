#include <bits/stdc++.h>
#define ll long long
#define endl '\n'
#define ff(i, x, y) for(int i = x; i <= y; i++)
#define fi first
#define se second
#define pb push_back

using namespace std;

struct Edge {
    int u, v, w;
};

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n; cin >> n;
    vector<vector<int>> adj(n + 1);
    vector<Edge> edges(n);
    ff(i, 1, n - 1) {
        int u, v, w; cin >> u >> v >> w;
        edges[i] = {u, v, w};
        adj[u].pb(v);
        adj[v].pb(u);
    }

    // hld
    vector<int> sz(n + 1, 1), d(n + 1, 1), par(n + 1, -1);
    auto dfs = [&](auto dfs, int u) -> void {
        for(int v : adj[u]) {
            if (v == par[u]) continue;
            par[v] = u;
            d[v] = d[u] + 1;
            dfs(dfs, v);
            sz[u] += sz[v];
        }
    };
    dfs(dfs, 1);

    vector<int> chain_id(n + 1, -1), chain_head(n + 1, -1), pos(n + 1), arr(n + 1);
    vector<int> in(n + 1), out(n + 1);
    int cur_chain = 1, cur_pos = 0, timer = 0;
    auto hld = [&](auto hld, int u) -> void {
        in[u] = ++timer;
        if (chain_head[cur_chain] == -1) chain_head[cur_chain] = u;
        chain_id[u] = cur_chain;
        cur_pos++;
        pos[u] = cur_pos;
        arr[cur_pos] = u;
        int big_child = -1;
        for(int v : adj[u]) {
            if (v == par[u]) continue;
            if (big_child == -1 || sz[big_child] < sz[v]) big_child = v;
        }
        if (big_child != -1) hld(hld, big_child);
        for(int v : adj[u]) {
            if (v == par[u] || v == big_child) continue;
            cur_chain++;
            hld(hld, v);
        }
        out[u] = timer;
    };
    hld(hld, 1);

    auto get_lca = [&](int u, int v) -> int {
        while(chain_id[u] != chain_id[v]) {
            if (chain_id[u] < chain_id[v]) swap(u, v);
            u = par[chain_head[chain_id[u]]];
        }
        return d[u] < d[v] ? u : v;
    };

    vector<int> weight(n + 1);
    ff(i, 1, n - 1) {
        auto[u, v, w] = edges[i];
        if (in[u] < in[v]) swap(u, v);
        edges[i] = {u, v, w};
        weight[u] = w;
    }

    // fenwick
    vector<ll> bit(n + 2, 0);

    auto add = [&](int x, int val) -> void {
        for(int i = x; i <= n; i += i & -i) bit[i] += val;
    };

    auto get = [&](int x) -> ll {
        ll res = 0;
        for(int i = x; i >= 1; i -= i & -i) res += bit[i];
        return res;
    };

    auto get_range = [&](int l, int r) -> ll {
        return get(r) - get(l - 1);
    };

    auto query = [&](int u, int v) -> ll {
        int lca = get_lca(u, v);
        ll ans = 0;
        while(chain_id[u] != chain_id[lca]) {
            ans += get_range(pos[chain_head[chain_id[u]]], pos[u]);
            u = par[chain_head[chain_id[u]]];
        }
        while(chain_id[v] != chain_id[lca]) {
            ans += get_range(pos[chain_head[chain_id[v]]], pos[v]);
            v = par[chain_head[chain_id[v]]];
        }
        if (d[u] < d[v]) swap(u, v);
        return ans + get_range(pos[v], pos[u]) - weight[lca];
    };

    ff(i, 1, n) add(i, weight[arr[i]]);

    // query
    int q; cin >> q;
    while(q--) {
        int type; cin >> type;
        if (type == 1) {
            int _i, _w; cin >> _i >> _w;
            auto[u, v, w] = edges[_i];
            add(pos[u], _w - w);
            edges[_i] = {u, v, _w};
            weight[u] = _w;
        } else {
            int _a, _b; cin >> _a >> _b;
            cout << query(_a, _b) << endl;
        }
    }

    return 0;
}