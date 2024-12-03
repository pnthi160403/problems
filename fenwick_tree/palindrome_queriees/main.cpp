// https://cses.fi/problemset/task/2420/
#include <bits/stdc++.h>
#define ll long long
#define int ll
#define endl '\n'
 
using namespace std;
 
const int MOD = (int)1e9 + 7;
const int BASE = 311;
const int N = (int)2e5;
vector<ll> POW(N + 1);
 
struct FT {
    int n;
    vector<ll> bit;
    void init(int _n) {
        n = _n;
        bit.assign(n + 2, 0);
    }
    void add(int x, ll val) {
        while(val < 0) val += MOD;
        val %= MOD;
        for(int i = x; i <= n; i += i & -i) {
            bit[i] = (bit[i] + val) % MOD;
        }
    }
    ll get(int x) {
        ll res = 0;
        for(int i = x; i >= 1; i -= i & -i) {
            res += bit[i];
            res %= MOD;
        }
        return res;
    }
    ll get(int l, int r) {
        return (get(r) - get(l - 1) + MOD) % MOD;
    }
};
 
int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n, m; cin >> n >> m;
    string s; cin >> s;
    POW[0] = 1;
    for(int i = 1; i <= n; i++) POW[i] = (POW[i - 1] * BASE) % MOD;
    FT left, right;
    left.init(n);
    right.init(n);
    for(int i = 1; i <= n; i++) {
        int x = s[i - 1] - 'a' + 1;
        left.add(i, x * POW[i] % MOD);
    }
    string rs(s.begin(), s.end());
    reverse(rs.begin(), rs.end());
    for(int i = 1; i <= n; i++) {
        int x = rs[i - 1] - 'a' + 1;
        right.add(i, x * POW[i] % MOD);
    }
    while(m--) {
        int type; cin >> type;
        if (type == 1) {
            int _k; 
            char _x;
            cin >> _k >> _x;
            ll old_hash = (s[_k - 1] - 'a' + 1) * POW[_k] % MOD;
            s[_k - 1] = _x;
            ll new_hash = (s[_k - 1] - 'a' + 1) * POW[_k] % MOD;
            left.add(_k, -old_hash + new_hash);
            _k = n - _k + 1;
            old_hash = (rs[_k - 1] - 'a' + 1) * POW[_k] % MOD;
            rs[_k - 1] = _x;
            new_hash = (rs[_k - 1] - 'a' + 1) * POW[_k] % MOD;
            right.add(_k, -old_hash + new_hash);
        } else if (type == 2) {
            int _a, _b; cin >> _a >> _b;
            ll hashs = left.get(_a, _b);
            int __a = n - _b + 1, __b = n - _a + 1;
            ll hashrs = right.get(__a, __b);
            if (_a > __a) {
                hashrs *= POW[_a - __a];
                hashrs %= MOD;
            }
            if (_a < __a) {
                hashs *= POW[__a - _a];
                hashs %= MOD;
            }
            if (hashs == hashrs) {
                cout << "YES" << endl;
            } else {
                cout << "NO" << endl;
            }
        }
    }
    return 0;
}