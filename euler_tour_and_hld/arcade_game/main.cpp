#include <bits/stdc++.h>
#define ll long long
#define endl '\n'
#define ff(i, x, y) for(int i = x; i <= y; i++)
#define fi first
#define se second
#define pb push_back

using namespace std;

struct Egde {
    int u, v, w;
};

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n; cin >> n;
    vector<Egde> edges(n);
    vector<vector<int>> a(n + 1, vector<int>());
    ff(i, 1, n - 1) {
        int u, v, w; cin >> u >> v >> w;
        edges[i] = {u, v, w};
        a[u].pb(v);
        a[v].pb(u);
    }
    
    // hld
    vector<int> sz(n + 1, 1), d(n + 1, 1), par(n + 1);
    auto dfs = [&](auto dfs, int u) -> void {
        for(int v : a[u]) {
            if (v == par[u]) continue;
            par[v] = u;
            d[v] = d[u] + 1;
            dfs(dfs, v);
            sz[u] += sz[v];
        }
    };
    dfs(dfs, 1);
    vector<int> chain_id(n + 1), chain_head(n + 1, -1), pos(n + 1), arr(n + 1);
    vector<int> in(n + 1), out(n + 1);
    int timer = 0;
    int cur_chain = 1, cur_pos = 0;
    auto hld = [&](auto hld, int u) -> void {
        in[u] = ++timer;
        if (chain_head[cur_chain] == -1) chain_head[cur_chain] = u;
        chain_id[u] = cur_chain;
        cur_pos++;
        pos[u] = cur_pos;
        arr[cur_pos] = u;
        int big_child = -1;
        for(int v : a[u]) {
            if (v == par[u]) continue;
            if (big_child == -1 || sz[big_child] < sz[v]) big_child = v;
        }
        if (big_child != -1) hld(hld, big_child);
        for(int v : a[u]) {
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
        if (in[u] < in[v]) swap(edges[i].u, edges[i].v);
        weight[edges[i].u] = w;
    }

    vector<ll> st(4 * (n + 1));

    auto build = [&](auto build, int id, int l, int r) -> void {
        if (l == r) {
            st[id] = weight[arr[l]];
            return;
        }
        int mid = (l + r) / 2;
        build(build, id * 2, l, mid);
        build(build, id * 2 + 1, mid + 1, r);
        st[id] = st[id * 2] + st[id * 2 + 1];
    };
    build(build, 1, 1, n);

    auto update = [&](auto update, int id, int l, int r, int pos, int val) -> void {
        if (l > pos || r < pos) return;
        if (l == r) {
            st[id] = val;
            return;
        }
        int mid = (l + r) / 2;
        update(update, id * 2, l, mid, pos, val);
        update(update, id * 2 + 1, mid + 1, r, pos, val);
        st[id] = st[id * 2] + st[id * 2 + 1];
    };

    auto get = [&](auto get, int id, int l, int r, int u, int v) -> ll {
        if (l > v || r < u) return 0;
        if (l >= u && r <= v) return st[id];
        int mid = (l + r) / 2;
        ll get1 = get(get, id * 2, l, mid, u, v);
        ll get2 = get(get, id * 2 + 1, mid + 1, r, u, v);
        return get1 + get2;
    };

    auto query = [&](int u, int v) -> ll {
        int lca = get_lca(u, v);
        ll ans = 0;
        while(chain_id[u] != chain_id[lca]) {
            ans += get(get, 1, 1, n, pos[chain_head[chain_id[u]]], pos[u]);
            u = par[chain_head[chain_id[u]]];
        }
        while(chain_id[v] != chain_id[lca]) {
            ans += get(get, 1, 1, n, pos[chain_head[chain_id[v]]], pos[v]);
            v = par[chain_head[chain_id[v]]];
        }
        if (d[u] < d[v]) swap(u, v);
        return ans + get(get, 1, 1, n, pos[v], pos[u]) - weight[lca];
    };
    
    int q; cin >> q;
    while(q--) {
        int type; cin >> type;
        if (type == 1) {
            int _i, _w; cin >> _i >> _w;
            int _pos = edges[_i].u;
            weight[_pos] = _w;
            update(update, 1, 1, n, pos[_pos], weight[_pos]);
        } else if (type == 2) {
            int _a, _b; cin >> _a >> _b;
            cout << query(_a, _b) << endl;
        }
    }

    return 0;
}