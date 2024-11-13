// https://codeforces.com/contest/600/problem/E
#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n; cin >> n;
    vector<int> color(n + 1);
    for(int i = 1; i <= n; i++) cin >> color[i];
    vector<vector<int>> a(n + 1, vector<int>());
    for(int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        a[u].push_back(v);
        a[v].push_back(u);
    }
    vector<int> sz(n + 1, -1);
    auto calc_height = [&](auto calc_height, int u, int p) -> void {
        if (sz[u] == -1) sz[u] = 1;
        for(int v : a[u]) {
            if (v == p) continue;
            calc_height(calc_height, v, u);
            sz[u] += sz[v];
        }
    };
    for(int i = 1; i <= n; i++) if (sz[i] == -1) calc_height(calc_height, i, -1);

    // dsu on tree
    vector<int> cnt(n + 1, 0);
    vector<ll> ans(n + 1, 0);
    vector<bool> big(n + 1, false);
    vector<int> cnt_of_cnt(n + 1, 0);
    vector<ll> sum(n + 1, 0);
    set<int> s;

    auto add = [&](auto add, int u, int p, int del) -> void {
        int c = color[u];
        cnt_of_cnt[cnt[c]]--;
        if (cnt_of_cnt[cnt[c]] == 0) s.erase(cnt[c]);
        sum[cnt[c]] -= c;
        cnt[c] += del;
        sum[cnt[c]] += c;
        cnt_of_cnt[cnt[c]]++;
        s.insert(cnt[c]);
        for(int v : a[u]) {
            if (v == p || big[v]) continue;
            add(add, v, u, del);
        }
    };

    auto dsu_on_tree = [&](auto dsu_on_tree, int u, int p, bool keep) -> void {
        // find big_c
        int big_c = -1;
        for(int v : a[u]) {
            if (v == p) continue;
            if (big_c == -1 || sz[big_c] < sz[v]) big_c = v;
        }
        // update child not big_c (not keep)
        for(int v : a[u])
            if (v != p && v != big_c)
                dsu_on_tree(dsu_on_tree, v, u, false);
        // update big_c (keep)
        if (big_c != -1) {
            big[big_c] = true;
            dsu_on_tree(dsu_on_tree, big_c, u, true);
        }
        // add value for cur node
        add(add, u, p, 1);
        int max_cnt = *s.rbegin();
        ans[u] = sum[max_cnt];
        // delete big_c
        if (big_c != -1) big[big_c] = false;
        // remove node u if not keep
        if (!keep) add(add, u, p, -1);
    };

    dsu_on_tree(dsu_on_tree,1, -1, false);
    for(int i = 1; i <= n; i++) cout << ans[i] << ' ';
    return 0;
}