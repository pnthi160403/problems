#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int candlesNumber, makeNew; cin >> candlesNumber >> makeNew;
    auto dq = [&](auto dq, int candles, int leftover) -> int {
        int ans = candles;
        if (candles == 0) return ans;
        leftover += candles;
        candles = leftover / makeNew;
        leftover = leftover % makeNew;
        ans += dq(dq, candles, leftover);
        return ans;
    };
    cout << dq(dq, candlesNumber, 0);
    return 0;
}