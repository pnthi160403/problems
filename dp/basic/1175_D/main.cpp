#include <bits/stdc++.h>
#define ll long long
#define enl '\n'

using namespace std;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n, k;
    cin >> n >> k;
    int a[n];
    for(int i = 0; i < n; i++) cin >> a[i];
    ll f[n];
    for(int i = n - 1; i >= 0; i--) {
        if (i != n - 1)
            f[i] = f[i + 1] + a[i];
        else
            f[i] = a[i];
    }
    sort(f + 1, f + n);
    reverse(f + 1, f + n);
    ll ans = 0;
    for(int i = 0; i < k; i++)
        ans += f[i];
    cout << ans;
    return 0;
}