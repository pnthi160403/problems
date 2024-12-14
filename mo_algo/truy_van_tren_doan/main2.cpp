// https://dmoj.ctu.edu.vn/problem/olp2024_query
#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

struct Query {
    int index;
    int l, r, a, b;
};

const int N = (int)1e5;
const int B = (int)sqrt(N + 2);
vector<vector<int>> b1(N / B + 2, vector<int>(B + 1));
vector<vector<int>> b2(N / B + 2, vector<int>(B + 1));
vector<int> block1(N / B + 2);
vector<int> block2(N / B + 2);

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n, m; cin >> n >> m;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) cin >> a[i];
    vector<Query> queries;
    for(int i = 0; i < m; i++) {
        int _l, _r, _a, _b; cin >> _l >> _r >> _a >> _b;
        queries.push_back({i, _l, _r, _a, _b});
    }
    sort(queries.begin(), queries.end(), [&](Query x, Query y) -> bool {
        if (x.l / B != y.l / B) return x.l / B < y.l / B;
        return x.r < y.r;
    });
    auto get_block = [&](int x) -> pair<int,int> {
        int i = x % B == 0 ? x / B : x / B + 1;
        int j = x % B == 0 ? B : x % B;
        return {i, j};
    };
    auto add = [&](int x) -> void {
        x = a[x];
        auto[i, j] = get_block(x);
        b1[i][j]++;
        block1[i]++;
        if (b1[i][j] == 1) {
            b2[i][j] = 1;
            block2[i]++;
        }
    };
    auto del = [&](int x) -> void {
        x = a[x];
        auto[i, j] = get_block(x);
        b1[i][j]--;
        block1[i]--;
        if (b1[i][j] == 0) {
            b2[i][j] = 0;
            block2[i]--;
        }
    };
    auto get_ans = [&](int _a, int _b) -> pair<int,int> {
        int ans1 = 0, ans2 = 0;
        auto[ia, ja] = get_block(_a);
        auto[ib, jb] = get_block(_b);
        if (ia == ib) {
            for(int x = ja; x <= jb; x++) {
                ans1 += b1[ia][x];
                ans2 += b2[ia][x];
            }
            return {ans1, ans2};
        }
        for(int x = ia + 1; x < ib; x++) {
            ans1 += block1[x];
            ans2 += block2[x];
        }
        for(int x = ja; x <= B; x++) {
            ans1 += b1[ia][x];
            ans2 += b2[ia][x];
        }
        for(int x = 1; x <= jb; x++) {
            ans1 += b1[ib][x];
            ans2 += b2[ib][x];
        }
        return {ans1, ans2};
    };
    int cur_l = 1, cur_r = 0;
    vector<pair<int,int>> ans(m);
    for(Query query : queries) {
        auto[index, l, r, _a, _b] = query;
        while(cur_l > l) add(--cur_l);
        while(cur_r < r) add(++cur_r);
        while(cur_l < l) del(cur_l++);
        while(cur_r > r) del(cur_r--);
        ans[index] = get_ans(_a, _b);
    }
    for(auto[ans1, ans2] : ans) {
        cout << ans1 << ' ' << ans2 << endl;
    }
    return 0;
}