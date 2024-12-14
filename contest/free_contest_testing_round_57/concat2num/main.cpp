#include <bits/stdc++.h>
#define ll long long
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
        ll ans = 0;
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) {
                string concat = a[i] + a[j];
                if (concat.size() > num_R) continue;
                ll number = conver_number(concat);
                if (number >= L && number <= R) ans++;
            }
        }
        cout << ans << endl;
    }
    return 0;
}