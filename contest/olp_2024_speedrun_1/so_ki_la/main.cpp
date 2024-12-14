#include <bits/stdc++.h>
#define ll long long
#define int ll
#define endl '\n'

using namespace std;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    ll l, r; cin >> l >> r;
    auto get_numbers = [&](ll x) -> vector<int> {
        vector<int> numbers;
        while(x) {
            numbers.push_back(x % 10);
            x /= 10;
        }
        reverse(numbers.begin(), numbers.end());
        return numbers;
    };
    vector<int> x;
    vector<vector<vector<vector<ll>>>> dp;
    vector<int> p = {2, 3, 5, 7};
    vector<int> q = {0, 2, 3, 5, 7};
    auto dq = [&](auto dq, int i, int r, int type, int start) -> ll {
        if (dp[i][r][type][start] != -1) return dp[i][r][type][start];
        ll ans = 0;
        if (i == (int)x.size() - 1) {
            int cnt = 0;
            for(int d : p) {
                if (type == 0 && (d + r) % 3 == 0) cnt++;
                if (type == 1 && d <= x[i] && (r + d) % 3 == 0) cnt++;
            }
            ans += cnt;
        } else {
            if (start == 0) {
                for(int d : q) {
                    if (d == 0) ans += dq(dq, i + 1, 0, 0, 0);
                    else {
                        if (d == x[i] && i == 0) ans += dq(dq, i + 1, d % 3, 1, 1);
                        else if (d < x[i] || i > 0) ans += dq(dq, i + 1, d % 3, 0, 1);
                    }
                }
            } else {
                for(int d = 0; d <= 9; d++) {
                    int rr = (r + d) % 3;
                    if (type == 0) ans += dq(dq, i + 1, rr, 0, start);
                    else if (type == 1) {
                        if (d == x[i]) ans += dq(dq, i + 1, rr, 1, start);
                        else if (d < x[i]) ans += dq(dq, i + 1, rr, 0, start);
                    }
                }
            }
        }
        return dp[i][r][type][start] = ans;
    };
    ll ans_l = 0, ans_r = 0;
    if (l - 1 >= 3) {
        x = get_numbers(l - 1);
        dp.assign(x.size(), vector<vector<vector<ll>>>(3, vector<vector<ll>>(2, vector<ll>(2, -1))));
        ans_l = dq(dq, 0, 0, 1, 0);
    }
    if (r >= 3) {
        x = get_numbers(r);
        dp.assign(x.size(), vector<vector<vector<ll>>>(3, vector<vector<ll>>(2, vector<ll>(2, -1))));
        ans_r = dq(dq, 0, 0, 1, 0);
    }
    cout << ans_r - ans_l;
    return 0;
}