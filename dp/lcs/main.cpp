#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    string s, t;
    cin >> s >> t;
    int len_s = (int)s.size();
    int len_t = (int)t.size();
    vector<vector<int>> dp(len_s + 1, vector<int>(len_t + 1, 0));
    s = ' ' + s;
    t = ' ' + t;
    for(int i = 1; i <= len_s; i++) {
        for(int j = 1; j <= len_t; j++) {
            dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            if (s[i] == t[j]) {
                dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + 1);
            }
        }
    }
    int i = len_s, j = len_t;
    string ans = "";
    while(i >= 1 && j >= 1) {
        if (s[i] == t[j]) {
            ans += s[i];
            i--, j--;
        } else {
            if (dp[i][j] == dp[i - 1][j]) {
                i--;
            } else {
                j--;
            }
        }
    }
    reverse(ans.begin(), ans.end());
    cout << ans;
    return 0;
}