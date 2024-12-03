// https://oj.vnoi.info/problem/segtree_itds1
#include <bits/stdc++.h>
#define ll long long
#define enl '\n'

using namespace std;

const int INF = (int)1e9;

struct ST {
    int n;
    vector<multiset<int>> st;
    vector<int> a;
    void init(vector<int> _a) {
        a = _a;
        n = a.size() - 1;
        st.resize(4 * n);
        build(1, 1, n);
    }
    void build(int id, int l, int r) {
        if (l == r) {
            st[id].insert(a[l]);
            return;
        }
        int mid = (l + r) / 2;
        build(id * 2, l, mid);
        build(id * 2 + 1, mid + 1, r);
        for(int x : st[id * 2]) st[id].insert(x);
        for(int x : st[id * 2 + 1]) st[id].insert(x);
    }
    void update(int id, int l, int r, int pos, int old_val, int val) {
        if (l > pos || r < pos) return;
        if (l == r) {
            st[id].erase(st[id].find(old_val));
            st[id].insert(val);
            return;
        }
        int mid = (l + r) / 2;
        update(id * 2, l, mid, pos, old_val, val);
        update(id * 2 + 1, mid + 1, r, pos, old_val, val);
        st[id].erase(st[id].find(old_val));
        st[id].insert(val);
    }
    int get(int id, int l, int r, int u, int v, int val) {
        if (l > v || r < u) return INF;
        if (l >= u && r <= v) {
            auto find_val = st[id].lower_bound(val);
            if (find_val != st[id].end()) return *find_val;
            return INF;
        }
        int mid = (l + r) / 2;
        int get1 = get(id * 2, l, mid, u, v, val);
        int get2 = get(id * 2 + 1, mid + 1, r, u, v, val);
        return min(get1, get2);
    }
};

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n, m; cin >> n >> m;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) cin >> a[i];
    ST st;
    st.init(a);
    while(m--) {
        int type; cin >> type;
        if (type == 1) {
            int _i, _v; cin >> _i >> _v;
            int old_val = a[_i];
            a[_i] = _v;
            int val = a[_i];
            st.update(1, 1, n, _i, old_val, val);
        } else {
            int _l, _r, _k; cin >> _l >> _r >> _k;
            int ans = st.get(1, 1, n, _l, _r, _k);
            cout << (ans == INF ? -1 : ans)  << endl;
        }
    }
    return 0;
}