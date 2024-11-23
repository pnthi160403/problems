#include <bits/stdc++.h>
#define ll long long
#define endl '\n'
 
using namespace std;
 
const int MOD = (int)1e7 + 7;
const int BASE = 311;
const int BASE1 = 31;
 
int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    string s, t; cin >> s >> t;
    auto calc_pow = [&](int n, int base) -> vector<ll> {
        vector<ll> p(n + 1);
        p[0] = 1;
        for(int i = 1; i <= n; i++) p[i] = (p[i - 1] * base) % MOD;
        return p;
    };
    auto calc_hash = [&](vector<ll> &p, string s, int base) -> vector<ll> {
        int n = s.length();
        vector<ll> hash(n + 1);
        for(int i = 1; i <= n; i++) {
            hash[i] = (hash[i - 1] * base + s[i - 1] - 'a') % MOD;
        }
        return hash;
    };
    auto get_hash = [&](vector<ll> &hash, vector<ll> &pow, int i, int j) -> ll {
        return (hash[j] - hash[i - 1] * pow[j - i + 1] + 1ll * MOD * MOD) % MOD;
    };
    int ns = s.length();
    int nt = t.length();
    vector<ll> pow = calc_pow(max(ns, nt), BASE);
    vector<ll> pow1 = calc_pow(max(ns, nt), BASE1);
    vector<ll> hash_s = calc_hash(pow, s, BASE);
    vector<ll> hash1_s = calc_hash(pow1, s, BASE1);
    vector<ll> hash_t = calc_hash(pow, t, BASE);
    vector<ll> hash1_t = calc_hash(pow1, t, BASE1);
    int ans = 0;
    for(int i = 1; i + nt - 1 <= ns; i++) {
        ll hashs = get_hash(hash_s, pow, i, i + nt - 1);
        ll hash1s = get_hash(hash1_s, pow1, i, i + nt - 1);
        ll hasht = get_hash(hash_t, pow, 1, nt);
        ll hash1t = get_hash(hash1_t, pow, 1, nt);
        ans += (hashs == hasht && hash1s == hash1t);
    }
    cout << ans;
    return 0;
}