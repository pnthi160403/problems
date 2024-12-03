// https://dmoj.ctu.edu.vn/problem/cictcpc2024_gotoschool
#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

struct Node {
    int v, cost;
};

const int INF = (int)1e9 + 7;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while(t--) {
        int n, m; cin >> n >> m;
        vector<vector<Node>> adjc(n + 1, vector<Node>()), adjw(n + 1, vector<Node>());
        for(int i = 0; i < m; i++) {
            int _a, _b, _c, _w; cin >> _a >> _b >> _c >> _w;
            adjc[_a].push_back({_b, _c});
            adjc[_b].push_back({_a, _c});
            adjw[_a].push_back({_b, _w});
            adjw[_b].push_back({_a, _w});
        }
        auto dj = [&](vector<vector<Node>> &adj, int start) -> vector<int> {
            vector<int> dist(n + 1, INF);
            dist[start] = 0;
            auto cmp = [&](int u, int v) -> bool {
                if (dist[u] != dist[v]) return dist[u] < dist[v];
                return u < v;
            };
            set<int,decltype(cmp)> s(cmp);
            s.insert(start);
            while(s.size()) {
                int u = *s.begin();
                s.erase(s.begin());
                for(Node node : adj[u]) {
                    auto[v, cost] = node;
                    if (dist[v] > dist[u] + cost) {
                        if (s.find(v) != s.end()) {
                            s.erase(s.find(v));
                        }
                        dist[v] = dist[u] + cost;
                        s.insert(v);
                    }
                }
            }
            return dist;
        };
        // bike -> c, walk -> w
        vector<int> distc_start_1 = dj(adjc, 1);
        vector<int> distc_start_n = dj(adjc, n);
        vector<int> distw_start_1 = dj(adjw, 1);
        vector<int> distw_start_n = dj(adjw, n);
        cerr << "check test " << t << endl;
        cerr << "check distc_start_1" << endl;
        for(int i = 1; i <= n; i++) {
            cerr << "distc_start_1[" << i << "] = " << distc_start_1[i] << endl;
        }
        cerr << endl;
        cerr << "check distc_start_n" << endl;
        for(int i = 1; i <= n; i++) {
            cerr << "distc_start_n[" << i << "] = " << distc_start_n[i] << endl;
        }
        cerr << endl;
        cerr << "check distw_start_1" << endl;
        for(int i = 1; i <= n; i++) {
            cerr << "distw_start_1[" << i << "] = " << distw_start_1[i] << endl;
        }
        cerr << endl;
        cerr << "check distw_start_n" << endl;
        for(int i = 1; i <= n; i++) {
            cerr << "distw_start_n[" << i << "] = " << distw_start_n[i] << endl;
        }
        cerr << endl;
        int ans = INF;
        for(int i = 2; i < n; i++) {
            if (max({distc_start_1[i],  distw_start_n[i], distw_start_1[i], distc_start_n[i]}) == INF) continue;
            int res1 = distc_start_1[i] + distw_start_n[i];
            int res2 = max(distw_start_1[i], distc_start_1[i]) + distc_start_n[i];
            int res = max(res1, res2);
            cerr << "check i = " << i << endl;
            cerr << "check res = " << res << endl;
            ans = min(ans, res);
        }
        cerr << "end check test " << t << endl;
        cout << ans << endl;
    }
    return 0;
}