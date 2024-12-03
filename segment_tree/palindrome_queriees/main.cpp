// https://cses.fi/problemset/task/2420 -> TLE
#include <bits/stdc++.h>
#define ll long long
#define endl '\n'
 
using namespace std;
 
const int MOD = (int)1e9 + 7;
const int BASE = 311;
const int N = (int)2e5;
 
vector<ll> POW(N + 1);
 
struct Node {
    ll hashl[26], hashr[26];
    ll len;
 
    Node() {
        for(int i = 0; i < 26; i++) hashl[i] = hashr[i] = 0;
        len = 0;
    }
};
 
struct ST {
    string s;
    int n;
    vector<Node> st;
 
    void init(string &_s) {
        s = _s;
        s = "#" + s;
        n = s.length() - 1;
        st.resize(4 * (n + 1));
        build(1, 1, n);
    }
    Node combine(Node left, Node right) {
        if (left.len == 0) return right;
        if (right.len == 0) return left;
        Node res;
        res.len = left.len + right.len;
        for(int i = 0; i < 26; i++) {
            res.hashl[i] = (left.hashl[i] * POW[right.len] + right.hashl[i]) % MOD;
            res.hashr[i] = (right.hashr[i] * POW[left.len] + left.hashr[i]) % MOD;
        }
        return res;
    }
    void build(int id, int l, int r) {
        if (l == r) {
            int x = s[l] - 'a';
            ll hash_val = x + 1;
            st[id].hashl[x] = st[id].hashr[x] = hash_val;
            st[id].len = 1;
            return;
        }
        int mid = (l + r) / 2;
        build(id * 2, l, mid);
        build(id * 2 + 1, mid + 1, r);
        st[id] = combine(st[id * 2], st[id * 2 + 1]);
    }
    void update(int id, int l, int r, int pos, char c) {
        if (l > pos || r < pos) return;
        if (l == r) {
            int old = s[l] - 'a';
            st[id].hashl[old] = st[id].hashr[old] = 0;
            s[l] = c;
            int x = s[l] - 'a';
            ll hash_val = x + 1;
            st[id].hashl[x] = st[id].hashr[x] = hash_val;
            return;
        }
        int mid = (l + r) / 2;
        update(id * 2, l, mid, pos, c);
        update(id * 2 + 1, mid + 1, r, pos, c);
        st[id] = combine(st[id * 2], st[id * 2 + 1]);
    }
    Node get(int id, int l, int r, int u, int v) {
        if (l > v || r < u) {
            Node null_node;
            null_node.len = 0;
            return null_node;
        } else if (l >= u && r <= v) {
            return st[id];
        }
        int mid = (l + r) / 2;
        Node get1 = get(id * 2, l, mid, u, v);
        Node get2 = get(id * 2 + 1, mid + 1, r, u, v);
        return combine(get1, get2);
    }
};
 
int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    POW[0] = 1;
    for(int i = 1; i <= N; i++) POW[i] = (POW[i - 1] * BASE) % MOD;
    int n, m; cin >> n >> m;
    string s; cin >> s;
    ST st;
    st.init(s);
    while(m--) {
        int type; cin >> type;
        if (type == 1) {
            int _k;
            char _x;
            cin >> _k >> _x;
            st.update(1, 1, n, _k, _x);
        } else if (type == 2) {
            int _a, _b; cin >> _a >> _b;
            Node get = st.get(1, 1, n, _a, _b);
            ll hashl = 0, hashr = 0;
            for(int i = 0; i < 26; i++) {
                hashl += get.hashl[i];
                hashr += get.hashr[i];
                hashl %= MOD;
                hashr %= MOD;
            }
            if (hashl == hashr) {
                cout << "YES" << endl;
            } else {
                cout << "NO" << endl;
            }
        }
    }
    return 0;
}