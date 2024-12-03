// https://cses.fi/problemset/task/1111/
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
    vector<ll> hashl = calc_hash(pow, s);
    string tmp(s.begin(), s.end());
    reverse(tmp.begin(), tmp.end());
    vector<ll> hashr = calc_hash(pow, tmp);
    int index_odd = 1, len_odd = 0;
    for(int i = 2; i <= n - 1; i++) {
        int l = 1, r = min(i - 1, n - i), res = 0;
        while(l <= r) {
            int len = (l + r) / 2;
            if (get_hash(hashl, pow, i - len, i - 1) == get_hash(hashr, pow, n - i - len + 1, n - i)) {
                res = len;
                l = len + 1;
            } else {
                r = len - 1;
            }
        }
        if (res > len_odd) {
            index_odd = i;
            len_odd = res;
        }
    }
    int index_even = -1, len_even = 0;
    for(int i = 1; i <= n; i++) {
        int l = 1, r = min(i, n - i), res = 0;
        while(l <= r) {
            int len = (l + r) / 2;
            if (get_hash(hashl, pow, i - len + 1, i) == get_hash(hashr, pow, n - i - len + 1, n - i)) {
                res = len;
                l = len + 1;
            } else {
                r = len - 1;
            }
            if (res > len_even) {
                index_even = i;
                len_even = res;
            }
        }
    }
    int l = 1, r = 1;
    if (len_odd * 2 + 1 > len_even * 2) {
        l = index_odd - len_odd, r = index_odd + len_odd;
    } else {
        l = index_even - len_even + 1, r = index_even + len_even;
    }
    for(int i = l; i <= r; i++) {
        cout << s[i - 1];
    }
    return 0;
}