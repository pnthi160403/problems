#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++)
        cin >> a[i];
    vector<vector<ll>> dp(n + 1, vector<ll>(n + 1, 0));
    vector<ll> prefix(n + 1, 0);
    for(int i = 1; i <= n; i++) {
        prefix[i] = prefix[i - 1] + a[i];
    }
    for(int i = 1; i <= n; i++)
        dp[i][i] = a[i];
    for(int i = 1; i < n; i++)
        dp[i][i + 1] = max(a[i], a[i + 1]);
    auto sum = [&](int i, int j) -> ll {
        return prefix[j] - prefix[i - 1];
    };
    for(int i = n; i >= 1; i--) {
        for(int j = i + 2; j <= n; j++) {
            dp[i][j] = max(sum(i, j) - dp[i + 1][j], sum(i, j) - dp[i][j - 1]);
        }
    }
    cout << 2 * dp[1][n] - sum(1, n);
    return 0;
}