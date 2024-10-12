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
    vector<int> a;
    int n;
    ST(vector<int> _a) {
        a = _a;
        n = (int)a.size();
        st.assign(4 * n, {0, INF});
    }
    void update(int id, int l, int r, Node node) {
        int mid = (l + r) / 2;
        bool check_left = node.get(a[l]) <= st[id].get(a[l]);
        bool check_mid = node.get(a[mid]) <= st[id].get(a[mid]);
        if (check_mid) {
            swap(st[id], node);
        }
        if (l == r)
            return;
        if (check_left != check_mid) {
            update(id * 2, l, mid, node);
        } else {
            update(id * 2 + 1, mid + 1, r, node);
        }
    }
    ll get(int id, int l, int r, int x) {
        int mid = (l + r) / 2;
        ll res = st[id].get(a[x]);
        if (l == r)
            return res;
        if (x <= mid)
            return min(res, get(id * 2, l, mid, x));
        else
            return min(res, get(id * 2 + 1, mid + 1, r, x));
    }
};

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n;
    ll c;
    cin >> n >> c;
    vector<int> h(n);
    for(int &x : h)
        cin >> x;
    vector<ll> dp(n);
    dp[0] = 0;
    ST st(h);
    Node node(-1ll * 2 * h[0], dp[0] + 1ll * h[0] * h[0] + c);
    st.update(1, 0, n - 1, node);
    for(int i = 1; i < n; i++) {
        dp[i] = st.get(1, 0, n - 1, i) + 1ll * h[i] * h[i];
        Node node(-1ll * 2 * h[i], dp[i] + 1ll * h[i] * h[i] + c);
        st.update(1, 0, n - 1, node);
    }
    cout << dp[n - 1];
    return 0;
}