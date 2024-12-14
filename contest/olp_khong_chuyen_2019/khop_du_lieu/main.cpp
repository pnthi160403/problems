#include <bits/stdc++.h>
#define ll long long
#define int ll
#define endl '\n'

using namespace std;

struct ST {
    int n;
    vector<int> st;
    void init(int _n) {
        n = _n;
        st.assign(4 * n, 0);
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
        st[id] = gcd(st[id * 2], st[id * 2 + 1]);
    }
    int get(int id, int l, int r, int u, int v) {
        if (l > v || r < u) return 0;
        if (l >= u && r <= v) return st[id];
        int mid = (l + r) / 2;
        int g1 = get(id * 2, l, mid, u, v);
        int g2 = get(id * 2 + 1, mid + 1, r, u, v);
        return gcd(g1, g2);
    }
};

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n, k; cin >> n >> k;
    vector<int> a(n + 1), b(n + 1);
    for(int i = 1; i <= n; i++) cin >> a[i];
    for(int i = 1; i <= n; i++) cin >> b[i];
    ST st;
    st.init(n);
    for(int i = 1; i <= n; i++) {
        st.update(1, 1, n, i, abs(a[i] - b[i]));
    }
    while(k--) {
        int l, r; cin >> l >> r;
        int ans = st.get(1, 1, n, l, r);
        cout << ans << endl;
    }
    return 0;
};