#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n; cin >> n;
    vector<ll> a(n);
    for(ll &x : a) cin >> x;
    int ans = 0;
    auto check = [&](ll x) -> bool {
        ll sq = (ll)sqrt(x);
        return sq * sq == x;
    };
    for(int i = 0; i < a.size() - 1; i++) {
        ll _lcm = lcm(a[i], a[i + 1]);
        if (check(_lcm)) {
            continue;
        }
        ans++;
        i++;
    }
    cout << ans;
    return 0;
}