#include <bits/stdc++.h>
#define ll long long
#define endl '\n'
#define ff(i, x, y) for(int i = x; i <= y; i++)
#define fi first
#define se second
#define pb push_back

using namespace std;

const int INF = (int)1e9;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while(t--) {
        int n, k; cin >> n >> k;
        vector<int> a(n + 1);
        ff(i, 1, n) cin >> a[i];
        deque<pair<int,int>> q;
        vector<int> ans;
        ff(i, 1, n) {
            while(q.size() && q.front().fi + k <= i) q.pop_front();
            while(q.size() && q.back().se >= a[i]) q.pop_back();
            q.pb({i, a[i]});
            if (i >= k) ans.pb(q.front().se);
        }
        for(int x : ans) cout << x << ' ';
        cout << endl;
    }
    return 0;
}