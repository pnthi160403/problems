#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    ll n, p, q, r;
    auto cnt = [&](ll x, ll y) -> ll {
        return n / lcm(x, y);
    };
    while(cin >> n >> p >> q >> r) {
        ll ans = cnt(p, q) + cnt(q, r) + cnt(p, r);
        ll lcm_pq = lcm(p, q);
        ll gcd_pqr = gcd(lcm_pq, r);
        lcm_pq /= gcd_pqr;
        r /= gcd_pqr;
        if (lcm_pq * r <= (ll)1e18 / gcd_pqr) {
            ans -= n / (lcm_pq * r * gcd_pqr) * 3;
        }
        cout << ans << endl;
    }
    return 0;
}