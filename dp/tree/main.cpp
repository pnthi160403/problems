#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

const int MOD = (int)1e9 + 7;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n;
    cin >> n;
    vector<vector<int>> a(n, vector<int>());
    for(int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--,v--;
        a[u].push_back(v);
        a[v].push_back(u);
    }
    vector<ll> dp1(n, 0), dp2(n, 0);
    vector<bool> used(n, false);
    auto dfs = [&](auto dfs, int u, int p) -> void {
        used[u] = true;
        dp1[u] = dp2[u] = 1;
        if ((int)a[u].size() == 0) {
            return;
        }
        for(int v : a[u]) {
            if (v != p && used[v] == false) {
                dfs(dfs, v, u);
                dp1[u] *= (dp1[v] + dp2[v]);
                dp1[u] %= MOD;
                dp2[u] *= dp1[v];
                dp2[u] %= MOD;
            }
        }
    };
    dfs(dfs, 0, -1);
    cout << (dp1[0] + dp2[0]) % MOD;
    return 0;
}