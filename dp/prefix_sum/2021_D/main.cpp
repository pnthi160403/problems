// https://codeforces.com/problemset/problem/2021/D
#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

const ll INF = (ll)1e18;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int t;
    cin >> t;
    while(t--) {
        int n, m;
        cin >> n >> m;
        vector<vector<int>> a(n + 1, vector<int>(m + 2, 0));
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= m; j++) {
                cin >> a[i][j];
            }
        }
        auto calc_l = [&](vector<int> &a) -> vector<vector<ll>> {
            int na = (int)a.size();
            vector<ll> prefix_sum(na, 0);
            for(int i = 0; i < na; i++) {
                if (i == 0) {
                    prefix_sum[i] = a[i];
                    continue;
                } else {
                    prefix_sum[i] = prefix_sum[i - 1] + a[i];
                }
            }
            vector<ll> min_prefix_sum(na, INF);
            vector<ll> max_prefix_sum(na, -INF);
            for(int i = 0; i < na; i++) {
                if (i == 0) {
                    min_prefix_sum[i] = prefix_sum[i];
                    max_prefix_sum[i] = prefix_sum[i];
                    continue;
                }
                min_prefix_sum[i] = min(min_prefix_sum[i - 1], prefix_sum[i]);
                max_prefix_sum[i] = max(max_prefix_sum[i - 1], prefix_sum[i]);
            }
            vector<vector<ll>> res = {min_prefix_sum, max_prefix_sum, prefix_sum};
            return res;
        };
        auto calc_r = [&](vector<int> &a) -> vector<vector<ll>> {
            int na = (int)a.size();
            vector<ll> prefix_sum(na, 0);
            for(int i = na - 1; i >= 0; i--) {
                if (i == na - 1) {
                    prefix_sum[i] = a[i];
                    continue;
                } else {
                    prefix_sum[i] = prefix_sum[i + 1] + a[i];
                }
            }
            vector<ll> min_prefix_sum(na, INF);
            vector<ll> max_prefix_sum(na, -INF);
            for(int i = na - 1; i >= 0; i--) {
                if (i == na - 1) {
                    min_prefix_sum[i] = prefix_sum[i];
                    max_prefix_sum[i] = prefix_sum[i];
                    continue;
                }
                min_prefix_sum[i] = min(min_prefix_sum[i + 1], prefix_sum[i]);
                max_prefix_sum[i] = max(max_prefix_sum[i + 1], prefix_sum[i]);
            }
            vector<vector<ll>> res = {min_prefix_sum, max_prefix_sum, prefix_sum};
            return res;
        };
        vector<vector<ll>> dp(n + 1, vector<ll>(m + 1, -INF));
        for(int i = 1; i <= m; i++) {
            dp[0][i] = 0;
        }
        cerr << "hi" << endl;
        for(int i = 1; i <= n; i++) {
            vector<vector<ll>> lg = calc_l(a[i]);
            vector<vector<ll>> rg = calc_r(a[i]);
            cerr << endl;
            cerr << "check a[" << i << "]" << endl;
            for(int j = 0; j <= m + 1; j++) {
                cerr << a[i][j] << ' ';
            }
            cerr << endl;
            cerr << "check prefix sum lg" << endl;
            for(int j = 0; j <= m + 1; j++) {
                cerr << lg[2][j] << ' ';
            }
            cerr << endl;
            cerr << "check min lg" << endl;
            for(int j = 0; j <= m + 1; j++) {
                cerr << lg[0][j] << ' ';
            }
            cerr << endl;
            cerr << "check max_lg" << endl;
            for(int j = 0; j <= m + 1; j++) {
                cerr << lg[1][j] << ' ';
            }
            cerr << endl;
            cerr << "check prefix sum rg" << endl;
            for(int j = 0; j <= m + 1; j++) {
                cerr << rg[2][j] << ' ';
            }
            cerr << endl;
            cerr << "check min rg" << endl;
            for(int j = 0; j <= m + 1; j++) {
                cerr << rg[0][j] << ' ';
            }
            cerr << endl;
            cerr << "check max_rg" << endl;
            for(int j = 0; j <= m + 1; j++) {
                cerr << rg[1][j] << ' ';
            }
            cerr << endl;
            for(int j = 1; j <= m; j++) {
                dp[i][j] = max({dp[i][j], dp[i - 1][j] + lg[1][j] - lg[0][j - 1], dp[i - 1][j] + rg[1][j] - rg[0][j + 1]});
            }
        }
        ll ans = -INF;
        for(int j = 1; j <= m; j++) {
            ans = max(ans, dp[n][j]);
        }
        cerr << "ans = ";
        cout << ans << endl;
    }
    return 0;
}