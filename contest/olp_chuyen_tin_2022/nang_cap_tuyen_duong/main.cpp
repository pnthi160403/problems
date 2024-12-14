#include <bits/stdc++.h>
#define ll long long
#define int ll

using namespace std;

struct Node {
    int v, cost;
};

const ll INF = (ll)1e18;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n, m, q; cin >> n >> m >> q;
    vector<vector<Node>> adj(n + 1, vector<Node>());
    for(int i = 0; i < m; i++) {
        int u, v, cost; cin >> u >> v >> cost;
        adj[u].push_back({v, cost});
    }
    auto dj = [&](int t0) -> pair<vector<ll>,vector<ll>> {
        vector<ll> d1(n + 1, INF), d2(n + 1, INF);
        d1[1] = 0;
        auto cmp = [&](int x, int y) -> bool {
            if (d1[x] != d1[y]) return d1[x] < d1[y];
            if (d2[x] != d2[y]) return d2[x] < d2[y];
            return x < y;
        };
        set<int,decltype(cmp)> q(cmp);
        q.insert(1);
        while(q.size()) {
            int u = *q.begin();
            q.erase(q.begin());
            for(auto[v, cost] : adj[u]) {
                if (d1[v] > d1[u] + cost) {
                    q.erase(v);
                    d1[v] = d1[u] + cost;
                    q.insert(v);
                }
                if (d2[v] > d1[u] + t0) {
                    q.erase(v);
                    d2[v] = d1[u] + t0;
                    q.insert(v);
                }
                if (d2[v] > d2[u] + cost) {
                    q.erase(v);
                    d2[v] = d2[u] + cost;
                    q.insert(v);
                }
            }
        }
        return {d1, d2};
    };
    vector<ll> d1, d2;
    auto res = dj(0);
    d1 = res.first;
    d2 = res.second;
    while(q--) {
        int s, t0; cin >> s >> t0;
        // d1.clear();
        // d2.clear();
        // auto res = dj(t0);
        cout << min(d1[s], d2[s] + t0) << endl;
    }
    return 0;
}