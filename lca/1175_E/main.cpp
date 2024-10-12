// https://codeforces.com/contest/1175/problem/E
#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

const int N = (int)2e5;
const int M = (int)2e5;
const int LOG = 20;

struct Range {
    int l, r, idx;
};

struct Query {
    int x, y;
};

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n, m;
    cin >> n >> m;

    vector<Range> ranges(n);
    for(int i = 0; i < n; i++) {
        cin >> ranges[i].l >> ranges[i].r;
    }
    sort(ranges.begin(), ranges.end(), [&](const Range &x, const Range &y) -> bool {
        if (x.l != y.l) {
            return x.l < y.l;
        } else {
            return x.r < y.r;
        }
    });

    vector<int> max_r(ranges.size(), 0);
    max_r[0] = ranges[0].r;
    for(int i = 1; i < ranges.size(); i++) {
        max_r[i] = max(max_r[i - 1].r, ranges[i].r);
    }

    vector<int> root(N + 1, -1);
    vector<vector<int>> a(N + 1, vector<int>());
    int cur_index = 0;
    while(true) {
        int cur_root = ranges[cur_index].r;
        root[cur_root] = cur_root;
        a[0].push_back(cur_root);
        int break_index = -1;
        for(int i = cur_index + 1; i < ranges.size(); i++) {
            if (ranges[i].l <= ranges[i - 1].r) {
                root[ranges[i].r] = cur_root;
                a[ranges[i - 1].r].push_back(ranges[i].r);
            } else {
                break_index = i;
                break;
            }
        }
        if (break_index == -1) {
            break;
        } else {
            cur_index = break_index;
        }
    }

    vector<int> h(N + 1, 0);
    vector<vector<int>> p(N + 1, vector<int>(LOG + 1, 0));
    auto dfs = [&](auto dfs, int u) -> void {
        for(int v : a[u]) {
            if (v != p[u][0]) {
                p[v][0] = u;
                h[v] = h[u] + 1;
                dfs(dfs, v);
            }
        }
    };
    dfs(dfs, 0);
    for(int j = 1; j <= LOG; j++) {
        for(int i = 0; i <= N; i++) {
            p[i][j] = p[p[i][j - 1]][j - 1];
        }
    }
    auto lca = [&](auto lca, int u, int v) -> int {
        if (h[u] < h[v])
            return lca(lca, v, u);
        for(int i = LOG; i >= 0; i--) {
            if (h[p[u][i]] >= h[v]) {
                u = p[u][i];
            }
        }
        if (u == v) return u;
        for(int i = LOG; i >= 0; i--) {
            if (p[u][i] != p[v][i]) {
                u = p[u][i];
                v = p[v][i];
            }
            return p[u][0];
        }
    };

    while(m--) {
        int x, y;
        cin >> x >> y;
        int l = 0, r = ranges.size() - 1, res = -1;
        while(l <= r) {
            int m = (l + r) / 2;
            if (ranges[m].l <= y) {
                res = m;
                
            }
        }
    }
    return 0;
}