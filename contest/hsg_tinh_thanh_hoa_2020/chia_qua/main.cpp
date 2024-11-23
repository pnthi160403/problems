#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    freopen("CAU1.INP", "r", stdin);
    freopen("CAU1.OUT", "w", stdout);
    int x, y; cin >> x >> y;
    auto solve = [&](int n) -> set<int> {
        set<int> s;
        for(int i = 1; i * i <= n; i++) {
            if (n % i == 0) {
                s.insert(i);
                s.insert(n / i);
            }
        }
        return s;
    };
    set<int> sx = solve(x);
    set<int> sy = solve(y);
    int ans = 0;
    for(int x : sx) {
        if (sy.find(x) != sy.end()) ans++;
    }
    cout << ans;
    return 0;
}