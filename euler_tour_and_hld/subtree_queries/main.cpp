// https://oj.vnoi.info/problem/euler_f
#include <bits/stdc++.h>
#define ll long long
#define endl '\n'
#define ff(i, x, y) for(int i = x; i <= y; i++)
#define fi first
#define se second
#define pb push_back

using namespace std;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n, q; cin >> n >> q;
    vector<int> a(n + 1);
    ff(i, 1, n) cin >> a[i];;
    vector<vector<int>> adj(n + 1, vector<int>());
    ff(i, 2, n) {
        int u, v; cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
    }

    vector<int> sz(n + 1, 1);
    vector<int> depth(n + 1, 1);
    vector<int> par(n + 1, -1);

    auto dfs = [&](auto dfs, int u) -> void {
        for (int v : adj[u]) {
            if (v == par[u]) continue;
            par[v] = u;
            depth[v] = depth[u] + 1;
            dfs(dfs, v);
            sz[u] += sz[v];
        }
    };
    dfs(dfs, 1);

    vector<int> chain_head(n + 1, -1), chain_id(n + 1), pos(n + 1), arr(n + 1);
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
        return depth[u] < depth[v] ? u : v;
    };

    vector<ll> st(4 * (n + 1));
    auto build = [&](auto build, int id, int l, int r) -> void {
        if (l == r) {
            st[id] = a[arr[l]];
            return;
        }
        int mid = (l + r) / 2;
        build(build, id * 2, l, mid);
        build(build, id * 2 + 1, mid + 1, r);
        st[id] = st[id * 2] + st[id * 2 + 1];
    };
    build(build, 1, 1, n);
    auto update = [&](auto update, int id, int l, int r, int pos, int val) -> void {
        if (pos < l || pos > r) return;
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
    
    while(q--) {
        int type; cin >> type;
        if (type == 1) {
            int _pos, _val; cin >> _pos >> _val;
            a[_pos] = _val;
            update(update, 1, 1, n, pos[_pos], _val);
        } else if (type == 2) {
            int _pos; cin >> _pos;
            cout << get(get, 1, 1, n, in[_pos], out[_pos]) << endl;
        }
    }
    return 0;
}