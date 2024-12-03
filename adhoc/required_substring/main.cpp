#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

const int MOD = (int)1e9 + 7;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n; cin >> n;
    string s; cin >> s;
    n -= s.length();
    if (n <= 0) {
        cout << 0;
    } else {
        ll ans = n + 1;
        while(n--) {
            ans *= 26;
            ans %= MOD;
        }
        cout << ans;
    }
    return 0;
}