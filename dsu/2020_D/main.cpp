// https://codeforces.com/problemset/problem/2020/D
#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    struct Query {
            int a, k;
    };
    int t;
    cin >> t;
    while(t--) {
        // cerr << endl << endl;
        // cerr << "t = " << t + 1 << endl;
        int n, m;
        cin >> n >> m;
        vector<vector<vector<Query>>> queries(11, vector<vector<Query>>(11, vector<Query>()));
        for(int i = 0; i < m; i++) {
            int a, d, k;
            cin >> a >> d >> k;
            for(int flow = 1; flow <= d; flow++) {
                if (a - flow >= 0 && (a - flow) % d == 0) {
                    queries[d][flow].push_back({a, k});
                }
            }
        }
        for(int d = 1; d <= 10; d++) {
            for(int flow = 1; flow <= 10; flow++) {
                sort(queries[d][flow].begin(), queries[d][flow].end(), [&](const Query &x, const Query &y) -> bool {
                    if (x.a != y.a) {
                        return x.a < y.a;
                    }
                    return x.k > y.k;
                });
            }
        }
        for(int d = 1; d <= 10; d++) {
            for(int flow = 1; flow <= 10; flow++) {
                // cerr << endl;
                // cerr << "d = " << d << endl;
                // cerr << "flow = " << flow << endl;
                for(auto[a, k] : queries[d][flow]) {
                    // cerr << "a = " << a << endl;
                    // cerr << "k = " << k << endl;
                }
            }
        }
        vector<int> par(n + 1, -1);
        for(int i = 1; i <= n; i++)
            par[i] = i;
        auto find_p = [&](auto find_p, int x) -> int {
            if (x != par[x]) {
                return par[x] = find_p(find_p, par[x]);
            }
            return x;
        };
        vector<int> sz(n + 1, 1);
        auto union_sets = [&](int x, int y) -> bool {
            x = find_p(find_p, x);
            y = find_p(find_p, y);
            if (x == y)
                return false;
            if (sz[x] < sz[y]) {
                swap(x, y);
            }
            sz[x] += sz[y];
            par[y] = x;
            return true;
        };
        // cerr << "hi" << endl;
        int ans = n;
        for(int d = 1; d <= 10; d++) {
            for(int flow = 1; flow <= d; flow++) {
                int max = 0;
                // cerr << endl << endl;
                // cerr << "d = " << d << endl;
                // cerr << "flow = " << flow << endl;
                for(Query q : queries[d][flow]) {
                    int a = q.a;
                    int k = q.k;
                    // cerr << "a = " << a << endl;
                    // cerr << "k = " << k << endl;
                    int x;
                    if (a > max) {
                        x = 1;
                        max = a;
                    } else if (a + k * d <= max) {
                        continue;
                    } else {
                        x = (max - a) / d + 1;
                    }
                    for(int j = x; j <= k; j++) {
                        ans -= (int)union_sets(max, a + j * d);
                        max = a + j * d;
                    }
                }
            }
        }
        // cerr << "ans = ";
        cout << ans << endl;
    }
    return 0;
}