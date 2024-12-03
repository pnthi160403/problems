#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

const int N = (int)1e6;

struct ST {
    int n;
    vector<int> st;
    void init(int _n) {
        n = _n;
        st.assign(4 * n, 0);
    }
    void update(int id, int l, int r, int pos, int val) {
        if (r < pos || l > pos) return;
        if (l == r) {
            st[id] = max(st[id], val);
            return;
        }
        int mid = (l + r) / 2;
        update(id * 2, l, mid, pos, val);
        update(id * 2 + 1, mid + 1, r, pos, val);
        st[id] = max(st[id * 2], st[id * 2 + 1]);
    }
    void add(int pos, int val) {
        update(1, 1, n, pos, val);
    }
    int get(int id, int l, int r, int u, int v) {
        if (l > v || r < u) return 0;
        if (l >= u && r <= v) return st[id];
        int mid = (l + r) / 2;
        int get1 = get(id * 2, l, mid, u, v);
        int get2 = get(id * 2 + 1, mid + 1, r, u, v);
        return max(get1, get2);
    }
    int get(int l, int r) {
        if (l > r) return 0;
        return get(1, 1, n, l, r);
    }
};

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int m; cin >> m;
    vector<pair<int,int>> a;
    for(int i = 0; i < m; i++) {
        int _x, _y; cin >> _x >> _y;
        _y = _x + _y - 1;
        a.push_back({_x, _y});
    }
    vector<int> dp(m);
    int ans = 0;
    ST ft1, ft2;
    ft1.init(N);
    ft2.init(N);
    for(int i = m - 1; i >= 0; i--) {
        // cerr << a[i].first << ' ' << a[i].second << endl;
        dp[i] = a[i].second - a[i].first + 1;
        // cerr << "ft1 = " << ft1.get(a[i].second + 1, N) << endl;
        // cerr << "ft2 = " << ft2.get(a[i].first + 1, N) << endl;
        dp[i] = max(dp[i], ft1.get(a[i].second + 1, N) + a[i].second - a[i].first + 1);
        dp[i] = max(dp[i], ft2.get(a[i].first + 1, a[i].second) - a[i].first);
        ft1.add(a[i].first, dp[i]);
        ft2.add(a[i].first, dp[i] + a[i].first);
        // cerr << "dp[" << i << "] = " << dp[i] << endl << endl;
        ans = max(ans, dp[i]);
    }
    cout << ans;
    return 0;
} 