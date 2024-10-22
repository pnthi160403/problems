// https://codeforces.com/problemset/problem/744/A
#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n, m, k;
    cin >> n >> m >> k;
    vector<bool> goverment(n + 1, false);
    vector<vector<int>> a(n + 1, vector<int>());
    for(int i = 0; i < k; i++) {
        int x; cin >> x;
        goverment[x] = true;
    }
    for(int i = 0; i < m; i++) {
        int x, y; cin >> x >> y;
        a[x].push_back(y);
        a[y].push_back(x);
    }
    int cnt = 0;
    vector<bool> used(n + 1, false);
    auto dfs = [&](auto dfs, int u) -> void {
        used[u] = true;
        cnt++;
        for(int v : a[u]) {
            if (used[v] == true) continue;
            dfs(dfs, v);
        }
    };
    ll ans = 0;
    int max_size_goverment = 0;
    for(int i = 1; i <= n; i++) {
        cnt = 0;
        if (goverment[i]) dfs(dfs, i);
        max_size_goverment = max(max_size_goverment, cnt);
        ans += cnt * (cnt - 1) / 2;
    }
    int added_not_goverment = -m;
    int sum_not_goverment = 0;
    for(int i = 1; i <= n; i++) {
        if (used[i] == false) {
            cnt = 0;
            dfs(dfs, i);
            sum_not_goverment += cnt;
        }
    }
    ans -= max_size_goverment * (max_size_goverment - 1) / 2;
    max_size_goverment += sum_not_goverment;
    ans += max_size_goverment * (max_size_goverment - 1) / 2;
    cout << ans - m;
    return 0;
}