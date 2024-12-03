// https://oj.vnoi.info/problem/bedao_r13_xorqry
#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

struct Query {
    int index;
    int l;
};

struct FT {
    int n;
    vector<int> bit;
    
    void init(int _n) {
        n = _n;
        bit.assign(n + 2, 0);
    }
    void add(int x, int val) {
        for(int i = x; i <= n; i += i & -i) {
            bit[i] ^= val;
        }
    }
    int get(int x) {
        int res = 0;
        for(int i = x; i >= 1; i -= i & -i) {
            res ^= bit[i];
        }
        return res;
    }
    int get(int l, int r) {
        return get(r) ^ get(l - 1);
    }
};

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n, q; cin >> n >> q;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) cin >> a[i];
    vector<vector<Query>> queries(n + 1);
    for(int i = 0; i < q; i++) {
        int l, r; cin >> l >> r;
        queries[r].push_back({i, l});
    }
    FT ft;
    ft.init(n);
    map<int,int> last_index;
    vector<int> ans(q);
    for(int r = 1; r <= n; r++) {
        if (last_index.find(a[r]) != last_index.end()) {
            int cur_last_index = last_index[a[r]];
            ft.add(cur_last_index, a[r]);
        }
        last_index[a[r]] = r;
        ft.add(r, a[r]);
        for(auto[index, l] : queries[r]) {
            ans[index] = ft.get(l, r);
        }
    }
    for(int x : ans) cout << x << ' ';
    return 0;
}