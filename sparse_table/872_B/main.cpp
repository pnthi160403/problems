#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

const int INF = (int)1e9;
const int LOG = 20;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for(int &x : a) cin >> x;
    if (k == 1) {
        int min_val = INF;
        for(int x : a)
            min_val = min(min_val, x);
        cout << min_val;
    } else if (k > 2) {
        int max_val = -INF;
        for(int x : a)
            max_val = max(max_val, x);
        cout << max_val;
    } else {
        vector<vector<int>> st(LOG + 1, vector<int>(n, INF));
        for(int i = 0; i < n; i++) st[0][i] = a[i];
        for(int i = 1; i <= LOG; i++)
            for(int j = 0; j + (1 << i) <= n; j++)
                st[i][j] = min(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
        vector<ll> lg(n);
        lg[1] = 0;
        for(int i = 2; i < n; i++) lg[i] = lg[i / 2] + 1;
        // range minimum queries
        auto get_min = [&](int l, int r) -> int {
            int i = lg[r - l + 1];
            return min(st[i][l], st[i][r - (1 << i) + 1]);
        };
        // range sum queries
        auto get_sum = [&](int l, int r) -> ll {
            ll sum = 0;
            for(int i = LOG; i >= 0; i--) {
                if ((1 << i) <= r - l + 1) {
                    sum += st[i][l];
                    l += (1 << i);
                }
            }
            return sum;
        };
        int ans = -INF;
        for(int i = 0; i < n - 1; i++) {
            int cur_ans = max(get_min(0, i), get_min(i + 1, n - 1));
            ans = max(ans, cur_ans);
        }
        cout << ans;
    }
    return 0;
}