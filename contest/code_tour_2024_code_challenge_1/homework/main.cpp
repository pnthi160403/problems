#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

const ll INF = (ll)1e18;
vector<vector<map<int,ll>>> dp;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while(t--) {
        int n, k, d; cin >> n >> k >> d;
        vector<int> type(n + 1);
        for(int i = 1; i <= n; i++) cin >> type[i];
        type[0] = 0;
        vector<int> a(k + 1);
        for(int i = 1; i <= k; i++) cin >> a[i];
        vector<int> b(k + 1);
        for(int i = 1; i <= k; i++) cin >> b[i];
        dp.assign(n + 1, vector<map<int,ll>>(k + 1, map<int,ll>()));
        auto dq = [&](auto dq, int i, int k, int h) -> ll {
            if (i == n + 1) return 0;
            if (dp[i][k].find(h) != dp[i][k].end()) return dp[i][k][h];
            ll ans = INF;
            if (i - h - 1 < d) {
                ll res = dq(dq, i + 1, i, h) + (type[i] != type[k] ? a[type[i]] : min(a[type[i]], b[type[i]]));
                ans = min(ans, res);
            }
            if (i - k - 1 < d) {
                ll res = dq(dq, i + 1, k, i) + (type[i] != type[h] ? a[type[i]] : min(a[type[i]], b[type[i]]));
                ans = min(ans, res);
            }
            return dp[i][k][h] = ans;
        };
        cout << dq(dq, 1, 0, 0) << endl;
    }
    return 0;
}