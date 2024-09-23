// https://oj.vnoi.info/problem/bedao_r20_e

#include <bits/stdc++.h>
#define ll long long
#define enl '\n'

using namespace std;

const ll BASE = 311;
const ll MOD = (ll)1e9 + 7;

struct Node {
    vector<ll> left, right;
    int sz;

    Node() {
        left.resize(26);
        right.resize(26);
        for(int i = 0; i < 26; i++) {
            left[i] = right[i] = 0;
        }
        sz = 0;
    } 
};

struct ST {
    vector<Node> st;
    string s;
    int n;
    vector<ll> pw;
    Node combine(Node l, Node r) {
        Node res;
        for(int i = 0; i < 26; i++) {
            res.left[i] = (l.left[i] * pw[r.sz] % MOD + r.left[i]) % MOD;
            res.right[i] = (l.right[i] + r.right[i] * pw[l.sz] % MOD) % MOD;
        }
        res.sz = l.sz + r.sz;
        return res;
    }
    ST(string _s, vector<ll> _pw) {
        pw = _pw;
        s = _s;
        n = (int)s.length();
        st.assign(4 * n, Node());
        build(1, 0, n - 1);
    }
    void build(int id, int l, int r) {
        if (l == r) {
            int id_char = (int)(s[l] - 'a');
            st[id].left[id_char] = st[id].right[id_char] = pw[1];
            st[id].sz = 1;
        } else {
            int mid = (l + r) / 2;
            build(id * 2, l, mid);
            build(id * 2 + 1, mid + 1, r);
            st[id] = combine(st[id * 2], st[id * 2 + 1]);
        }
    }
    void update(int id, int l, int r, int u, int v, int k) {
        if (l > v || r < u) {
            return;
        } else if (l >= u && r <= v) {
            rotate(st[id].left.begin(), st[id].left.begin() + k % 26, st[id].left.end());
            rotate(st[id].right.begin(), st[id].right.begin() + k % 26, st[id].right.end());
        } else {
            int mid = (l + r) / 2;
            update(id * 2, l, mid, u, v, k);
            update(id * 2 + 1, mid + 1, r, u, v, k);
            st[id] = combine(st[id * 2], st[id * 2 + 1]);
        }
    }
    Node get(int id, int l, int r, int u, int v) {
        if (l > v || r < u) {
            return Node();
        } else if (l >= u && r <= v) {
            return st[id];
        } else {
            int mid = (l + r) / 2;
            Node getl = get(id * 2, l, mid, u, v);
            Node getr = get(id * 2 + 1, mid + 1, r, u, v);
            if (getl.sz == 0)
                return getr;
            else if (getr.sz == 0)
                return getl;
            return combine(getl, getr);
        }
    }
};

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n, q;
    cin >> n >> q;
    string s;
    cin >> s;
    vector<ll> pw(n + 1, 1);
    for(int i = 1; i <= n; i++) {
        pw[i] = (pw[i - 1] * BASE) % MOD;
    }
    ST st(s, pw);
    for(int i = 0; i < q; i++) {
        int type;
        cin >> type;
        if (type == 1) {
            int l, r, k;
            cin >> l >> r >> k;
            l--, r--;
            st.update(1, 0, n - 1, l, r, k);
        } else if (type == 2) {
            int l, r;
            cin >> l >> r;
            l--, r--;
            ll get_sum_l = 0, get_sum_r = 0;
            Node get_node = st.get(1, 0, n - 1, l, r);
            for(int i = 0; i < 26; i++) {
                get_sum_l = (get_sum_l + 1ll * (i + 1) * get_node.left[i]) % MOD;
                get_sum_r = (get_sum_r + 1ll * (i + 1) * get_node.right[i]) % MOD;
            }
            cerr << "l = " << l << endl;
            cerr << "r = " << r << endl;
            cerr << "get_sum_l = " << get_sum_l << endl;
            cerr << "get_sum_r = " << get_sum_r << endl;
            if (get_sum_l != get_sum_r) {
                cout << (r - l + 1) << endl;
            } else {
                int cnt = 0;
                for(int i = 0; i < 26; i++) {
                    cnt += get_node.left[i] != 0;
                }
                if (cnt == 1) {
                    cout << 0 << endl;
                } else {
                    cout << (r - l) << endl;
                }
            }
        }
    }
    return 0;
}