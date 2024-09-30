#include <bits/stdc++.h>
#define ll long long
#define endl '\n'
#define int ll

using namespace std;

const int MOD = (int)1e9 + 7;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    string K;
    int D;
    cin >> K >> D;
    vector<int> digit_k;
    for(int i = 0; i < (int)K.length(); i++) {
        digit_k.push_back(K[i] - '1' + 1);
    }
    vector<vector<vector<int>>> dp((int)digit_k.size() + 1, vector<vector<int>>(D, vector<int>(2, -1)));
    auto dq = [&](auto dq, int pos, int r, int state, int cur_num) -> int {
        if (pos == (int)digit_k.size()) {
            return r == 0;
        }
        if (dp[pos][r][state] != -1) {
            return dp[pos][r][state];
        }
        int res = 0;
        for(int i = 0; i <= 9; i++) {
            int new_r = (r + i) % D;
            if (state == 0) {
                res += dq(dq, pos + 1, new_r, 0, cur_num * 10 + i);
                res %= MOD;
            } else if (state == 1) {
                if (i == digit_k[pos]) {
                    res += dq(dq, pos + 1, new_r, 1, cur_num * 10 + i);
                    res %= MOD;
                } else if (i < digit_k[pos]) {
                    res += dq(dq, pos + 1, new_r, 0, cur_num * 10 + i);
                    res %= MOD;
                }
            }
        }
        return dp[pos][r][state] = res;
    };
    cout << dq(dq, 0, 0, 1, 0) - 1;
    return 0;
}
