// https://cses.fi/problemset/task/2085
#include <bits/stdc++.h>
#define ll long long
#define endl '\n'
#define int ll
 
using namespace std;
 
const ll INF = (ll)1e18;
 
struct Node {
    ll a, b;
    ll get(int x) {
        return a * x + b;
    }
};
 
struct Lichao {
    int n;
    vector<Node> st;
    void init(int _n) {
        n = _n;
        Node node = {0, INF};
        st.assign(4 * n, node);
    }
    void update(int id, int l, int r, Node node) {
        int mid = (l + r) / 2;
        bool check_mid = node.get(mid) < st[id].get(mid);
        bool check_left = node.get(l) < st[id].get(l);
        if (check_mid) swap(st[id], node);
        if (l == r) return;
        if (check_left != check_mid) update(id * 2, l, mid, node);
        else update(id * 2 + 1, mid + 1, r, node);
    }
    ll get(int id, int l, int r, int x) {
        int mid = (l + r) / 2;
        ll res = st[id].get(x);
        if (l == r) return res;
        if (x <= mid) return min(res, get(id * 2, l, mid, x));
        return min(res, get(id * 2 + 1, mid + 1, r, x));
    }
};

const int N = (int)1e6;
 
int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n, x; cin >> n >> x;
    vector<int> s(n + 1), f(n + 1);
    for(int i = 1; i <= n; i++) cin >> s[i];
    for(int i = 1; i <= n; i++) cin >> f[i];
    Lichao st;
    st.init(N + 1);
    vector<ll> dp(n + 1);
    st.update(1, 1, N, {x, 0});
    for(int i = 1; i <= n; i++) {
        dp[i] = st.get(1, 1, N, s[i]);
        st.update(1, 1, N, {f[i], dp[i]});
    }
    cout << dp[n];
    return 0;
}