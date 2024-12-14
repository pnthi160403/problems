// https://dmoj.ctu.edu.vn/problem/olp2024_query
#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n, m; cin >> n >> m;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) cin >> a[i];
    while(m--) {
        int l, r, _a, _b; cin >> l >> r >> _a >> _b;
        int cnt = 0;
        set<int> s;
        for(int i = l; i <= r; i++) {
            // cerr << a[i] << ' ';
            if (a[i] >= _a && a[i] <= _b) {
                s.insert(a[i]);
                cnt++;
            }
        }
        // cerr << endl;
        cout << cnt << ' ' << s.size() << endl;
    }
    return 0;
}