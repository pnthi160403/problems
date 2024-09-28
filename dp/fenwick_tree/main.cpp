#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

struct FT {
    vector<ll> bit;
    int n;
    FT(int _n) {
        n = _n;
        bit.resize(n + 1);
    }
    void add(ll value, int index) {
        for(int i = index + 1; i <= n; i += i & -i)
            bit[i] = max(bit[i], value);
    }
    ll get(int index) {
        ll ans = 0;
        for(int i = index + 1; i >= 1; i -= i & -i)
            ans = max(ans, bit[i]);
        return ans;
    }
};

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n;
    cin >> n;
    vector<int> h(n), a(n);
    for(int &x : h)
        cin >> x;
    for(int &x : a)
        cin >> x;
    FT ft(n);
    ft.add(a[0], h[0] - 1);
    ll ans = a[0];
    for(int i = 1; i < n; i++) {
        ll max_value = ft.get(h[i] - 1) + a[i];
        ans = max(ans, max_value);
        ft.add(max_value, h[i] - 1);
    }
    cout << ans;
    return 0;
}