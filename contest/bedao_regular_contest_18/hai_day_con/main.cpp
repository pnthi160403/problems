#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n, k;
    cin >> n >> k;
    vector<ll> s(n + 1, 0);
    for(int i = 1; i <= n; i++) {
        cin >> s[i];
        s[i] += s[i - 1];
    }
    vector<ll> a(n + 1, 0), max_a(n + 1, 0);
    multiset<ll> ms;
    for(int i = n - k + 1; i >= 1; i--) {
        a[i] = s[i + k - 1] - s[i - 1];
        // cerr << "s[" << i + k << "] = " << s[i + k] << endl;
        // cerr << "s[" << i - 1 << "] = " << s[i - 1] << endl;
        // cerr << "a[" << i << "] = " << a[i] << endl;
        // max_a[i] = max(max_a[i + 1], a[i]);
        if (i > k)
            ms.insert(a[i]);
    }
    // for(int i = 1; i <= n - k + 1; i++) {
        // cerr << "a[" << i << "] = " << a[i] << endl;
        // cerr << "max_a[" << i << "] = " << max_a[i] << endl;
    // }
    ll ans = 0;
    for(int i = 1; i + k <= n - k + 1; i++) {
        auto min_val = *ms.begin();
        auto max_val = *ms.rbegin();
        // cerr << "min_val = " << min_val << endl;
        // cerr << "max_val = " << max_val << endl;
        if (i + k <= n)
            ms.erase(ms.find(a[i + k]));
        ans = max({ans, abs(a[i] - min_val), abs(a[i] - max_val)});
    }
    cout << ans;
    return 0;
}