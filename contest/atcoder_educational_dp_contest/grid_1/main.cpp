#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

const int MOD = (int)1e9 + 7;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int h, w; cin >> h >> w;
    vector<string> a(h);
    for(string &x : a) cin >> x;
    vector<vector<int>> dp(h + 1, vector<int>(w + 1));
    vector<int> dx = {0, -1}, dy = {-1, 0};
    dp[1][1] = 1;
    for(int i = 1; i <= h; i++) {
        for(int j = 1; j <= w; j++) {
            for(int d = 0; d < 2; d++) {
                int ii = i + dx[d];
                int jj = j + dy[d];
                if (ii >= 1 && ii <= h && jj >= 1 && jj <= w && a[ii - 1][jj - 1] != '#') {
                    dp[i][j] = (dp[i][j] + dp[ii][jj]) % MOD;
                }
            }
        }   
    }
    cout << dp[h][w];
    return 0;
}