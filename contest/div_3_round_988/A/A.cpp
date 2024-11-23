#include <bits/stdc++.h>
#define ll long long
#define endl '\n'
#define ff(i, x, y) for(int i = x; i <= y; i++)
#define fi first
#define se second

using namespace std;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while(t--) {
        int n; cin >> n;
        vector<int> cnt(n + 1, 0);
        for(int i = 1; i <= n; i++) {
            int x; cin >> x;
            cnt[x]++;
        }
        ll ans = 0;
        for(int i = 1; i <= n; i++) {
            ans += cnt[i] / 2;
        }
        cout << ans << endl;
    }
    return 0;
}