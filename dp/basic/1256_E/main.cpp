// https://codeforces.com/contest/1256/problem/E
#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

const ll INF = (ll)1e18;

struct Element {
    int value, index;
};

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n;
    cin >> n;
    vector<Element> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i].value;
        a[i].index = i;
    }
    sort(a.begin() + 1, a.end(), [](const Element &x, const Element &y) -> bool {
        if (x.value != y.value)
            return x.value < y.value;
        return x.index > y.index;
    });
    vector<ll> dp(n + 2), g(n + 2), par(n + 1, -1);
    dp[0] = 0;
    g[0] = -a[1].value;
    int min_index = 0;
    for(int i = 3; i <= n; i++) {
        dp[i] = g[min_index] + a[i].value;
        par[i] = min_index + 1;
        if (i + 1 <= n) {
            g[i] = dp[i] - a[i + 1].value;
        }
        if (g[min_index] > g[i - 2]) {
            min_index = i - 2;
        }
    }
    int find_index = n;
    vector<pair<int,int>> paths;
    while(find_index > 0) {
        int par_findex_index = par[find_index];
        if (par_findex_index <= 0) {
            paths.push_back({1, find_index});
            break;
        }
        paths.push_back({par_findex_index, find_index});
        find_index = par_findex_index - 1;
    }
    vector<int> ans(n + 1);
    int cnt = 1;
    for(pair<int,int> path : paths) {
        for(int i = path.first; i <= path.second; i++) {
            ans[a[i].index] = cnt;
        }
        cnt++;
    }
    cout << dp[n] << ' ' << (int)paths.size() << endl;
    for(int i = 1; i <= n; i++) {
        cout << ans[i] << ' ';
    }
    return 0;
}