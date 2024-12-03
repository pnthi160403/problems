#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    auto check_prime = [&](ll n) -> bool {
        for(ll i = 2; i * i <= n; i++) {
            if (n % i == 0) return false;
        }
        return n >= 2;
    };
    int t; cin >> t;
    while(t--) {
        ll n; cin >> n;
        if (n <= (ll)1e7 && check_prime(n)) {
            cout << 2 << endl;
            continue;
        }
        if (n <= (ll)1e5) {
            vector<ll> gcd_n;
            for(ll i = 1; i * i <= n; i++) {
                if (n % i == 0) {
                    gcd_n.push_back(i);
                    if (n / i != i)
                        gcd_n.push_back(n / i);
                }
            }
            ll ans = 0;
            for(ll g : gcd_n) {
                for(ll i = 1; i * i <= g; i++) {
                    if (g % i) continue;                
                    ll x = i, y = g / i;
                    if (gcd(x, y) == 1 && x <= y) {
                        ans++;
                    }
                }
            }
            cout << ans << endl;
            continue;
        }
        ll sn = (ll)sqrt(n);
        if (check_prime(sn) && sn * sn == n) {
            cout << 3 << endl;
            continue;
        }
    }
    return 0;
}