// https://cses.fi/problemset/task/1731
#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

const int MOD = (int)1e7 + 7;
const int BASE1 = 31;
const int BASE2 = 311;
vector<vector<pair<int,int>>> m(MOD + 1, vector<pair<int,int>>());

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    string s; cin >> s;
    int k; cin >> k;
    vector<string> a;
    for(int i = 0; i < k; i++) {
        string x; cin >> x;
        a.push_back(x);
    }
    int n = s.length();
    vector<ll> pow1(n + 1), pow2(n + 1);
    pow1[0] = 1;
    for(int i = 1; i <= n; i++) pow1[i] = (pow1[i - 1] * BASE1) % MOD;
    pow2[0] = 1;
    for(int i = 1; i <= n; i++) pow2[i] = (pow2[i - 1] * BASE2) % MOD;
    auto calc_hash = [&](string s, int BASE) -> vector<ll> {
        int n = s.length();
        vector<ll> hash(n + 1, 0);
        for(int i = 1; i <= n; i++) {
            hash[i] = (hash[i - 1] * BASE + s[i - 1] - 'a' + 1) % MOD;
        }
        return hash;
    };
    auto get_hash = [&](vector<ll> &hash, vector<ll> &pow, int i, int j) -> ll {
        return (hash[j] - hash[i - 1] * pow[j - i + 1] + 1ll * MOD * MOD) % MOD;
    };
    vector<int> dp(n + 1, 0);
    vector<ll> hash1_s = calc_hash(s, BASE1);
    vector<ll> hash2_s = calc_hash(s, BASE2);
    for(string x : a) {
        vector<ll> hash1_x = calc_hash(x, BASE1);
        vector<ll> hash2_x = calc_hash(x, BASE2);
        int hash1 = get_hash(hash1_x, pow1, 1, x.size());
        int hash2 = get_hash(hash2_x, pow2, 1, x.size());
        m[hash1].push_back({hash2, x.length()});
    }
    dp[0] = 1;
    for(int i = 1; i <= n; i++) {
        for(int j = i; j >= 1; j--) {
            ll hash1 = get_hash(hash1_s, pow1, j, i);
            ll hash2 = get_hash(hash2_s, pow2, j, i);
            int len = 0;
            for(auto[_hash2, _len] : m[hash1]) {
                if (_hash2 == hash2) {
                    len = _len;
                    break;
                }
            }
            if (len) {
                dp[i] += dp[i - len];
                dp[i] %= (int)1e9 + 7;
            }
        }
    }
    cout << dp[n];
    return 0;
}