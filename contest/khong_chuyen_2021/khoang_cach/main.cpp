#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int INF = (int)1e9;

struct ST {
    int n;
    vector<int> st;
    void init(int _n) {
        n = _n;
        st.assign(4 * n, INF);
    }
    void update(int id, int l, int r, int pos, int val) {
        if (l > pos || r < pos) return;
        if (l == r) {
            st[id] = val;
            return;
        }
        int mid = (l + r) / 2;
        update(id * 2, l, mid, pos, val);
        update(id * 2 + 1, mid + 1, r, pos, val);
        st[id] = min(st[id * 2], st[id * 2 + 1]);
    }
    int get(int id, int l, int r, int u, int v) {
        if (l > v || r < u) return INF;
        if (l >= u && r <= v) return st[id];
        int mid = (l + r) / 2;
        int g1 = get(id * 2, l, mid, u, v);
        int g2 = get(id * 2 + 1, mid + 1, r, u, v);
        return min(g1, g2);
    }
};

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int m, n, k; cin >> m >> n >> k;
    vector<int> a(m + 1), b(n + 1);
    for(int i = 1; i <= m; i++) cin >> a[i];
    for(int i = 1; i <= n; i++) cin >> b[i];
    ST st;
    st.init(m + 1);
    sort(b.begin() + 1, b.end());
    for(int i = 1; i <= m; i++) {
        int res = INF;
        int b1 = upper_bound(b.begin() + 1, b.end(), a[i]) - b.begin() - 1;
        int b2 = lower_bound(b.begin() + 1, b.end(), a[i]) - b.begin();
        if (b1 >= 1 && b1 <= n) res = min(res, abs(a[i] - b[b1]));
        if (b2 >= 1 && b2 <= n) res = min(res, abs(a[i] - b[b2]));
        st.update(1, 1, m, i, res);
    }
    while(k--) {
        int l, r; cin >> l >> r;
        cout << st.get(1, 1, m, l, r) << endl;
    }
    return 0;
}