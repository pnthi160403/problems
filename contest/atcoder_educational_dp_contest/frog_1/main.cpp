#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

const int INF = (int)1e9;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n; cin >> n;
    vector<int> h(n + 1);
    for(int i = 1; i <= n; i++) cin >> h[i];
    vector<int> dp(n + 1, INF);
    dp[1] = 0;
    dp[2] = abs(h[2] - h[1]);
    for(int i = 3; i <= n; i++) dp[i] = min(dp[i - 1] + abs(h[i] - h[i - 1]), dp[i - 2] + abs(h[i] - h[i - 2]));
    cout << dp[n];
    return 0;
}