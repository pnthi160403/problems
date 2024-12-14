#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

struct Query {
    int id, l, r, a, b;
};

struct FT {
    vector<int> bit;
    int n;
    void init(int _n) {
        n = _n;
        bit.assign(n + 2, 0);
    }
    void add(int x, int val) {
        for(int i = x; i <= n; i += i & -i) bit[i] += val;
    }
    int get(int x) {
        int res = 0;
        for(int i = x; i >= 1; i -= i & -i) res += bit[i];
        return res;
    }
    int get(int l, int r) {
        if (l - 1 >= 1) return get(r) - get(l - 1);
        return get(r);
    }
} ft1, ft2;

const int N = (int)1e5;
vector<int> cur_val(N + 1);

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n, m; cin >> n >> m;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) cin >> a[i];
    vector<Query> queries;
    for(int i = 0; i < m; i++) {
        int l, r, _a, _b; cin >> l >> r >> _a >> _b;
        queries.push_back({i, l, r, _a, _b});
    }
    int B = (int)sqrt(n) + 1;
    sort(queries.begin(), queries.end(), [&](Query x, Query y) -> bool {
        if (x.l / B != y.l / B) return x.l / B < y.l / B;
        return x.r < y.r;
    });
    ft1.init(n);
    ft2.init(n);
    auto add = [&](int i) -> void {
        i = a[i];
        ft1.add(i, 1);
        cur_val[i]++;
        if (cur_val[i] == 1) ft2.add(i, 1);
    };
    auto del = [&](int i) -> void {
        i = a[i];
        ft1.add(i, -1);
        cur_val[i]--;
        if (cur_val[i] == 0) ft2.add(i, -1);
    };
    vector<pair<int,int>> ans(m);
    int cur_l = 1, cur_r = 0;
    for(Query query : queries) {
        auto[id, l, r, _a, _b] = query;
        while(cur_l > l) add(--cur_l);
        while(cur_r < r) add(++cur_r);
        while(cur_l < l) del(cur_l++);
        while(cur_r > r) del(cur_r--);
        int ans1 = ft1.get(_a, _b);
        int ans2 = ft2.get(_a, _b);
        ans[id] = {ans1, ans2};
    }
    for(int i = 0; i < m; i++) {
        cout << ans[i].first << ' ' << ans[i].second << endl;
    }
    return 0;
}