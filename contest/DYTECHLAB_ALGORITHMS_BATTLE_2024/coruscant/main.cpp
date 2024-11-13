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
        int n, k; cin >> n >> k;
        vector<int> a(n + 1);
        ff(i, 1, n) cin >> a[i];
        sort(a.begin() + 1, a.end());
        map<int,int> cnt;
        ff(i, 1, k - 1) cnt[a[i]]++;
        int ans = n;
        ff(i, k, n) {
            cnt[a[i]]++;
            ans = min(ans, k - cnt[a[i - k + 1]]);
            cnt[a[i - k + 1]]--;
            if (cnt[a[i - k + 1]] == 0) cnt.erase(a[i - k + 1]);
        }
        cout << ans << endl;
    }
    return 0;
}