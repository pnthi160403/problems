#include <bits/stdc++.h>
#define ll long long

using namespace std;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int h, w, k; cin >> h >> w >> k;
    vector<string> a(h);
    for(string &x : a) cin >> x;
    vector<int> dx = {-1, 1, 0, 0}, dy = {0, 0, -1, 1};
    auto check_sub1 = [&]() -> bool {
        return k <= 3;
    };
    auto solve_sub1 = [&]() -> void {
        if (k == 1) {
            int cnt = 0;
            for(int i = 0; i < a.size(); i++) {
                for(int j = 0; j < a[i].size(); j++) {
                    cnt += a[i][j] == '#';
                }
            }
            cout << cnt;
        } else if (k == 2) {
            int ans = 0;
            for(int i = 0; i < h; i++) {
                for(int j = 0; j < w; j++) {
                    if (a[i][j] == '.') continue;
                    int cnt = 0;
                    for(int d = 0; d < 4; d++) {
                        int ii = i + dx[d];
                        int jj = j + dy[d];
                        if (ii >= 0 && ii < h && jj >= 0 && jj < w && a[ii][jj] == '#') {
                            cnt++;
                        }
                        a[i][j] = '.';
                    }
                    ans += cnt;
                }
            }
            cout << ans;
        } else if (k == 3) {
            int ans = 0;
            for(int i = 0; i < h; i++) {
                for(int j = 0; j < w; j++) {
                    if (a[i][j] == '.') continue;
                    int cnt = 0;
                    for(int d = 0; d < 4; d++) {
                        int ii = i + dx[d];
                        int jj = j + dy[d];
                        if (ii >= 0 && ii < h && jj >= 0 && jj < w && a[ii][jj] == '#') {
                            cnt++;
                        }
                    }
                    ans += cnt * (cnt - 1) / 2;
                }
            }
            cout << ans;
        }
    };
    if (check_sub1()) {
        solve_sub1();
    }
    return 0;
}