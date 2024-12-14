#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MOD = (int)1e9 + 7;
const int BASE = 311;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    string s; cin >> s;
    string rs(s.begin(), s.end());
    reverse(rs.begin(), rs.end());
    int n = s.length();
    s = "#" + s;
    rs = "#" + rs;
    vector<ll> pow(n + 1);
    pow[0] = 1;
    for(int i = 1; i <= n; i++) {
        pow[i] = (pow[i - 1] * BASE) % MOD;
    }
    auto calc_hash = [&](string a, int mod, int base) -> vector<ll> {
        int n = a.length() - 1;
        vector<ll> hash(n + 1);
        for(int i = 1; i <= n; i++) {
            hash[i] = (hash[i - 1] * base + a[i] - 'a' + 1) % mod;
        }
        return hash;
    };
    auto get_hash = [&](vector<ll> &hash, int i, int j, int mod) -> ll {
        if (i > j) return 0;
        return (hash[j] - hash[i - 1] * pow[j - i + 1] + 1ll * mod * mod) % mod;
    };
    vector<ll> hash_s = calc_hash(s, MOD, BASE);
    vector<ll> hash_rs = calc_hash(rs, MOD, BASE);
    int t; cin >> t;
    while(t--) {
        int k; cin >> k;
        auto check_sub1 = [&]() -> bool {
            return k == 1;
        };
        auto solve_sub1 = [&]() -> void {
            int max_length; cin >> max_length;
            int max_odd = 0, max_even = 0;
            // odd
            for(int i = 2; i <= n - 1; i++) {
                int l = 1, r = min(i - 1, n - i), res = 0;
                while(l <= r) {
                    int len = (l + r) / 2;
                    if (get_hash(hash_s, i - len, i - 1, MOD) == get_hash(hash_rs, n - i - len + 1, n - i, MOD)) {
                        res = len;
                        l = len + 1;
                    } else {
                        r = len - 1;
                    }
                }
                max_odd = max(max_odd, 1 + res * 2);
            }
            // even
            for(int i = 1; i <= n - 1; i++) {
                int l = 1, r = min(i, n - i), res = -1;
                while(l <= r) {
                    int len = (l + r) / 2;
                    if (get_hash(hash_s, i - len + 1, i, MOD) == get_hash(hash_rs, n - i - len + 1, n - i, MOD)) {
                        res = len;
                        l = len + 1;
                    } else {
                        r = len - 1;
                    }
                }
                max_even = max(max_even, res * 2);
            }
            if (max_length % 2 == 1 && max_odd >= max_length) {
                cout << "YES" << endl;
            } else if (max_length % 2 == 0 && max_even >= max_length) {
                cout << "YES" << endl;
            } else {
                cout << "NO" << endl;
            }
        };
        auto check_sub2 = [&]() -> bool {
            return k <= 13 && n <= 200;
        };
        auto solve_sub2 = [&]() -> void {
            vector<int> len(k);
            for(int i = 0; i < k; i++) cin >> len[i];
            vector<vector<bool>> dp(n + 1, vector<bool>(1 << k, false));
            dp[0][0] = true;
            auto check = [&](int i, int j) -> bool {
                if (get_hash(hash_s, i, j, MOD) == get_hash(hash_rs, n - j + 1, n - i + 1, MOD)) {
                    return true;
                }
                return false;
            };
            for(int i = 1; i <= n; i++) {
                for(int mask = 1; mask < (1 << k); mask++) {
                    for(int j = 0; j < k; j++) {
                        if ((mask & (1 << j)) == 0) continue;
                        if (check(i + 1 - len[j], i) == false) continue;
                        if (dp[i - len[j]][mask - (1 << j)]) {
                            dp[i][mask] = true;
                        }
                    }
                    if (dp[i][(1 << k) - 1]) {
                        cout << "YES" << endl;
                        return;
                    }
                }
                for(int mask = 0; mask < (1 << k); mask++) {
                    dp[i][mask] = dp[i][mask] | dp[i - 1][mask];
                }
            }
            cout << "NO" << endl;
        };
        if (check_sub1()) {
            solve_sub1();
        } else if (check_sub2()) {
            solve_sub2();
        } else {
            solve_sub2();
        }
    }
    return 0;
}