// https://oj.vnoi.info/problem/icpc22_national_a
#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

struct Query {
    int u, v, id;
};

struct Operation {
    char type;
    int u, v, id;
};

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n, q; cin >> n >> q;
    vector<vector<Query>> queries(q + 1);
    vector<Operation> operations;
    for(int i = 0; i < q; i++) {
        char type; cin >> type;
        if (type == 'Q') {
            int s, u, v; cin >> s >> u >> v;
            queries[s].push_back({u, v, i});
        } else if (type != 'C') {
            int u, v; cin >> u >> v;
            operations.push_back({type, u, v, i});
        } else {
            operations.push_back({type, -1, -1, i});
        }
    }
    vector<int> p(n + 1), sz(n + 1, 1);
    for(int i = 1; i <= n; i++) p[i] = i;
    auto find_p = [&](auto find_p, int u) -> int {
        if (u == p[u]) return u;
        return p[u] = find_p(find_p, p[u]);
    };
    auto union_sets = [&](int u, int v) -> int {
        u = find_p(find_p, u);
        v = find_p(find_p, v);
        if (u == v) return false;
        if (sz[v] > sz[u]) swap(u, v);
        sz[u] += sz[v];
        p[v] = u;
        return true;
    };
    auto same = [&](int u, int v) -> int {
        if (find_p(find_p, u) == find_p(find_p, v)) return 1;
        return 0;
    };
    vector<int> ans(q + 1, -1);
    for(Query q : queries[0])
        ans[q.id] = 0;
    int s = 0;
    for(Operation o : operations) {
        if (o.type == 'A') {
            union_sets(o.u, o.v);
        } else if (o.type == '?') {
            ans[o.id] = same(o.u, o.v);
        } else if (o.type == 'C') {
            s++;
            for(Query q : queries[s])
                ans[q.id] = same(q.u, q.v);
        }
    }
    for(int x : ans) if (x != -1) cout << (x == 1 ? 'Y' : 'N');
    return 0;
}