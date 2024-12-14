#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

pair<int,int> get_number(int l, int r) {
    if (r < l) return {0, 0};
    int odd = (r - l) / 2 + 1;
    int even = (r - l + 1) - odd;
    if (r % 2 == 0) swap(odd, even);
    return {odd, even};
}

struct Node {
    ll sum;
    int l, r;
    ll lz_odd, lz_even;
};

struct ST {
    int n;
    vector<Node> st;
    void init(int _n) {
        n = _n;
        st.assign(4 * (n + 1), {0, 0, 0, 0, 0});
        build(1, 1, n);
    }
    void build(int id, int l, int r) {
        st[id].l = l;
        st[id].r = r;
        if (l == r) {
            return;
        }
        int mid = (l + r) / 2;
        build(id * 2, l, mid);
        build(id * 2 + 1, mid + 1, r);
    }
    void down(int id) {
        ll lz_odd = st[id].lz_odd;
        ll lz_even = st[id].lz_even;

        if (lz_odd == 0 && lz_even == 0) return;

        auto[left_odd, left_even] = get_number(st[id * 2].l, st[id * 2].r);
        auto[right_odd, right_even] = get_number(st[id * 2 + 1].l, st[id * 2 + 1].r);

        st[id * 2].sum += lz_odd * left_odd + lz_even * left_even;
        st[id * 2 + 1].sum += lz_odd * right_odd + lz_even * right_even;

        st[id * 2].lz_odd += lz_odd;
        st[id * 2 + 1].lz_odd += lz_odd;
        st[id * 2].lz_even += lz_even;
        st[id * 2 + 1].lz_even += lz_even;

        st[id].lz_odd = st[id].lz_even = 0;
    }
    void update(int id, int l, int r, int u, int v, int val, bool is_odd) {
        if (l > v || r < u) return;
        if (l >= u && r <= v) {
            auto[odd, even] = get_number(l, r);
            if (is_odd) {
                st[id].sum += 1ll * val * odd;
                st[id].lz_odd += val;
            } else {
                st[id].sum += 1ll * val * even;
                st[id].lz_even += val;
            }
            return;
        }
        down(id);
        int mid = (l + r) / 2;
        update(id * 2, l, mid, u, v, val, is_odd);
        update(id * 2 + 1, mid + 1, r, u, v, val, is_odd);
        st[id].sum = st[id * 2].sum + st[id * 2 + 1].sum;
    }
    ll get(int id, int l, int r, int u, int v) {
        if (l > v || r < u) return 0;
        if (l >= u && r <= v) return st[id].sum;
        down(id);
        int mid = (l + r) / 2;
        ll g1 = get(id * 2, l, mid, u, v);
        ll g2 = get(id * 2 + 1, mid + 1, r, u, v);
        return g1 + g2;
    }
};

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n, q; cin >> n >> q;
    ST st;
    st.init(n);
    while(q--) {
        int type; cin >> type;
        if (type == 1) {
            int l, r, x; cin >> l >> r >> x;
            if (l % 2 == 1) {
                st.update(1, 1, n, l, r, x, true);
            } else {
                st.update(1, 1, n, l, r, x, false);
            }
        } else if (type == 2) {
            int l, r; cin >> l >> r;
            cout << st.get(1, 1, n, l, r) << endl;
        }
    }
    return 0;
}