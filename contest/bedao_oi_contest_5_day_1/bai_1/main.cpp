#include <bits/stdc++.h>
#define ll long long
#define endl '\n'
#define ff(i, x, y) for(int i = x; i <= y; i++)
#define fi first
#define se second
#define int ll

using namespace std;

const ll MOD = (ll)1e9 + 7;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    freopen("oneshot.inp", "r", stdin);
    freopen("oneshot.out", "w", stdout);
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

    auto module_invert = [&](ll a) -> ll {
        return bin_pow(a % MOD, MOD - 2);
    };

    auto get_ans = [&](pair<ll,ll> x) -> ll {
        return x.fi * module_invert(x.se) % MOD; 
    };

    int n; cin >> n;
    vector<ll> a(n);
    for(ll &x : a) cin >> x;

    auto simplify = [&](pair<ll,ll> ps) -> pair<ll,ll> {
        ll g = gcd(abs(ps.fi), abs(ps.se));
        ps.fi /= g;
        ps.se /= g;
        return ps;
    };

    auto add = [&](pair<ll,ll> x, pair<ll,ll> y) -> pair<ll,ll> {
        if (x.fi == 0) return y;
        pair<ll,ll> res;
        res.se = x.se * y.se;
        res.fi = x.fi * y.se + y.fi * x.se;
        return simplify(res);
    };

    auto sub = [&](pair<ll,ll> x, pair<ll,ll> y) -> pair<ll,ll> {
        pair<ll,ll> res;
        res.se = x.se * y.se;
        res.fi = x.fi * y.se - y.fi * x.se;
        return simplify(res);
    };

    auto mul = [&](pair<ll,ll> x, pair<ll,ll> y) -> pair<ll,ll> {
        pair<ll,ll> res;
        res.se = x.se * y.se;
        res.fi = x.fi * y.fi;
        return simplify(res);
    };

    auto debug = [&](pair<ll,ll> x) -> void {
        cerr << x.fi << " / " << x.se << endl;
    };

    vector<pair<ll,ll>> ans(n);
    ff(i, 0, n - 1) ans[i].fi = 1, ans[i].se = 1;
    ff(i, 0, n - 1) {
        int l, r; cin >> l >> r;
        l--, r--;
        if (l == r) {
            ans[l] = {0, 0};
            continue;
        }
        int len;
        if (l <= r) {
            len = r - l + 1;
        } else {
            len = n - 1 - l + 1 + r + 1;
        }
        pair<ll,ll> tmp = {len - 1, len};
        if (l <= r) {
            ff(j, l, r) {
                if (ans[j].fi == 0) continue;
                ans[j] = mul(ans[j], tmp);
            }
        } else {
            ff(j, l, n - 1) {
                if (ans[j].fi == 0) continue;
                ans[j] = mul(ans[j], tmp);
            }
            ff(j, 0, r) {
                if (ans[j].fi == 0) continue;
                ans[j] = mul(ans[j], tmp);
            }
        }
    }

    pair<ll,ll> res = {0, 0};
    ff(i, 0, n - 1) {
        if (a[i] == 0) continue;
        if (ans[i].fi == 0 && a[i] != 0) {
            pair<ll,ll> tmp = {a[i], 1};
            res = add(res, tmp);
            continue;
        }
        pair<ll,ll> tmp = {-a[i], 1};
        tmp = mul(tmp, ans[i]);
        res = add(res, tmp);
        tmp = {1, 1};
        tmp = sub(tmp, ans[i]);
        pair<ll,ll> tmp1 = {a[i], 1};
        tmp1 = mul(tmp1, tmp);
        res = add(res, tmp1);
    }
    // debug(res);
    cout << get_ans(res);
    return 0;
}