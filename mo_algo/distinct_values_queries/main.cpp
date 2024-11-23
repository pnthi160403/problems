// https://cses.fi/problemset/task/1734
#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

const int B = 400;

struct Query {
    int id, l, r;
};

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n, q; cin >> n >> q;
    map<int,vector<int>> ma;
    for(int i = 1; i <= n; i++) {
        int x; cin >> x;
        ma[x].push_back(i);
    }
    int cnt = 0;
    vector<int> map_index(n + 1);
    for(pair<int,vector<int>> x : ma) {
        cnt++;
        for(int index : x.second) {
            map_index[index] = cnt;
        }
    }
    // cerr << "check map index" << endl;
    // for(int i = 1; i <= n; i++) {
    //     cerr << "map_index[" << i << "] = " << map_index[i] << endl;
    // }
    // cerr << endl;
    vector<Query> queries(q + 1);
    for(int i = 1; i <= q; i++) {
        int _a, _b; cin >> _a >> _b;
        queries[i] = {i, _a, _b};
    }
    sort(queries.begin() + 1, queries.end(), [&](Query x, Query y) -> bool {
        if (x.l / B != y.l / B) return x.l / B < y.l / B;
        return x.r < y.r;
    });

    vector<int> cur(n + 1);
    int distinct = 0;

    auto add = [&](int i) -> void {
        int index = map_index[i];
        cur[index]++;
        if (cur[index] == 1) distinct++;
    };

    auto del = [&](int i) -> void {
        int index = map_index[i];
        cur[index]--;
        if (cur[index] == 0) distinct--;
    };

    int cur_l = 1, cur_r = 0;
    vector<int> ans(q + 1);
    for(Query query : queries) {
        int id = query.id, l = query.l, r = query.r;
        while(cur_l > l) add(--cur_l);
        while(cur_r < r) add(++cur_r);
        while(cur_l < l) del(cur_l++);
        while(cur_r > r) del(cur_r--);
        ans[id] = distinct;
    }
    for(int i = 1; i <= q; i++) cout << ans[i] << endl;
    return 0;
}