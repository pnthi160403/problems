#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

const int MOD = (int)1e9 + 7;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    string K;
    int D;
    cin >> K >> D;
    int len_k = (int)K.size();
    vector<vector<vector<int>>> dp(len_k + 1, vector<vector<int>>(D, vector<int>(2, 0)));
    auto act = [&](int i, int j, int t) -> int {
        return (i >= 0 && j >= 0 && t >= 0) ? dp[i][j][t] : 0;
    };
    auto add = [&](int &x, int y) -> void {
        x += y;
        x %= MOD;
    };
    dp[0][0][1] = 1;
    for(int i = 1; i <= len_k; i++) {
        for(int j = 0; j < D; j++) {
            for(int d = 0; d < 10; d++) {
                if (i > 0)
                    add(dp[i][(j + d) % D][0], dp[i - 1][j][0]);
                if (d == K[i] - '0') {
                    add(dp[i][(j + d) % D][1], dp[i - 1][j][1]);
                } else if (d < K[i] - '0') {
                    add(dp[i][(j + d) % D][0], dp[i - 1][j][1]);
                }
                cerr << "i - 1 = " << i - 1 << endl;
                cerr << "j = " << j << endl;
                cerr << "dp[" << i << "][" << (j + d) % D << "][0] = " << dp[i][(j + d) % D][0] << endl;
                cerr << "dp[" << i << "][" << (j + d) % D << "][1] = " << dp[i][(j + d) % D][1] << endl;
            }
        }
    }
    cout << dp[len_k - 1][0][0] + dp[len_k - 1][0][1];
    return 0;
}