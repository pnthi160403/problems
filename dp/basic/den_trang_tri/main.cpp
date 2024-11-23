// https://dmoj.ctu.edu.vn/problem/olp2024_light
#include <bits/stdc++.h>
#define ll long long
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
            st[id] = max(st[id], val);
            return;
        }
        int mid = (l + r) / 2;
        update(id * 2, l, mid, pos, val);
        update(id * 2 + 1, mid + 1, r, pos, val);
        st[id] = max(st[id * 2], st[id * 2 + 1]);
    }
    int get(int id, int l, int r, int u, int v) {
        if (l > v || r < u) return 0;
        if (l >= u && r <= v) return st[id];
        int mid = (l + r) / 2;
        int get1 = get(id * 2, l, mid, u, v);
        int get2 = get(id * 2 + 1, mid + 1, r, u, v);
        return max(get1, get2);
    }
};

const int N = (int)1e6;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n, k; cin >> n >> k;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) cin >> a[i];
    vector<int> dp1(n + 1), dp2(n + 1);
    dp1[1] = 1;
    ST st;
    st.init(N);
    st.update(1, 1, N, a[1], dp1[1]);
    for(int i = 2; i <= n; i++) {
        dp2[i] = max(dp2[i - 1], dp1[i - 1]);
        dp1[i] = 1;
        dp1[i] = max(dp1[i], st.get(1, 1, N, max(1, a[i] - k), min(a[i] + k, N)) + 1);
        st.update(1, 1, N, a[i], dp1[i]);
    }
    cout << max(dp1[n], dp2[n]);
    return 0;
}