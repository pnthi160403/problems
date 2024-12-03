#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n, m; cin >> n >> m;
    vector<pair<int,int>> a;
    for(int i = 0; i < m; i++) {
        int _a, _b; cin >> _a >> _b;
        a.push_back({_a, _b});
    }
    sort(a.begin(), a.end(), [&](pair<int,int> x, pair<int,int> y) -> bool {
        if (x.second != y.second) return x.second > y.second;
        return x.first > y.first;
    });
    ll ans = 0;
    int max_b = a[0].second;
    for(int i = 0; i < m; i++) {
        if (n == 0) break;
        if (a[i].first > max_b) {
            ans += a[i].first;
            a[i].first = -1;
            n--;
        }
    }
    if (n) {
        ll max_val = 0;
        if (a[0].first != -1) {
            max_val = 1ll * (n - 1) * a[0].second + a[0].first;
        } else {
            max_val = 1ll * n * a[0].second;
        }
        for(int i = 1; i < m; i++) {
            ll val = 0;
            if (a[i].first != -1) {
                val = 1ll * (n - 1) * a[i].second + a[i].first;
            } else {
                val = 1ll * n * a[i].second;
            }
            max_val = max(max_val, val);
        }
        ans += max_val;
    }
    cout << ans;
    return 0;
}