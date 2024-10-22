#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

const ll INF = (ll)1e18;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n;
    cin >> n;
    vector<pair<int,int>> a(n);
    bool have_00 = false;
    for(int i = 0; i < n; i++) {
        cin >> a[i].first >> a[i].second;
        if (a[i].first == 0 && a[i].second == 0)
            have_00 = true;
    }
    if (have_00 == false) {
        n++;
        a.push_back({0, 0});
    }
    sort(a.begin(), a.end(), [&](pair<int,int> x, pair<int,int> y) -> bool {
        int max_x = max(x.first, x.second);
        int max_y = max(y.first, y.second);
        if (max_x != max_y)
            return max_x < max_y;
        if (x.first != y.first)
            return x.first < y.first;
        return x.second < y.second;
    });
    vector<vector<pair<int,ll>>> adj(a.size(), vector<pair<int,ll>>());
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if (i == j)
                continue;
            int max_i = max(a[i].first, a[i].second);
            int max_j = max(a[j].first, a[j].second);
            if (max_i < max_j) {
                adj[i].push_back({j, abs(a[i].first - a[j].first) + abs(a[j].second - a[i].second)});
            } else if(max_j < max_i) {
                adj[j].push_back({i, abs(a[i].first - a[j].first) + abs(a[j].second - a[i].second)});
            } else {
                adj[i].push_back({j, abs(a[i].first - a[j].first) + abs(a[j].second - a[i].second)});
                adj[j].push_back({i, abs(a[i].first - a[j].first) + abs(a[j].second - a[i].second)});
            }
        }
    }
    vector<vector<ll>> min_cost(a.size(), vector<ll>(a.size(), INF));
    auto bfs = [&](int x) -> void {
        vector<ll> dist(a.size(), INF);
        dist[x] = 0;
        queue<pair<int,ll>> q;
        q.push({x, dist[x]});
        while(q.size()) {
            auto[cur, cost] = q.front();
            q.pop();
            min_cost[x][cur] = cost;
            for(auto[v, cost_v] : adj[cur]) {
                if (dist[v] > dist[cur] + cost_v) {
                    dist[v] = dist[cur] + cost_v;
                    q.push({v, dist[v]});
                }
            }
        }
    };
    for(int i = 0; i < n; i++)
        bfs(i);

    // check array a;
    for(int i = 0; i < n; i++) {
        cerr << a[i].first << ' ' << a[i].second << endl;
    }
    cerr << endl;

    // check bfs
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cerr << "min_cost[" << i << "][" << j << "] = " << min_cost[i][j] << endl;
        }
    }
    cerr << endl;

    vector<vector<ll>> dp(a.size(), vector<ll>(a.size(), INF));
    vector<int> used(a.size(), 0);
    dp[0][1] = 0;
    auto dfs = [&](auto dfs, int u) -> void {
        // used[u]++;
        for(auto[v, cost] : adj[u]) {
            if (used[v] == 2)
                continue;
            for(int k = 2; k <= n; k++) {
                if (dp[u][k - 1] == INF)
                    continue;
                dp[v][k] = min(dp[v][k], dp[u][k - 1] + min_cost[u][v]);
                // cerr << "dp[" << v << "][" << k << "] = " << dp[v][k] << endl;
            }
            dfs(dfs, v);
        }
    };
    dfs(dfs, 0);
    ll ans = INF;
    for(int i = 0; i < n; i++){
        ans = min(ans, dp[i][n]);
    }
    cout << ans;
    return 0;
}