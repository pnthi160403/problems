#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n, k; cin >> n >> k;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) cin >> a[i];
    multiset<int> s;
    ll sum = 0;
    for(int i = 1; i < k; i++) {
        s.insert(a[i]);
        sum += a[i];
    }
    int ans = 0;
    for(int i = k; i <= n; i++) {
        s.insert(a[i]);
        sum += a[i];
        int max_val = *s.rbegin();
        ans += sum > 2 * max_val;
        s.erase(s.find(a[i - k + 1]));
        sum -= a[i - k + 1];
    }
    cout << ans;
    return 0;
};