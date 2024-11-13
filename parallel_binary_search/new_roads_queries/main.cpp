// https://cses.fi/problemset/task/2101
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
    int n, m, q; cin >> n >> m >> q;
    vector<pair<int,int>> a(m + 1), queries(q + 1);
    ff(i, 1, m) cin >> a[i].fi >> a[i].se;
    ff(i, 1, q) cin >> queries[i].fi >> queries[i].se;
 
    vector<int> p(n + 1), sz(n + 1);
 
    vector<int> l(q + 1), r(q + 1);
    ff(i, 1, q) l[i] = 1, r[i] = m;
    
    auto find_p = [&](auto find_p, int u) -> int {
        if (u == p[u]) return u;
        return p[u] = find_p(find_p, p[u]);
    };
    auto union_sets = [&](int u, int v) -> bool {
        u = find_p(find_p, u);
        v = find_p(find_p, v);
        if (u == v) return true;
        if (sz[v] > sz[u]) swap(u, v);
        sz[u] += sz[v];
        p[v] = u;
        return true;
    };
    auto same = [&](int u, int v) -> bool {
        return find_p(find_p, u) == find_p(find_p, v);
    };
    
    bool any = true;
    vector<int> ans(q + 1, -1);
    while(true) {
        any = false;
        vector<vector<int>> cands(m + 1, vector<int>());
        ff(i, 1, q) {
            if (l[i] > r[i]) continue;
            cands[(l[i] + r[i]) / 2].pb(i);
            any = true;
        }
        if (any == false) break;
        ff(i, 1, n) p[i] = i, sz[i] = 1;
        ff(i, 1, m) {
            union_sets(a[i].fi, a[i].se);
            for(int cand : cands[i]) {
                if (same(queries[cand].fi, queries[cand].se)) {
                    ans[cand] = i;
                    r[cand] = i - 1;   
                } else {
                    l[cand] = i + 1;
                }
            }
        }
        cands.clear();
    }
    ff(i, 1, q) {
        if (queries[i].fi != queries[i].se) cout << ans[i] << endl;
        else cout << 0 << endl;
    }
    return 0;
}
