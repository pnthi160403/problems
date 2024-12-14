#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    ll l, r, k; cin >> l >> r >> k;
    ll ans = 0;
    auto check = [&](ll x, ll y) -> bool {
        return (x ^ y) % k == (x & y) % k;
    };
    for(ll i = l; i <= r; i++) {
        for(ll j = i + 1; j <= r; j++) {
            ans += check(i, j);
        }
    }
    cout << ans;
    return 0;
}