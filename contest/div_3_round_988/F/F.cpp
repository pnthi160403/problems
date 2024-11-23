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
        int n, m, k; cin >> n >> m >> k;
        vector<int> a(n + 1);
        ff(i, 0, n - 1) {
            int x; cin >> x;
        }
        ff(i, 1, n) cin >> a[i];
        sort(a.begin() + 1, a.end());
        int ans = k;
        for(int i = 1; i + k - 1 <= n; i++) {
            int range = x[i + k - 1] - x[i] + 1;
            int l = 1, r = k, res = -1;
            while(l <= r) {
                int mid = (l + r) / 2;
                if (mid * 2 - 1 >= range) {
                    res = mid;
                    r = mid - 1;
                } else l = mid + 1;
            }
        }
    }
    return 0;
}