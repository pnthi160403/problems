#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

struct Node {
    int min_val, max_val;
};

const int INF = (int)1e9;

struct ST {
    int n;
    vector<Node> st;
    void init(int _n) {
        n = _n;
        st.assign(4 * (n + 1), {INF, -INF});
    }
    Node combine(Node left, Node right) {
        Node res;
        res.min_val = min(left.min_val, right.min_val);
        res.max_val = max(left.max_val, right.max_val);
        return res;
    }
    void update(int id, int l, int r, int pos, int val) {
        if (l > pos || r < pos) return;
        if (l == r) {
            st[id].min_val = min(st[id].min_val, val);
            st[id].max_val = max(st[id].max_val, val);
            return;
        }
        int mid = (l + r) / 2;
        update(id * 2, l, mid, pos, val);
        update(id * 2 + 1, mid + 1, r, pos, val);
        st[id] = combine(st[id * 2], st[id * 2 + 1]);
    }
    Node get(int id, int l, int r, int u, int v) {
        if (l > v || r < u) return {INF, -INF};
        if (l >= u && r <= v) return st[id];
        int mid = (l + r) / 2;
        Node g1 = get(id * 2, l, mid, u, v);
        Node g2 = get(id * 2 + 1, mid + 1, r, u, v);
        return combine(g1, g2);
    }
};

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    // freopen("maximize.inp", "r", stdin);
    // freopen("maximize.out", "w", stdout);
    int n, k; cin >> n >> k;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) cin >> a[i];
    vector<vector<ll>> dp(n + 1, vector<ll>(k + 1));
    dp[1][1] = 2 * a[1];
    ST st;
    st.init(n);
    st.update(1, 1, n, 1, a[1]);
    for(int i = 2; i <= n; i++) {
        st.update(1, 1, n, i, a[i]);
        Node g = st.get(1, 1, n, 1, i);
        dp[i][1] = g.min_val + g.max_val;
        for(int j = 2; j <= min(i, k); j++) {
            for(int ii = 1; ii < i; ii++) {
                Node g = st.get(1, 1, n, ii + 1, i);
                dp[i][j] = max(dp[i][j], dp[ii][j - 1] + g.min_val + g.max_val);
            }
        }
    }
    cout << dp[n][k];
    return 0;
}