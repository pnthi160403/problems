#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

const int MOD = (int)1e9 + 7;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n;
    cin >> n;
    if (n == 1) {
        int x;
        cin >> x;
        cout << x;
        return 0;
    }
    vector<vector<int>> a(n, vector<int>(n));
    for(int i = 0; i < n; i++) 
        for(int j = 0; j < n; j++)
            cin >> a[i][j];
    vector<pair<int,int>> masks;
    vector<int> count_bit(1 << n, 0);
    for(int i = 0; i < (1 << n); i++) {
        int cnt = 0;
        for(int j = 0; j < 21; j++) {
            cnt += (i >> j) & 1;
        }
        masks.push_back({cnt, i});
    }
    sort(masks.begin(), masks.end());
    vector<int> dp(1 << n, 0);
    dp[0] = 1;
    for(pair<int,int> _ : masks) {
        auto[cnt, mask] = _;
        if (mask == 0)
            continue;
        for(int i = 0; i < n; i++) {
            if ((mask >> (n - i - 1) & 1) == 0)
                continue;
            if (a[i][cnt - 1] == 1) {
                dp[mask] += dp[mask ^ (1 << (n - i - 1))];
                dp[mask] %= MOD;
            }
        }
    }
    cout << dp[(1 << n) - 1];
    return 0;
}