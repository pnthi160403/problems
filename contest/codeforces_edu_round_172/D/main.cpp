#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

struct Node {
    vector<pair<int,int>> all;
    vector<int> maxl;
};

struct ST {
    int n;
    vector<Node> st;
    vector<pair<int,int>> all;
    void init(vector<pair<int,int>> _all) {
        all = _all;
        n = all.size();
        st.resize(4 * n);
        build(1, 0, n - 1);
    }
    Node combine(Node left, Node right) {
        Node res;
        for(auto x : left.all) res.all.push_back(x);
        for(auto x : right.all) res.all.push_back(x);
        sort(res.all.begin(), res.all.end(), [&](pair<int,int> x, pair<int,int> y) -> bool {
            if (x.second != y.second) return x.second < y.second;
            return x.first < y.first;
        });
        res.maxl.resize(left.maxl.size() + right.maxl.size());
        res.maxl[res.maxl.size() - 1] = res.all.back().first;
        for(int i = res.maxl.size() - 2; i >= 0; i--) {
            res.maxl[i] = min(res.maxl[i + 1], res.all[i].first);
        }
        return res;
    }
    void build(int id, int l, int r) {
        if (l == r) {
            st[id].all.push_back(all[l]);
            st[id].maxl = {all[l].first};
            return;
        }
        int mid = (l + r) / 2;
        build(id * 2, l, mid);
        build(id * 2 + 1, mid + 1, r);
        st[id] = combine(st[id * 2], st[id * 2 + 1]);
    }
    pair<int,int> get(int id, int l, int r, int u, int v, int minr) {
        if (l > v || r < u) return {-1, -1};
        if (l >= u && r <= v) {
            int pl = 0, pr = st[id].all.size() - 1, res = -1;
            while(pl <= pr) {
                int pmid = (pl + pr) / 2;
                if (st[id].all[pmid].second >= minr) {
                    res = pmid;
                    pr = pmid - 1;
                } else {
                    pl = pmid + 1;
                }
            }
            return {st[id].maxl[res], st[id].all[res].second};
        }
        int mid = (l + r) / 2;
        pair<int,int> get1 = get(id * 2, l, mid, u, v, minr);
        pair<int,int> get2 = get(id * 2 + 1, mid + 1, r, u, v, minr);
        if (get1.first == -1) return get2;
        if (get2.first == -1) return get1;
        return {max(get1.first, get2.first), min(get1.second, get2.second)};
    }
};

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while(t--) {
        int n; cin >> n;
        vector<pair<int,int>> a, all;
        for(int i = 0; i < n; i++) {
            int l, r; cin >> l >> r;
            a.push_back({l, r});
            all.push_back({l, r});
        }
        sort(all.begin(), all.end());
        vector<int> b;
        for(auto[l, r] : all) b.push_back(l);
        ST st;
        st.init(all);
        cerr << "check all" << endl;
        for(int i = 0; i < all.size(); i++) {
            cerr << "i = " << i << endl;
            cerr << all[i].first << ' ' << all[i].second << endl;
        }
        cerr << endl;
        for(auto[l, r] : a) {
            int find_max_left = lower_bound(b.begin(), b.end(), l) - b.begin();
            cerr << "l = " << l << endl;
            cerr << "r = " << r << endl;
            cerr << "find_max_left = " << find_max_left << endl;
            auto[maxl, minr] = st.get(1, 0, n - 1, 0, find_max_left, r);
            cerr << "maxl = " << maxl << endl;
            cerr << "minr = " << minr << endl;
            cout << l - maxl + r - minr << endl;
        }
    }
    return 0;
}