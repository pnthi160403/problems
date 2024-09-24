// https://oj.vnoi.info/problem/bedao_r19_e

#include <bits/stdc++.h>
#define ll long long

using namespace std;

const ll INF = (ll)1e18;

struct Node {
    int node;
    ll weight, height;
};

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n, m;
    cin >> n >> m;
    vector<vector<Node>> a(n, vector<Node>());
    for(int i = 0; i < m; i++) {
        int u, v;
        ll w, h;
        cin >> u >> v >> w >> h;
        u--, v--;
        a[u].push_back({v, w, h});
        a[v].push_back({u, w, h});
    }
    auto dj = [&](int source, vector<ll> &min_height, vector<ll> &max_height, vector<ll> &d) -> void {
        auto cmp = [&](int x, int y) -> bool {
            if (d[x] != d[y])
                return d[x] < d[y];
            if (min_height[x] != min_height[y]) {
                return min_height[x] < min_height[y];
            } else if (max_height[x] != max_height[y]) {
                return max_height[x] > max_height[y];
            } else {
                return x < y;
            }
        };
        set<int, decltype(cmp)> q(cmp);
        d[source] = 0;
        q.insert(source);
        while(!q.empty()) {
            int cur = *(q.begin());
            q.erase(q.begin());
            for(Node node : a[cur]) {
                if (d[cur] + node.weight < d[node.node]) {
                    d[node.node] = d[cur] + node.weight;
                    min_height[node.node] = min(node.height, min_height[cur]);
                    max_height[node.node] = max(node.height, max_height[cur]);
                    q.insert(node.node);
                } else if (d[cur] + node.weight == d[node.node]) {
                    min_height[node.node] = min({min_height[node.node], node.height, min_height[cur]});
                    max_height[node.node] = max({max_height[node.node], node.height, max_height[cur]});
                    q.insert(node.node);
                }
            }
        }
    };
    vector<ll> d1(n, INF), d2(n, INF);
    vector<ll> min_height1(n, INF), max_height1(n, -INF), min_height2(n, INF), max_height2(n, -INF);
    dj(0, min_height1, max_height1, d1);
    dj(n - 1, min_height2, max_height2, d2);
    ll ans = 0;
    for(int i = 1; i < n - 1; i++) {
        if (d1[i] != INF && d2[i] != INF && d1[i] + d2[i] == d1[n - 1]) {
            if (min_height2[i] != -INF && max_height1[i] != INF)
                ans = max(ans, max_height1[i] - min_height2[i]);
            if (max_height2[i] != INF && min_height1[i] != -INF)
                ans = max(ans, max_height2[i] - min_height1[i]);
        }
    }
    cout << ans;
    return 0;
}