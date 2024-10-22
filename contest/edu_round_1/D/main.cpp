#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n, m, k;
    cin >> n >> m >> k;
    vector<string> s(n);
    for(string &x : s) cin >> x;
    vector<vector<bool>> d(n, vector<bool>(m, false));
    vector<pair<int,int>> b;
    int sum = 0;
    vector<int> dx = {-1, 1, 0, 0};
    vector<int> dy = {0, 0, -1, 1};
    auto dfs = [&](auto dfs, int x, int y) -> void {
        b.push_back({x, y});
        d[x][y] = true;
        for(int dir = 0; dir < 4; dir++) {
            int xx = x + dx[dir];
            int yy = y + dy[dir];
            if (xx >= 0 && xx < n && yy >= 0 && yy < m && s[xx][yy] == '.' && d[xx][yy] == false) {
                dfs(dfs, xx, yy);
            } else if(xx >= 0 && xx < n && yy >= 0 && yy < m && s[xx][yy] == '*') {
                sum++;
            }
        }
    };
    vector<vector<int>> ans(n, vector<int>(m, 0));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if (s[i][j] == '*' || d[i][j]) continue;
            b.clear();
            sum = 0;
            dfs(dfs, i, j);
            for(auto[x, y] : b) ans[x][y] = sum;
        }
    }
    while(k--) {
        int x, y; cin >> x >> y;
        cout << ans[x - 1][y - 1] << endl;
    }
    return 0;
}