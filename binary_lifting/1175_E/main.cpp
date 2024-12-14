// https://codeforces.com/contest/1175/problem/E
#include <bits/stdc++.h>
#define ll long long
#define int ll
#define endl '\n'

using namespace std;

const int N = (int)5e5;
const int LOG = 25;
vector<vector<int>> p(N + 1, vector<int>(LOG + 1, -1));

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n, m; cin >> n >> m;
    vector<pair<int,int>> a;
    for(int i = 0; i < n; i++) {
        int l, r; cin >> l >> r;
        a.push_back({l, r});
    }
    sort(a.begin(), a.end());
    vector<int> max_r(a.size());
    max_r[0] = a[0].second;
    for(int i = 1; i < a.size(); i++) max_r[i] = max(max_r[i - 1], a[i].second);
    int i = 0;
    vector<int> b;
    for(auto[x, y] : a) b.push_back(x);
    for(int l = 0; l < N; l++) {
        int find_l = upper_bound(b.begin(), b.end(), l) - b.begin() - 1;
        if (find_l >= 0 && find_l < b.size()) {
            p[l][0] = max_r[find_l];
        }
    }
    for(int j = 1; j <= LOG; j++) {
        for(int i = 0; i < N; i++) {
            if (p[i][j - 1] < 1) continue;
            p[i][j] = p[p[i][j - 1]][j - 1];
        }
    }
    while(m--) {
        int x, y; cin >> x >> y;
        int ans = 0;
        int i = LOG;
        while(true) {
            int px = p[x][i];
            if (px < y && px >= 1) {
                x = px;
                ans += 1 << i;
            }
            i--;
            if (i < 0) break;
        }
        x = p[x][0];
        ans++;
        cout << (x >= y ? ans : -1) << endl;
    }
    return 0;
}