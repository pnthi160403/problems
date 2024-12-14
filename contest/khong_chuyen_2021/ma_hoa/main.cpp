#include <bits/stdc++.h>
#define ll long long

using namespace std;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    ll l, r, a, k; cin >> l >> r >> a >> k;
    a = a % k;
    ll g = gcd(a, k);
    k /= g;
    ll min_s = (l % k == 0 ? l / k : l / k + 1);
    ll max_s = r / k;
    if (max_s >= min_s) cout << max_s - min_s + 1;
    else cout << 0;
    return 0;
}