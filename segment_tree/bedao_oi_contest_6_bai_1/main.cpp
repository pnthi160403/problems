// https://oj.vnoi.info/problem/bedao_oi6_d
#include <bits/stdc++.h>
#define ll long long
#define int ll
#define endl '\n'

using namespace std;

const int INF = (int)1e15;

struct Node {
    ll min_val, max_val;
    ll dp_val;
};

struct Lazy {
    ll min_val, max_val;
};

struct ST {
    int n;
    vector<Node> st;
    vector<Lazy> lz;
    void init(int _n) {
        n = _n;
        st.assign(4 * (n + 1), {INF, -INF, 0});
        lz.assign(4 * (n + 1), {INF, -INF});
    }
    void down(int id) {
        int lz_min_val = lz[id].min_val;
        int lz_max_val = lz[id].max_val;

        if (lz_min_val != INF) {
            st[id * 2].min_val = lz_min_val;
            lz[id * 2].min_val = lz_min_val;
            st[id * 2 + 1].min_val = lz_min_val;
            lz[id * 2 + 1].min_val = lz_min_val;
        }

        if (lz_max_val != -INF) {
            st[id * 2].max_val = lz_max_val;
            st[id * 2].max_val = lz_max_val;
            st[id * 2 + 1].max_val = lz_max_val;
            st[id * 2 + 1].max_val = lz_max_val;
        }

        lz[id].min_val = INF;
        lz[id].max_val = -INF;
    }
    Node combine(Node left, Node right) {
        if (left.min_val == INF) return right;
        if (right.min_val == INF) return left;
        if (left.min_val + left.max_val + left.dp_val > right.min_val + right.max_val + right.dp_val) return left;
        return right;
    }
    void update(int id, int l, int r, int u, int v, ll val, int type) {
        if (l > v || r < u) return;
        if (l >= u && r <= v) {
            if (type == 1) {
                st[id].min_val = val;
                lz[id].min_val = val;
            } else if (type == 2) {
                st[id].max_val = val;
                lz[id].max_val = val;
            } else if (type == 3) {
                st[id].dp_val = val;
            }
            return;
        }
        down(id);
        int mid = (l + r) / 2;
        update(id * 2, l, mid, u, v, val, type);
        update(id * 2 + 1, mid + 1, r, u, v, val, type);
        st[id] = combine(st[id * 2], st[id * 2 + 1]);
    }
    Node get(int id, int l, int r, int u, int v) {
        if (l > v || r < u) return {INF, -INF, 0};
        if (l >= u && r <= v) return st[id];
        down(id);
        int mid = (l + r) / 2;
        Node get1 = get(id * 2, l, mid, u, v);
        Node get2 = get(id * 2 + 1, mid + 1, r, u, v);
        return combine(get1, get2);
    }
};

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    freopen("maximize.inp", "r", stdin);
    freopen("maximize.out", "w", stdout);
    int n, k; cin >> n >> k;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) cin >> a[i];
    vector<vector<ll>> dp(n + 1, vector<ll>(k + 1));
    dp[1][1] = 2 * a[1];
    ST st[k + 1];
    for(int i = 1; i <= k; i++) st[i].init(n);
    st[1].update(1, 1, n, 1, 1, dp[1][1], 3);
    int min_val = a[1], max_val = a[1];
    for(int i = 2; i <= n; i++) {
        min_val = min(min_val, a[i]);
        max_val = max(max_val, a[i]);
        for(int t = 1; t <= min(i, k); t++) {
            st[t].update(1, 1, n, i - 1, i - 1, a[i], 1);
            st[t].update(1, 1, n, i - 1, i - 1, a[i], 2);
            int l = 1, r = i - 2, res = -1;
            while(l <= r) {
                int mid = (l + r) / 2;
                int fmid = st[t].get(1, 1, n, mid, mid).min_val;
                if (fmid > a[i]) {
                    res = mid;
                    r = mid - 1;
                } else {
                    l = mid + 1;
                }
            }
            if (res != -1) st[t].update(1, 1, n, res, i - 2, a[i], 1);
            l = 1, r = i - 2, res = -1;
            while(l <= r) {
                int mid = (l + r) / 2;
                int fmid = st[t].get(1, 1, n, mid, mid).max_val;
                if (fmid < a[i]) {
                    res = mid;
                    r = mid - 1;
                } else {
                    l = mid + 1;
                }
            }
            if (res != -1) st[t].update(1, 1, n, res, i - 2, a[i], 2);
        }
        for(int j = 1; j <= min(i, k); j++) {
            if (j == 1) {
                dp[i][j] = min_val + max_val;
            } else {
                Node get = st[j - 1].get(1, 1, n, 1, i - 1);
                dp[i][j] = get.dp_val + get.min_val + get.max_val;
            }
            st[j].update(1, 1, n, i, i, dp[i][j], 3);
        }
    }
    cout << dp[n][k];
    return 0;
}
