#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

const int INF = (int)1e9;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n, k; cin >> n >> k;
    vector<int> h(n + 1);
    for(int i = 1; i <= n; i++) cin >> h[i];
    vector<int> dp(n + 1, INF);
    dp[1] = 0;
    for(int i = 2; i <= n; i++) {
        for(int j = i - 1; j >= max(1, i - k); j--) {
            dp[i] = min(dp[i], dp[j] + abs(h[i] - h[j]));
        }
    }
    cout << dp[n];
    return 0;
}