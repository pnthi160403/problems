// https://cses.fi/problemset/task/1110
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
    auto get_hash_index = [&](vector<ll> &hash, vector<ll> &pow, int i, int mid) -> ll {
        if (mid <= n - i + 1) return get_hash(hash, pow, i, i + mid - 1);
        int remain = mid - (n - i + 1);
        ll get_hash_left = get_hash(hash, pow, i, n);
        ll get_hash_right = get_hash(hash, pow, 1, remain);
        return (get_hash_left * pow[remain] % MOD + get_hash_right) % MOD;
    };
    vector<ll> hash_s = calc_hash(pow, s);
    int cur_index = 1;
    for(int i = 2; i <= n; i++) {
        int l = 0, r = n - 1, res = -1;
        while(l <= r) {
            int mid = (l + r) / 2;
            if (get_hash_index(hash_s, pow, cur_index, mid) == get_hash_index(hash_s, pow, i, mid)) {
                res = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        int index = i + res;
        int old_index = cur_index + res;
        if (index > n) index -= n;
        if (old_index > n) old_index -= n;
        if (s[index - 1] < s[old_index - 1]) {
            cur_index = i;
        }
    }
    for(int j = cur_index; j <= n; j++) {
        cout << s[j - 1];
    }
    for(int j = 1; j < cur_index; j++) {
        cout << s[j - 1];
    }
    return 0;
}