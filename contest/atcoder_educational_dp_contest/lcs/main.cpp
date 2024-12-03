#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    string s, t; cin >> s >> t;
    int ns = s.length(), nt = t.length();
    vector<vector<int>> dp(ns + 1, vector<int>(nt + 1));
    for(int i = 1; i <= ns; i++) {
        for(int j = 1; j <= nt; j++) {
            dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            if (s[i - 1] == t[j - 1]) {
                dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + 1);
            }
        }
    }
    string ans = "";
    int i = ns, j = nt;
    while(i >= 1 && j >= 1) {
        if (s[i - 1] == t[j - 1]) {
            if (dp[i][j] == dp[i - 1][j - 1] + 1) {
                ans.push_back(s[i - 1]);
                i--, j--;
            }
        } else {
            if (dp[i][j] == dp[i - 1][j]) {
                i--;
            } else if (dp[i][j] == dp[i][j - 1]) {
                j--;
            }
        }
    }
    reverse(ans.begin(), ans.end());
    cout << ans;
    return 0;
}