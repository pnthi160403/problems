// https://atcoder.jp/contests/abc289/tasks/abc289_g
#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

const ll INF = (ll)1e18;

struct Node {
    ll a, b;
    Node(ll _a, ll _b) {
        a = _a;
        b = _b;
    }
    ll get(int x) {
        return a * x + b;
    }
};

struct ST {
    vector<Node> st;
    int n;
    vector<int> a;
    ST(vector<int> _a) {
        a = _a;
        n = (int)a.size();
        st.assign(4 * n, Node(0, -INF));
    }
    void update(int id, int l, int r, Node value) {
        int mid = (l + r) / 2;
        bool check_left = value.get(a[l]) >= st[id].get(a[l]);
        bool check_mid = value.get(a[mid]) >= st[id].get(a[mid]);
        if (check_mid) {
            swap(st[id], value);
        }
        if (l == r)
            return;
        if (check_left != check_mid)
            update(id * 2, l, mid, value);
        else
            update(id * 2 + 1, mid + 1, r, value);
    }
    ll get(int id, int l, int r, int x) {
        int mid = (l + r) / 2;
        ll res = st[id].get(a[x]);
        if (l == r)
            return res;
        if (x <= mid)
            return max(res, get(id * 2, l, mid, x));
        else
            return max(res, get(id * 2 + 1, mid + 1, r, x));
    }
};

struct Query {
    int index, value;
};

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n, m;
    cin >> n >> m;
    vector<int> b(n);
    vector<int> c(m);
    for(int &x : b)
        cin >> x;
    for(int &x : c)
        cin >> x;
    vector<Query> queries;
    for(int i = 0; i < m; i++) {
        queries.push_back({i, c[i]});
    }
    sort(b.begin(), b.end());
    reverse(b.begin(), b.end());
    sort(queries.begin(), queries.end(), [](const Query &x, const Query &y) -> bool {
        if (x.value != y.value) {
            return x.value < y.value;
        }
        return x.index < y.index;
    });
    sort(c.begin(), c.end());
    ST st(c);
    for(int i = 0; i < n; i++) {
        st.update(1, 0, (int)c.size() - 1, Node(i + 1, 1ll * (i + 1) * b[i]));
    }
    vector<ll> ans(m);
    for(int i = 0; i < m; i++) {
        ans[queries[i].index] = st.get(1, 0, (int)c.size() - 1, i);
    }
    for(int i = 0; i < m; i++)
        cout << ans[i] << ' ';
    return 0;
}