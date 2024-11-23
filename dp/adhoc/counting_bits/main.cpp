// https://cses.fi/alon/task/1146
#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    ll n; cin >> n;
    vector<ll> dp(60, 0);
    for(int i = 1; i < 60; i++) {
        ll pow = 1;
        for(int j = 1; j <= i - 1; j++) pow *= 2;
        dp[i] = 2 * dp[i - 1] + pow;
    }
    auto cntBit = [&](ll n) -> int {
        int cnt = 0;
        while(n) {
            cnt++;
            n /= 2;
        }
        return cnt;
    };
    auto dq = [&](auto dq, ll n) -> ll {
        if (n <= 1) return n;
        int cnt = cntBit(n);
        ll pow = 1;
        for(int i = 1; i <= cnt - 1; i++) pow *= 2;
        return dp[cnt - 1] + n - pow + 1 + dq(dq, n - pow);
    };
    cout << dq(dq, n);
    return 0;
}