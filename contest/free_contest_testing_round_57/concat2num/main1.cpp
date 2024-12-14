#include <bits/stdc++.h>
#define ll long long
#define int ll
#define endl '\n'

using namespace std;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while(t--) {
        int n;
        ll L, R;
        cin >> n >> L >> R;
        auto get_num = [&](ll x) -> int {
            int ans = 0;
            while(x) {
                x /= 10;
                ans++;
            }
            return ans;
        };
        auto conver_number = [&](string s) -> ll {
            ll ans = 0;
            for(char c : s) {
                int x = c - '0';
                ans = ans * 10 + x;
            }
            return ans;
        };
        int num_R = get_num(R);
        vector<string> a(n + 1);
        for(int i = 1; i <= n; i++) cin >> a[i];
        sort(a.begin() + 1, a.end(), [&](string x, string y) -> bool {
            if (x.size() != y.size()) return x.size() < y.size();
            return x < y;
        });
        auto check_r = [&](int i, int j) -> bool {
            string tmp = a[i] + a[j];
            if (tmp.length() > num_R) return false;
            ll number = conver_number(tmp);
            return number <= R;
        };
        auto check_l = [&](int i, int j) -> bool {
            string tmp = a[i] + a[j];
            if (tmp.length() > num_R) return false;
            ll number = conver_number(tmp);
            return number >= L;
        };
        vector<pair<int,int>> ans(n + 1);
        for(int i = 1; i <= n; i++) {
            int l = 1, r = n, res = -1;
            while(l <= r) {
                int mid = (l + r) / 2;
                if (check_l(i, mid)) {
                    res = mid;
                    r = mid - 1;
                } else {
                    l = mid + 1;
                }
            }
            ans[i].first = res;
            l = 1, r = n, res = -1;
            while(l <= r) {
                int mid = (l + r) / 2;
                if (check_r(i, mid)) {
                    res = mid;
                    l = mid + 1;
                } else {
                    r = mid - 1;
                }
            }
            ans[i].second = res;
        }
        ll res = 0;
        for(int i = 1; i <= n; i++) {
            if (ans[i].first == -1 || ans[i].second == -1) {
                continue;
            }
            res += ans[i].second - ans[i].first + 1;
        }
        for(int i = 1; i <= n; i++) {
            if(check_l(i, i) && check_r(i, i)) res--;
        }
        cout << res << endl;
    }
    return 0;
}