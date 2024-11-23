#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

struct Query {
    int id, l, r, a, b;
};

struct ST {
    int n;
    vector<vector<int>> st;
    vector<int> a;
    void init(vector<int> _a) {
        a = _a;
        n = (int)a.size();
        st.resize(4 * n);
    }
    vector<int> combine(vector<int> &a, vector<int> &b) {
        vector<int> c;
        for(int x : a) c.push_back(x);
        for(int x : b) c.push_back(x);
        sort(c.begin(), c.end());
        return c;
    }
    void build(int id, int l, int r) {
        if (l == r) {
            st[id] = {a[l]};
            return;
        }
        int mid = (l + r) / 2;
        build(id * 2, l, mid);
        build(id * 2 + 1, mid + 1, r);
        st[id] = combine(st[id * 2], st[id * 2 + 1]);
    }
    int get(int id, int l, int r, int u, int v, int left, int right) {
        if (l > v || r < u) return 0;
        if (l >= u && r <= v) {
            int find_l = lower_bound(st[id].begin(), st[id].end(), left) - st[id].begin();
            int find_r = upper_bound(st[id].begin(), st[id].end(), right) - st[id].begin() - 1;
            return 
        }
    }
};

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n, m; cin >> n >> m;
    vector<int> a(n);
    for(int &x : a) cin >> x;
    vector<pair<int,int>> b;
    for(int i = 0; i < n; i++) {
        b.push_back({a[i], i});
    }
    sort(b.begin(), b.end());
    cerr << "check b" << endl;
    for(pair<int,int> x : b) {
        cerr << x.first << ' ' << x.second << endl;
    }
    cerr << endl;
    return 0;
}