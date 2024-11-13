#include <bits/stdc++.h>
#define ll long long
#define endl '\n'
#define ff(i, x, y) for(int i = x; i <= y; i++)
#define fi first
#define se second
#define pb push_back
#define out(x) cerr << x << endl;

using namespace std;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n, m, q; cin >> n >> m >> q;
    vector<vector<int>> queries(m + 1, vector<int>());
    vector<int> l(m + 1, 1), r(m + 1, q), ans(m + 1, -1);
    ff(i, 1, n) {
        int x; cin >> x;
        queries[x].pb(i);
    }
    vector<pair<int,int>> a(q + 1);
    ff(i, 1, q) cin >> a[i].fi >> a[i].se;
    vector<int> p(n + 1), sz(n + 1);
    auto find_p = [&](auto find_p, int u) -> int {
        if (u == p[u]) return u;
        return p[u] = find_p(find_p, p[u]);
    };
    auto union_sets = [&](int u, int v) -> bool {
        u = find_p(find_p, u);
        v = find_p(find_p, v);
        if (u == v) return false;
        if (sz[v] < sz[u]) swap(u, v);
        sz[u] += sz[v];
        p[v] = u;
        return true;
    };
    auto same = [&](int u, int v) -> bool {
        return find_p(find_p, u) == find_p(find_p, v);
    };
    auto reset = [&]() -> void {
        ff(i, 1, n) p[i] = i, sz[i] = 1;
    };
    bool any = true;
    while(true) {
        any = false;
        vector<vector<int>> cands(q + 1, vector<int>());
        ff(i, 1, m) {
            if (l[i] > r[i]) continue;
            cands[(l[i] + r[i]) / 2].pb(i);
            any = true;
        }
        if (any == false) break;
        reset();
        ff(i, 1, q) {
            union_sets(a[i].fi, a[i].se);
            for(int j : cands[i]) {
                int par = -1;
                bool ok = true;
                for(int x : queries[j]) {
                    if (par == -1) {
                        par = find_p(find_p, x);
                        continue;
                    } else if (same(par, x) == false) ok = false;
                }
                if (ok) {
                    ans[j] = i;
                    r[j] = i - 1;
                } else l[j] = i + 1;
            }
        }
        cands.clear();
    }
    ff(i, 1, m) {
        if (queries[i].size() == 1) cout << 0 << endl;
        else cout << ans[i] << endl;
    }
    return 0;
}