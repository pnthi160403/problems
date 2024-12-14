// https://dmoj.ctu.edu.vn/src/8323
#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

ll get_sum(ll start, ll d, int number) {
    ll end = start + (number - 1) * d;
    return ((end + start) * number) / 2;
}

struct Node {
    int l, r;
    ll sum, dl, dr, startl, startr;
};

vector<int> a;

struct ST {
    int n;
    vector<Node> st;
    void init(int _n) {
        n = _n;
        st.resize(4 * n);
        build(1, 1, n);
    }
    void build(int id, int l, int r) {
        st[id].l = l;
        st[id].r = r;
        if (l == r) {
            st[id].sum = a[l];
            st[id].startl = st[id].startr = 0;
            st[id].dl = st[id].dr = 0;
            return;
        }
        int mid = (l + r) / 2;
        build(id * 2, l, mid);
        build(id * 2 + 1, mid + 1, r);
        st[id].sum = st[id * 2].sum + st[id * 2 + 1].sum;
    }
    void down(int id) {
        int left = id * 2, right = id * 2 + 1;

        st[left].dl += st[id].dl;
        st[right].dl += st[id].dl;
        st[left].dr += st[id].dr;
        st[right].dr += st[id].dr;

        st[left].startl += st[id].startl;
        st[left].startr += st[id].startr + st[id].dr * (st[right].r - st[right].l + 1);
        st[right].startl += st[id].startl + st[id].dl * (st[left].r - st[left].l + 1);
        st[right].startr += st[id].startr;

        st[left].sum += get_sum(st[id].startl, st[id].dl, st[left].r - st[left].l + 1) + get_sum(st[id].startr + st[id].dr * (st[right].r - st[right].l + 1), st[id].dr, st[left].r - st[left].l + 1);
        st[right].sum += get_sum(st[id].startr, st[id].dr, st[right].r - st[right].l + 1) + get_sum(st[id].startl + st[id].dl * (st[left].r - st[left].l + 1), st[id].dl, st[right].r - st[right].l + 1);

        st[id].dl = 0;
        st[id].dr = 0;
        st[id].startl = 0;
        st[id].startr = 0;
    }
    void update(int id, int l, int r, int u, int v, int type, int B) {
        if (l > v || r < u) return;
        if (l >= u && r <= v) {
            if (type == 1) {
                st[id].sum += get_sum(1ll * (l - u + 1) * B, B, r - l + 1);
                st[id].dl += B;
                st[id].startl += 1ll * (l - u + 1) * B;
            } else if (type == 2) {
                st[id].sum += get_sum(1ll * (v - r + 1) * B, B, r - l + 1);
                st[id].dr += B;
                st[id].startr += 1ll * (v - r + 1) * B;
            }
            return;
        }
        down(id);
        int mid = (l + r) / 2;
        update(id * 2, l, mid, u, v, type, B);
        update(id * 2 + 1, mid + 1, r, u, v, type, B);
        st[id].sum = st[id * 2].sum + st[id * 2 + 1].sum;
    }
    ll get(int id, int l, int r, int u, int v) {
        if (l > v || r < u) return 0;
        if (l >= u && r <= v) {
            return st[id].sum;
        }
        down(id);
        int mid = (l + r) / 2;
        ll g1 = get(id * 2, l, mid, u, v);
        ll g2 = get(id * 2 + 1, mid + 1, r, u, v);
        return g1 + g2;
    }
} st;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n, q; cin >> n >> q;
    a.resize(n + 1);
    for(int i = 1; i <= n; i++) cin >> a[i];
    st.init(n);
    while(q--) {
        int type; cin >> type;
        if (type <= 2) {
            int l, r, B; cin >> l >> r >> B;
            st.update(1, 1, n, l, r, type, B);
        } else if (type == 3) {
            int l, r; cin >> l >> r;
            cout << st.get(1, 1, n, l, r) << endl;
        }
    }
    return 0;
}