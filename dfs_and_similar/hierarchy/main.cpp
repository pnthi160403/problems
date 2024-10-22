// https://codeforces.com/contest/17/problem/B
#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

const int INF = (int)1e9;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n; cin >> n;
    vector<int> q(n);
    for(int &x : q) cin >> x;
    int m; cin >> m;
    vector<pair<int,int>> p(n + 1, {-1, INF});
    for(int i = 0; i < m; i++) {
        int u, v, cost; cin >> u >> v >> cost;
        if (p[v].second > cost) p[v] = {u, cost};
    }
    ll sum_cost = 0;
    vector<vector<int>> a(n + 1, vector<int>());
    for(int i = 1; i <= n; i++) {
        if (p[i].first != -1) {
            sum_cost += p[i].second;
            a[p[i].first].push_back(i);
        }
    }
    vector<bool> used(n + 1, false);
    auto dfs = [&](auto dfs, int u) -> void {
        used[u] = true;
        for(int v : a[u]) {
            if (used[v]) continue;
            dfs(dfs, v);
        }
    };
    bool check = true;
    for(int i = 1; i <= n; i++) {
        if (p[i].first == -1) {
            dfs(dfs, i);
            for(int i = 1; i <= n; i++)
                if (used[i] == false)
                    check = false;
        }
    }
    cout << (check == true ? sum_cost : -1);
    return 0;
}