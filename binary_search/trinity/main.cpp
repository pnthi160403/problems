#include <bits/stdc++.h>
#define ll long long
#define endl '\n'
#define ff(i, x, y) for(int i = x; i <= y; i++)
#define fi first
#define se second
#define pb push_back

using namespace std;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while(t--) {
        int n; cin >> n;
        vector<int> a(n + 1);
        ff(i, 1, n) cin >> a[i];
        sort(a.begin() + 1, a.end());
        reverse(a.begin() + 1, a.end());
        int ans = n + 1;
        ff(i, 1, n) {
            int l = i + 1, r = n - 1, res = -1;
            while(l <= r) {
                int mid = (l + r) / 2;
                if (a[mid] + a[mid + 1] <= a[i]) {
                    res = mid;
                    r = mid - 1;
                } else l = mid + 1;
            }
            if (res != -1) ans = min(ans, i - 1 + n - res);
            else ans = min(ans, i - 1);
        }
        cout << ans << endl;
    }
    return 0;
}