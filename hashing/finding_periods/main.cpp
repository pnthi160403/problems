// https://cses.fi/problemset/task/1733
#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

const int MOD = (int)1e9 + 7;
const int BASE = 311;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    string s; cin >> s;
    int n = s.length();
    vector<ll> pow(n + 1);
    pow[0] = 1;
    for(int i = 1; i <= n; i++) pow[i] = (pow[i - 1] * BASE) % MOD;
    auto calc_hash = [&](vector<ll> &pow, string &s) -> vector<ll> {
        int n = s.length();
        vector<ll> hash(n + 1);
        for(int i = 1; i <= n; i++) {
            hash[i] = (hash[i - 1] * BASE + s[i - 1] - 'a') % MOD;
        }
        return hash;
    };
    auto get_hash = [&](vector<ll> &hash, vector<ll> &pow, int i, int j) -> ll {
        return (hash[j] - hash[i - 1] * pow[j - i + 1] + 1ll * MOD * MOD) % MOD;
    };
    vector<ll> hash_s = calc_hash(pow, s);
    vector<int> ans;
    for(int len = 1; len <= n; len++) {
        ll hash_prefix = get_hash(hash_s, pow, 1, len);
        int i = len + 1;
        bool check = true;
        for(; i + len - 1 <= n; i += len) {
            ll cur_hash = get_hash(hash_s, pow, i, i + len - 1);
            if (hash_prefix != cur_hash) {
                check = false;
                break;
            }
        }
        if (i <= n && check) {
            ll sub_hash_prefix = get_hash(hash_s, pow, 1, 1 + n - i);
            ll sub_cur_hash = get_hash(hash_s, pow, i, n);
            check = (sub_cur_hash == sub_hash_prefix);
        }
        if (check) {
            ans.push_back(len);
        }
    }
    for(int x : ans) cout << x << ' ';
    return 0;
}