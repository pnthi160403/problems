// https://codeforces.com/contest/1175/problem/E
#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

const int N = (int)5e5;
const int M = (int)5e5;
const int LOG = 25;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n, m;
    cin >> n >> m;
    vector<int> max_r(N + 1, -1);
    for(int i = 0; i < n; i++) {
        int l, r;
        cin >> l >> r;
        max_r[l] = max(max_r[l], r);

    }
    vector<vector<int>> p(N + 1, vector<int>(LOG + 1, -1));
    for(int i = 0; i <= N; i++) {
        max_r[i] = (i == 0 ? max_r[i] : max(max_r[i], max_r[i - 1]));
        p[i][0] = max_r[i];
    }
    for(int j = 1; j <= LOG; j++) {
        for(int i = 0; i <= N; i++) {
            if (p[i][j - 1] != -1) {
                p[i][j] = p[p[i][j - 1]][j - 1];
            }
        }
    }
    while(m--) {
        int x, y;
        cin >> x >> y;
        int ans = 0;
        for(int j = LOG; j >= 0; j--) {
            if (p[x][j] == -1)
                continue;
            if (p[x][j] < y) {
                x = p[x][j];
                ans += 1 << j;
            }
        }
        x = p[x][0];
        ans++;
        if (x < y) {
            cout << -1 << endl;
        } else {
            cout << ans << endl;
        }
    }
    return 0;
}