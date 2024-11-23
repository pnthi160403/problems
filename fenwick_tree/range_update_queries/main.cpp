// https://cses.fi/problemset/task/1651
#include <bits/stdc++.h>
#define ll long long
#define endl '\n'
#define ff(i, x, y) for(int i = x; i <= y; i++)
#define fi first
#define se second
#define pb push_back

using namespace std;

struct FT {
    int n;
    vector<ll> bit;
    FT(int _n) : n(_n), bit(n + 2, 0) {};
    void add(int x, int val) {
        for(int i = x; i <= n; i += i & -i) bit[i] += val;
    }
    void add(int l, int r, int val) {
        add(l, val);
        add(r + 1, -val);
    }
    ll get(int x) {
        ll ans = 0;
        for(int i = x; i >= 1; i -= i & -i) ans += bit[i];
        return ans;
    }
};

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n, q; cin >> n >> q;
    FT ft(n);
    ff(i, 1, n) {
        int x; cin >> x;
        ft.add(i, i, x);
    }
    while(q--) {
        int type; cin >> type;
        if (type == 1) {
            int _a, _b, _u; cin >> _a >> _b >> _u;
            ft.add(_a, _b, _u);
        } else if (type == 2) {
            int _k; cin >> _k;
            cout << ft.get(_k) << endl;
        }
    }
    return 0;
}