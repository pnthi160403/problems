#include <bits/stdc++.h>
#define ll long long
#define int ll
#define endl '\n'

using namespace std;

struct ST {
    int n;
    vector<int> a;
    vector<int> st;
    void init(vector<int> _a) {
        a = _a;
        n = a.size() - 1;
        st.assign(4 * (n + 1), 0);
        build(1, 1, n);
    }
    int combine(int l, int r) {
        if (l == -1) return r;
        if (r == -1) return l;
        if (a[l] >= a[r]) {
            return l;
        }
        return r;
    }
    void build(int id, int l, int r) {
        if (l == r) {
            st[id] = l;
            return;
        }
        int mid = (l + r) / 2;
        build(id * 2, l, mid);
        build(id * 2 + 1, mid + 1, r);
        st[id] = combine(st[id * 2], st[id * 2 + 1]);
    }
    int get(int id, int l, int r, int u, int v) {
        if (l > v || r < u) return -1;
        if (l >= u && r <= v) return st[id];
        int mid = (l + r) / 2;
        int get1 = get(id * 2, l, mid, u, v);
        int get2 = get(id * 2 + 1, mid + 1, r, u, v);
        return combine(get1, get2);
    }
};

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while(t--) {
        int n, k; cin >> n >> k;
        string s; cin >> s;
        s = "#" + s;
        vector<int> a(n + 1);
        a[n] = s[n] == '1' ? 1 : -1;
        for(int i = n - 1; i >= 1; i--) {
            if (s[i] == '1') {
                a[i] = a[i + 1] + 1;
            } else {
                a[i] = a[i + 1] - 1;
            }
        }
        ST st;
        st.init(a);
        int l = 2, r = n, res = -1;
        auto check = [&](int m) -> bool {
            int pre = n + 1;
            ll ans = 0;
            while(m >= 2) {
                int res = st.get(1, 1, n, m, pre - 1);
                ans += 1ll * (a[res] - (pre <= n ? a[pre] : 0)) * (m - 1);
                m--;
                pre = res;
            }
            return ans >= k;
        };
        while(l <= r) {
            int mid = (l + r) / 2;
            if (check(mid)) {
                res = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        cout << res << endl;
    }
    return 0;
}