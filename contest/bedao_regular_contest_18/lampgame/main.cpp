#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n;
    cin >> n;
    vector<pair<int,int>> a(n);
    for(int i = 0; i < n; i++)
        cin >> a[i].first;
    for(int i = 0; i < n; i++)
        cin >> a[i].second;
    sort(a.begin(), a.end(), [&](pair<int,int> &x, pair<int,int> &y) -> bool {
        // if (x.second != y.second) {
        //     return x.second > y.second;
        // }
        // return x.first > y.first;
        if (x.first != y.first) {
            return x.first > y.first;
        }
        return x.second > y.second;
    });
    vector<ll> s(n);
    s[0] = a[0].second;
    for(int i = 1; i < n; i++)
        s[i] = s[i - 1] + a[i].second;
    for(int i = 0; i < n; i++) {
        cerr << a[i].first << ' ';
    }
    cerr << endl;
    vector<int> dp(n);
    dp[0] = 1;
    for(int i = 1; i < n; i++) {
        dp[i] = 1;
        for(int j = dp[i - 1]; j >= 1; j--) {
            if (a[i - j].first >= j + 1) {
                dp[i] = j + 1;
                break;
            }
        }
    }
    for(int i = 0; i < n; i++) {
        cerr << "dp[" << i << "] = " << dp[i] << endl;
    }
    ll ans = s[0];
    for(int i = 1; i < n; i++) {
        if (i - dp[i] < 0)
            ans = max(ans, s[i]);
        else
            ans = max(ans, s[i] - s[i - dp[i]]);
    }
    cout << ans;
    return 0;
}