#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

const int INF = (int)1e9;
const int max_v = 12;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int test_case; cin >> test_case;
    while(test_case--) {
        int n; cin >> n;
        int na, nb, nc; cin >> na >> nb >> nc;
        vector<int> in_a(n + 1, 0), in_b(n + 1, 0), in_c(n + 1);
        for(int i = 0; i < 3; i++) {
            int m; cin >> m;
            while(m--) {
                int x; cin >> x;
                if (i == 0) in_a[x] = 1;
                else if (i == 1) in_b[x] = 1;
                else in_c[x] = 1;
            }
        }
        int a = 0, b = 0, c = 0;
        int ab = 0, bc = 0, ac = 0;
        int abc = 0;
        for(int i = 1; i <= n; i++) {
            if (in_a[i] && in_b[i] && in_c[i]) abc++;
            else if (in_a[i] && in_b[i]) ab++;
            else if (in_b[i] && in_c[i]) bc++;
            else if (in_a[i] && in_c[i]) ac++;
            else if (in_a[i]) a++;
            else if (in_b[i]) b++;
            else if (in_c[i]) c++;
        }
        vector<vector<int>> capacity(max_v, vector<int>(max_v)), f(max_v, vector<int>(max_v, 0));
        vector<vector<int>> adj(max_v, vector<int>());
        auto add_edge = [&](int u, int v, int num) -> void {
            adj[u].push_back(v);
            adj[v].push_back(u);
            capacity[u][v] = num;
        };
        
        vector<int> tmp, val_tmp;

        tmp = {1, 2, 3, 4, 5, 6, 7};
        val_tmp = {a, b, c, ab, bc, ac, abc};
        for(int i = 0; i < tmp.size(); i++)
            add_edge(0, tmp[i], val_tmp[i]);

        tmp = {1, 4, 6, 7};
        val_tmp = {a, ab, ac, abc};
        for(int i = 0; i < tmp.size(); i++)
            add_edge(tmp[i], 8, val_tmp[i]);

        tmp = {2, 4, 5, 7};
        val_tmp = {b, ab, bc, abc};
        for(int i = 0; i < tmp.size(); i++)
            add_edge(tmp[i], 9, val_tmp[i]);

        tmp = {3, 5, 6, 7};
        val_tmp = {c, bc, ac, abc};
        for(int i = 0; i < tmp.size(); i++)
            add_edge(tmp[i], 10, val_tmp[i]);

        tmp = {8, 9, 10};
        val_tmp = {na, nb, nc};
        for(int i = 0; i < tmp.size(); i++)
            add_edge(tmp[i], 11, val_tmp[i]);

        vector<int> d(max_v);
        int s = 0, t = max_v - 1;
        auto bfs = [&]() -> void {
            for(int &x : d) x = INF;
            d[s] = 0;
            queue<int> q;
            q.push(s);
            while(q.size()) {
                int u = q.front(); q.pop();
                for(int v : adj[u]) {
                    if (d[v] != INF) continue;
                    if (capacity[u][v] - f[u][v] == 0) continue;
                    d[v] = d[u] + 1;
                    q.push(v);
                }
            }
        };

        vector<int> cur_vertex_id(max_v);
        auto dfs = [&](auto dfs, int u, int cur_delta) -> int {
            if (cur_delta == 0) return 0;
            if (u == t) return cur_delta;
            for(; cur_vertex_id[u] < adj[u].size(); cur_vertex_id[u]++) {
                int v = adj[u][cur_vertex_id[u]];
                if (d[v] != d[u] + 1) continue;
                if (capacity[u][v] - f[u][v] == 0) continue;
                int delta = dfs(dfs, v, min(capacity[u][v] - f[u][v], cur_delta));
                if (delta == 0) continue;
                f[u][v] += delta;
                f[v][u] -= delta;
                return delta;
            }
            return 0;
        };

        int max_flow = 0;
        while(true) {
            bfs();
            if (d[t] == INF) break;
            for(int &x : cur_vertex_id) x = 0;
            while(true) {
                int delta = dfs(dfs, s, INF);
                if (delta != 0) max_flow += delta;
                else break;
            }
        }
        cout << max_flow << endl;
    }
    return 0;
}