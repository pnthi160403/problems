#include <bits/stdc++.h>
#define ll long long
#define endl '\n'
#define ff(i, x, y) for(int i = x; i <= y; i++)
#define fi first
#define se second
#define pb push_back

using namespace std;

const int MOD = (int)1e9 + 7;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while(t--) {
        int n; cin >> n;
        vector<ll> a(n + 1), b(n + 1), c(n + 1);
        ff(i, 1, n) {
            cin >> a[i];
            ll tmp = a[i];
            while(tmp % 2 == 0) {
                tmp /= 2;
                c[i]++;
            }
            b[i] = tmp;
        }
        ff(i, 1, n) {
            b[i] = (b[i] + b[i - 1]) % MOD;
            c[i] = (c[i] + c[i - 1]) % MOD;
        }
        vector<ll> dp(n + 1);
        dp[1] = a[1];
        vector<ll> _b;
        ff(i, 1, n) _b.pb(a[i]);
        auto bin_pow = [&](ll a, ll b) -> ll {
            ll res = 1;
            while(b) {
                if (b & 1) {
                    res *= a;
                    res %= MOD;
                }
                b /= 2;
                a *= a;
                a %= MOD;
            }
            return res;
        };
        ff(i, 2, n) {
            int l = 1, r = i - 1, j = i;
            int j = i;
            for(int p = i - 1; p >= 1; p--) {
                if (a[p] > a[i] * bin_pow(2ll, c[i - 1] - c[p - 1])) {
                    j = p;
                    break;
                }
            }
            if (j == i) {
                dp[i] = b[i - 1] + 1ll * a[i] * bin_pow(2ll, c[i - 1]);
            } else {
                dp[i] = dp[j] + b[i - 1] - b[j] + 1ll * a[i] * bin_pow(2ll, c[i - 1] - c[j]);
            }
            dp[i] %= MOD;
        }
        ff(i, 1, n)
            cout << dp[i] << ' ';
        cout << endl;
    }
    return 0;
}