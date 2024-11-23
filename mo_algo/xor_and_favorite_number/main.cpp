#include <bits/stdc++.h>
#define ll long long
#define endl '\n'
#define ff(i, x, y) for(int i = x; i <= y; i++)
#define fi first
#define se second
#define pb push_back

using namespace std;

struct Query {
    int id, l, r;
};

const int MAX_A = (int)1e7;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n, m, k; cin >> n >> m >> k;
    vector<int> a(n + 1);
    vector<int> p(n + 1);
    ff(i, 1, n) {
        cin >> a[i];
        p[i] = p[i - 1] ^ a[i];
    }
    vector<Query> queries;
    ff(i, 0, m - 1) {
        int l, r; cin >> l >> r;
        l--;
        queries.pb({i, l, r});
    }
    int B = 400;
    sort(queries.begin(), queries.end(), [&](Query x, Query y) -> bool {
        if (x.l / B != y.l / B) return x.l / B < y.l / B;
        return x.r < y.r;
    });
    vector<ll> ans(m);
    ll cur_ans = 0;
    vector<int> cnt(MAX_A + 1, 0);

    auto add = [&](int i) -> void {
        cur_ans += cnt[k ^ p[i]];
        cnt[p[i]]++;
    };
    auto del = [&](int i) -> void {
        cnt[p[i]]--;
        cur_ans -= cnt[k ^ p[i]];
    };
    int cur_l = 1, cur_r = 0;
    for(Query query : queries) {
        int id = query.id, l = query.l, r = query.r;
        while(cur_l > l) add(--cur_l);
        while(cur_r < r) add(++cur_r);
        while(cur_l < l) del(cur_l++);
        while(cur_r > r) del(cur_r--);
        ans[id] = cur_ans;
    }
    for(ll x : ans) cout << x << endl;
    return 0;
}