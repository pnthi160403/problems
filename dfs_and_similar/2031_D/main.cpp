// https://codeforces.com/contest/2031/problem/D
#include <bits/stdc++.h>
#define ll long long
#define endl '\n'
#define ff(i, x, y) for(int i = x; i <= y; i++)
#define fr(i, x, y) for(int i = x; i >= y; i--)
#define fi first
#define se second
#define pb push_back

using namespace std;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while(t--) {
        int n; cin >> n;
        vector<int> a(n + 1);
        ff(i, 1, n) cin >> a[i];
        vector<int> min_id(n + 1), max_id(n + 1);
        min_id[n] = n;
        max_id[1] = 1;
        ff(i, 2, n) {
            if (a[max_id[i - 1]] < a[i]) max_id[i] = i;
            else max_id[i] = max_id[i - 1];
        }
        fr(i, n - 1, 1) {
            if (a[min_id[i + 1]] > a[i]) min_id[i] = i;
            else min_id[i] = min_id[i + 1];
        }
        vector<int> ans(n + 1, -1);
        vector<int> st;
        vector<bool> vis(n + 1, false);
        int max_val = -1;
        auto move = [&](auto move, int u) -> int {
            if (ans[u] != -1) return ans[u];
            max_val = max(max_val, a[u]);
            vis[u] = true;
            st.pb(u);
            if (u - 1 >= 1) {
                int max_cur_id = max_id[u - 1];
                if (a[max_cur_id] > a[u] && vis[max_cur_id] == false) return move(move, max_cur_id);
            }
            int l = u + 1, r = n, res = -1;
            while(l <= r) {
                int mid = (l + r) / 2;
                if (a[min_id[mid]] < a[u]) {
                    l = mid + 1;
                    res = mid;
                } else r = mid - 1;
            }
            if (res != -1 && vis[res] == false) return move(move, res);
            return max_val;
        };
        ff(i, 1, n) {
            if (ans[i] != -1) continue;
            int res = move(move, i);
            for(int x : st) ans[x] = res;
            st.clear();
        }
        ff(i, 1, n) cout << ans[i] << ' ';
        cout << endl;
    }
    return 0;
}