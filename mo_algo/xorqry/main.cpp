// https://oj.vnoi.info/problem/bedao_r13_xorqry
#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

struct Query {
    int index;
    int l, r;
};

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n, q; cin >> n >> q;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) cin >> a[i];
    vector<int> map_index(n + 1);
    map<int,vector<int>> indexs;
    for(int i = 1; i <= n; i++) {
        indexs[a[i]].push_back(i);
    }
    int cur = 0;
    for(auto[val, _indexs] : indexs) {
        cur++;
        for(int index : _indexs) {
            map_index[index] = cur;
        }
    }
    vector<Query> queries;
    for(int i = 0; i < q; i++) {
        int l, r; cin >> l >> r;
        queries.push_back({i, l, r});
    }
    int B = (int)sqrt(n + 10);
    sort(queries.begin(), queries.end(), [&](Query x, Query y) -> bool {
        if (x.l / B != y.l / B) return x.l / B < y.l / B;
        return x.r < y.r;
    });
    vector<int> cnt(cur + 1, 0);
    int cur_ans = 0;
    auto add = [&](int index) -> void {
        int map_index_val = map_index[index];
        cnt[map_index_val]++;
        if (cnt[map_index_val] == 1) {
            cur_ans ^= a[index];
        }
    };
    auto del = [&](int index) -> void {
        int map_index_val = map_index[index];
        cnt[map_index_val]--;
        if (cnt[map_index_val] == 0) {
            cur_ans ^= a[index];
        }
    };
    vector<int> ans(q);
    int cur_l = 1, cur_r = 0;
    for(Query query : queries) {
        auto[index, l, r] = query;
        while(cur_l > l) add(--cur_l);
        while(cur_r < r) add(++cur_r);
        while(cur_l < l) del(cur_l++);
        while(cur_r > r) del(cur_r--);
        ans[index] = cur_ans;
    }
    for(int x : ans) {
        cout << x << ' ';
    }
    return 0;
}