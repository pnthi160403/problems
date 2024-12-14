#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

struct Query {
    int x, y, z;
};

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n, m; cin >> n >> m;
    vector<int> p(n + 1), sz(n + 1, 1);
    for(int i = 1; i <= n; i++) {
        p[i] = i;
        sz[i] = 1;
    }
    vector<pair<int,int>> a;
    for(int i = 0; i < m; i++) {
        int x, y; cin >> x >> y;
        a.push_back({x, y});
    }
    int q; cin >> q;
    vector<Query> queries;
    while(q--) {
        int x, y, z; cin >> x >> y >> z;
        queries.push_back({x, y, z});
    }
    auto reset = [&]() -> void {
        for(int i = 1; i <= n; i++) {
            p[i] = i;
            sz[i] = 1;
        }
    };
    auto find_p = [&](auto find_p, int x) -> int {
        if (x == p[x]) return x;
        return p[x] = find_p(find_p, p[x]);
    };
    auto union_sets = [&](int u, int v) -> bool {
        u = find_p(find_p, u);
        v = find_p(find_p, v);
        if (u == v) return false;
        if (sz[u] < sz[v]) swap(u, v);
        sz[u] += sz[v];
        p[v] = u;
        return true;
    };
    vector<int> l(queries.size(), 0), r(queries.size(), a.size() - 1);
    vector<int> ans(queries.size(), a.size());
    while(true) {
        bool any = false;
        vector<vector<int>> cands(a.size(), vector<int>());
        for(int i = 0; i < queries.size(); i++) {
            if (l[i] <= r[i]) {
                int mid = (r[i] + l[i]) / 2;
                cands[mid].push_back(i);
                any = true;
            }
        }
        if (any == false) break;
        reset();
        for(int i = 0; i < a.size(); i++) {
            union_sets(a[i].first, a[i].second);
            for(int j = 0; j < cands[i].size(); j++) {
                auto[x, y, z] = queries[cands[i][j]];
                x = find_p(find_p, x);
                y = find_p(find_p, y);
                if (x == y) {
                    if (sz[x] >= z) {
                        ans[cands[i][j]] = i + 1;
                        r[cands[i][j]] = i - 1;
                    } else {
                        l[cands[i][j]] = i + 1;
                    }
                } else {
                    if (sz[x] + sz[y] >= z) {
                        ans[cands[i][j]] = i + 1;
                        r[cands[i][j]] = i - 1;
                    } else {
                        l[cands[i][j]] = i + 1;
                    }
                }
            }
        }
        cands.clear();
    }
    for(int x : ans) cout << x << endl;
    return 0;
}