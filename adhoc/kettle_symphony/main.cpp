#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while(t--) {
        int n, l, r; cin >> n >> l >> r;
        string s; cin >> s;
        auto solve = [&](string s) -> bool {
            for(int i = 0; i <= n - l; i++) {
                if (s[i] == '1') continue;
                for(int j = i; j <= i + l - 1; j++) {
                    s[j] = (s[j] == '0' ? '1' : '0');
                }
            }
            if (l < r) {
                for(int i = 0; i < n; i++) {
                    if (s[i] == '0') {
                        return i >= l;
                    }
                }
                return true;
            } else {
                for(int i = 0; i < n; i++) {
                    if (s[i] == '0') return false;
                }
                return true;
            }
        };
        string rs(s.begin(), s.end());
        if (solve(s) == false) {
            cout << "NO" << endl;
        } else {
            cout << "YES" << endl;
        }
    }
    return 0;
}