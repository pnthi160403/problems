#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n, k; cin >> n >> k;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) cin >> a[i];
    int min_val = a[1];
    for(int i = 2; i <= n; i++) min_val = min(min_val, a[i]);
    vector<int> dp(k + 1);
    for(int i = 0; i < min_val; i++) {
        dp[i] = 0;
    }
    for(int i = min_val; i <= k; i++) {
        for(int j = 1; j <= n; j++) {
            if (i - a[j] < 0) continue;
            if (dp[i - a[j]] == 0) {
                dp[i] = 1;
                break;
            }
        }
    }
    cout << (dp[k] == 1 ? "First" : "Second");
    return 0;
}