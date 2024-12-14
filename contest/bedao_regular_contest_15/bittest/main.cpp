#include <bits/stdc++.h>
#define ll long long
#define endl '\n'
#define int ll

using namespace std;

const int MOD = (int)1e9 + 7;
const int MOD1 = (int)1e7 + 7;
const int BASE = 311;
const int BASE1 = 31;

struct Node {
    int l, r;
    ll h[2];
};

struct Lazy {
    int move;
};

struct ST {
    int n;
    string s;
    vector<Node> st;
    vector<Lazy> lz;
    vector<ll> POW;
    int MOD;
    void init(string _s, vector<ll> _POW, int _MOD) {
        POW = _POW;
        MOD = _MOD;
        s = _s;
        n = s.length() - 1;
        st.assign(n * 4, {-1, -1, {0, 0}});
        lz.assign(n * 4, {0});
        build(1, 1, n);
    }
    Node combine(Node left, Node right) {
        if (left.h[0] == 0 && left.h[1] == 0) return right;
        if (right.h[0] == 0 && right.h[1] == 0) return left;
        Node res;
        res.h[0] = (left.h[0] * POW[right.r - right.l + 1] % MOD + right.h[0]) % MOD;
        res.h[1] = (left.h[1] * POW[right.r - right.l + 1] % MOD + right.h[1]) % MOD;
        res.l = left.l;
        res.r = right.r;
        return res;
    }
    void build(int id, int l, int r) {
        st[id].l = l;
        st[id].r = r;
        if (l == r) {
            if (s[l] == '0') {
                st[id].h[0] = 1;
                st[id].h[1] = 0;
                lz[id].move = 0;
            } else {
                st[id].h[0] = 0;
                st[id].h[1] = 1;
                lz[id].move = 0;
            }
            return;
        }
        int mid = (l + r) / 2;
        build(id * 2, l, mid);
        build(id * 2 + 1, mid + 1, r);
        st[id] = combine(st[id * 2], st[id * 2 + 1]);
    }
    void down(int id) {
        if (lz[id].move == 0) return;
        swap(st[id * 2].h[1], st[id * 2].h[0]);
        swap(st[id * 2 + 1].h[1], st[id * 2 + 1].h[0]);
        
        lz[id * 2].move ^= 1;
        lz[id * 2 + 1].move ^= 1;

        lz[id].move = 0;    
    }
    void update(int id, int l, int r, int u, int v) {
        if (l > v || r < u) return;
        if (l >= u && r <= v) {
            swap(st[id].h[0], st[id].h[1]);
            lz[id].move ^= 1;
            return;
        }
        down(id);
        int mid = (l + r) / 2;
        update(id * 2, l, mid, u, v);
        update(id * 2 + 1, mid + 1, r, u, v);
        st[id] = combine(st[id * 2], st[id * 2 + 1]);
    }
    Node get(int id, int l, int r, int u, int v) {
        if (l > v || r < u) {
            Node null_node;
            null_node.h[0] = null_node.h[1] = 0;
            return null_node;
        }
        if (l >= u && r <= v) {
            return st[id];
        }
        down(id);
        int mid = (l + r) / 2;
        Node left = get(id * 2, l, mid, u, v);
        Node right = get(id * 2 + 1, mid + 1, r, u, v);
        return combine(left, right);
    }
};

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    string s; cin >> s;
    s = "#" + s;
    int n = s.length() - 1;
    vector<ll> POW, POW1;
    POW.resize(n + 1);
    POW[0] = 1;
    for(int i = 1; i <= n; i++) {
        POW[i] = POW[i - 1] * BASE % MOD;
    }
    POW1.resize(n + 1);
    POW1[0] = 1;
    for(int i = 1; i <= n; i++) {
        POW1[i] = POW1[i - 1] * BASE1 % MOD1;
    }
    ST st, st1;
    st.init(s, POW, MOD);
    st1.init(s, POW1, MOD1);
    int q; cin >> q;
    while(q--) {
        int t; cin >> t;
        if (t == 1) {
            int l, r; cin >> l >> r;
            st.update(1, 1, n, l, r);
            st1.update(1, 1, n, l, r);
        } else {
            int x, y, z, _t; cin >> x >> y >> z >> _t;
            Node get_xy = st.get(1, 1, n, x, y);
            Node get_zt = st.get(1, 1, n, z, _t);
            ll hash_xy = (get_xy.h[0] + 2 * get_xy.h[1]) % MOD;
            ll hash_zt = (get_zt.h[0] + 2 * get_zt.h[1]) % MOD;
            Node get1_xy = st1.get(1, 1, n, x, y);
            Node get1_zt = st1.get(1, 1, n, z, _t);
            ll hash1_xy = (get1_xy.h[0] + 2 * get1_xy.h[1]) % MOD1;
            ll hash1_zt = (get1_zt.h[0] + 2 * get1_zt.h[1]) % MOD1;
            if (hash_xy == hash_zt && hash1_xy == hash1_zt) {
                cout << "YES" << endl;
            } else {
                cout << "NO" << endl;
            }
        }
    }
    return 0;
}