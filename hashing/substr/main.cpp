// https://oj.vnoi.info/problem/substr
#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

const int BASE = 311;
const int MOD = (int)1e9 + 7;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    string a, b;
    cin >> a >> b;
    if ((int)b.size() > (int)a.size()) {
        return 0;
    }
    int n = (int)a.size();
    vector<ll> pow(n + 1);
    pow[0] = 1;
    for(int i = 1; i <= n; i++) {
        pow[i] = (pow[i - 1] * BASE) % MOD;
    }
    vector<ll> hash_a(n + 1);
    for(int i = 1; i <= n; i++) {
        hash_a[i] = (hash_a[i - 1] * BASE + a[i - 1] - 'a' + 1) % MOD;
    }
    ll hash_b = 0;
    for(int i = 0; i < (int)b.size(); i++) {
        hash_b = (hash_b * BASE + b[i] - 'a' + 1) % MOD;
    }
    auto get_hash = [&](int i, int j) -> ll {
        return (hash_a[j] - hash_a[i - 1] * pow[j - i + 1] + 1ll * MOD * MOD) % MOD;
    };
    for(int i = 1; i <= n - (int)b.size() + 1; i++) {
        if (hash_b == get_hash(i, i + (int)b.size() - 1)) {
            cout << i << ' ';
        }
    }
    return 0;
}