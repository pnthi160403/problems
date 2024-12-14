#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int INF = (int)1e9;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n; cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) cin >> a[i];
    a[0] = -INF;
    auto solve = [&]() -> vector<ll> {
        vector<ll> dp(n + 1);
        dp[0] = 0;
        vector<int> st;
        st.push_back(0);
        vector<int> pre(n + 1);
        for(int i = 1; i <= n; i++) {
            while((int)st.size() && a[st.back()] > a[i]) st.pop_back();
            pre[i] = st.back();
            st.push_back(i);
        }
        for(int i = 1; i <= n; i++) {
            int j = pre[i];
            dp[i] = dp[j] + 1ll * a[i] * (i - j);
        }
        return dp;
    };
    vector<ll> dpl = solve();
    reverse(a.begin() + 1, a.end());
    vector<ll> dpr = solve();
    ll ans = 0;
    for(int i = 1; i <= n; i++) {
        ans = max(ans, dpl[i] + dpr[n - i + 1] - a[n - i + 1]);
    }
    cout << ans;
    return 0;
}