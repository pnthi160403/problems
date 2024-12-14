// https://oj.vnoi.info/problem/votree
#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

const int LOG = 25;
const int N = (int)7e4;
vector<vector<int>> p(N + 1, vector<int>(LOG + 1, 1));
vector<int> h(N + 1, 1);

int lca(int u, int v) {
    if (h[u] < h[v]) swap(u, v);
    int i = LOG;
    while(true) {
        int pu = p[u][i];
        if (h[pu] >= h[v]) {
            u = pu;
        }
        if (h[u] == h[v]) break;
        i--;
        if (i < 0) break;
    }
    if (u == v) return u;
    i = LOG;
    while(true) {
        int pu = p[u][i];
        int pv = p[v][i];
        if (pu != pv) {
            u = pu;
            v = pv;
        }
        i--;
        if (i < 0) break;
    }
    return p[u][0];
};

struct ST {
    int n;
    vector<int> st;
    void init(int _n) {
        n = _n;
        st.resize(4 * n);
    }
    int combine(int left, int right) {
        if (left == -1) return right;
        if (right == -1) return left;
        int res = lca(left, right);
        return res;
    }
    void update(int id, int l, int r, int pos, int val) {
        if (l > pos || r < pos) return;
        if (l == r) {
            st[id] = val;
            return;
        }
        int mid = (l + r) / 2;
        update(id * 2, l, mid, pos, val);
        update(id * 2 + 1, mid + 1, r, pos, val);
        st[id] = combine(st[id * 2], st[id * 2 + 1]);
    }
    int get(int id, int l, int r, int u, int v) {
        if (l > v || r < u) return -1;
        if (l >= u && r <= v) return st[id];
        int mid = (l + r) / 2;
        int g1 = get(id * 2, l, mid, u, v);
        int g2 = get(id * 2 + 1, mid + 1, r, u, v);
        return combine(g1, g2);
    }
};

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n, q; cin >> n >> q;
    vector<vector<int>> adj(n + 1, vector<int>());
    for(int i = 1; i <= n - 1; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    h[0] = 0;
    auto dfs = [&](auto dfs, int u, int par) -> void {
        p[u][0] = par;
        for(int v : adj[u]) {
            if (v == par) continue;
            h[v] = h[u] + 1;
            dfs(dfs, v, u);
        }
    };
    dfs(dfs, 1, 0);
    for(int j = 1; j <= LOG; j++) {
        for(int i = 1; i <= n; i++) {
            p[i][j] = p[p[i][j - 1]][j - 1];
        }
    }
    ST st;
    st.init(n);
    for(int i = 1; i <= n; i++) st.update(1, 1, n, i, i);
    while(q--) {
        int u, v; cin >> u >> v;
        cout << st.get(1, 1, n, u, v) << endl;
    }
    return 0;
}