#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

const ll INF = (ll)1e18;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n; cin >> n;
    vector<int> f(n + 1), c(n + 1);
    for(int i = 1; i <= n; i++) cin >> f[i];
    for(int i = 1; i <= n; i++) cin >> c[i];
    ll ans = INF;
    for(int i = 1; i <= n; i++) {
        if (f[i] >= n) {
            ans = min(ans, 1ll * f[i] * c[i]);
        }
    }
    auto solve = [&](vector<int> &f, vector<int> &c) -> ll {
        vector<ll> dp(n + 1, INF), pre_dp(n + 1, INF);
        pre_dp[1] = 1ll * f[1] * c[1];
        for(int i = 2; i <= n; i++) {
            for(int j = 0; j < n; j++) {
                if (pre_dp[j + 1] != INF && j + 1 < n)
                    dp[j] = min(dp[j], pre_dp[j + 1]);
                if (j - f[i] >= 0 && pre_dp[j - f[i]] != INF) 
                    dp[j] = min(dp[j], pre_dp[j - f[i]] + 1ll * f[i] * c[i]);
            }
            for(int j = 0; j < n; j++) {
                pre_dp[j] = dp[j];
                dp[j] = INF;
            }
        }
    };
    for(int i = 1; i <= n; i++) {
        vector<int> ff, cc;
        for(int j = i; j <= n; j++) ff.push_back(f[j]), cc.push_back(c[j]);
        for(int j = 1; j < i; j++) ff.push_back(f[j]), cc.push_back(c[j]);
        ans = min(ans, solve(ff, cc));
    }
    cout << (ans == INF ? -1 : ans);
    return 0;
}