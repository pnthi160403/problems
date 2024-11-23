#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    ll k, n; cin >> n >> k;
    ll x = n / k;
    if (n % k) x++;
    cout << x * (x + 1) / 2;
    return 0;
}