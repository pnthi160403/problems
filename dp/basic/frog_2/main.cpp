#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

const int INF = (int)1e9;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n, k;
    cin >> n >> k;
    vector<int> h(n);
    for(int &x : h)
        cin >> x;
    vector<int> dp(n, INF);
    dp[0] = 0;
    for(int i = 1; i < n; i++) {
        for(int j = 1; j <= k; j++) {
            if (i - j >= 0) {
                dp[i] = min(dp[i], dp[i - j] + abs(h[i] - h[i - j]));
            }
        }
    }
    cout << dp[n - 1];
    return 0;
}