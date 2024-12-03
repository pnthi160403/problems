// https://oj.vnoi.info/problem/segtree_itmed
#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

const ll INF = (ll)1e18;

struct ST {
    int n;
    vector<ll> st;
    void init(int _n) {
        n = _n;
        st.assign(4 * n, -INF);
    }
    void update(int id, int l, int r, int pos, ll val) {
        if (l > pos || r < pos) return;
        if (l == r) {
            st[id] = max(st[id], val);
            return;
        }
        int mid = (l + r) / 2;
        update(id * 2, l, mid, pos, val);
        update(id * 2 + 1, mid + 1, r, pos, val);
        st[id] = max(st[id * 2], st[id * 2 + 1]);
    }
    ll get(int id, int l, int r, int u, int v) {
        if (l > v || r < u) return -INF;
        if (l >= u && r <= v) return st[id];
        int mid = (l + r) / 2;
        ll get1 = get(id * 2, l, mid, u, v);
        ll get2 = get(id * 2 + 1, mid + 1, r, u, v);
        return max(get1, get2);
    }
};

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n, k; cin >> n >> k;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<ll> dp(n + 1);
    ST st;
    st.init(n + 1);
    ll ans = 0;
    for(int i = 1; i <= n; i++) {
        ll get = 0;
        if (i - 1 >= max(1, i - k))
            get = max(get, st.get(1, 1, n, max(1, i - k), i - 1));
        dp[i] = get + a[i];
        st.update(1, 1, n, i, dp[i]);
        ans = max(ans, dp[i]);
    }
    cout << ans;
    return 0;
}