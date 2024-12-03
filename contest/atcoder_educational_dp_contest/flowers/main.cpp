#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

struct ST {
    int n;
    vector<ll> st;
    
    void init(int _n) {
        n = _n;
        st.assign(4 * n, 0);
    }
    void update(int id, int l, int r, int pos, ll val) {
        if (l > pos || r < pos) {
            return;
        }
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
        if (l > v || r < u) return 0;
        if (l >= u && r <= v) return st[id];
        int mid = (l + r) / 2;
        ll get1 = get(id * 2, l, mid, u, v);
        ll get2 = get(id * 2 + 1, mid + 1, r, u, v);
        return max(get1, get2);
    }
};

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n; cin >> n;
    vector<int> h(n + 1), a(n + 1);
    for(int i = 1; i <= n; i++) cin >> h[i];
    for(int i = 1; i <= n; i++) cin >> a[i];
    vector<int> vals;
    for(int i = 1; i <= n; i++) vals.push_back(h[i]);
    sort(vals.begin(), vals.end());
    vector<ll> dp(n + 1);
    dp[1] = a[1];
    ST st;
    st.init(vals.size() + 1);
    int find_index = lower_bound(vals.begin(), vals.end(), h[1]) - vals.begin();
    st.update(1, 0, vals.size() - 1, find_index, dp[1]);
    for(int i = 2; i <= n; i++) {
        find_index = lower_bound(vals.begin(), vals.end(), h[i]) - vals.begin();
        if (find_index == 0) {
            dp[i] = a[i];
        } else {
            dp[i] = st.get(1, 0, vals.size() - 1, 0, find_index - 1) + a[i];
        }
        st.update(1, 0, vals.size() - 1, find_index, dp[i]);
    }
    ll ans = 0;
    for(int i = 1; i <= n; i++) ans = max(ans, dp[i]);
    cout << ans;
    return 0;
}