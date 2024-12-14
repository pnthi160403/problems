#include <bits/stdc++.h>
#define ll long long
#define int ll
#define endl '\n'

using namespace std;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n, m; cin >> n >> m;
    vector<int> v(n + 1), h(n + 1), s(n + 1), rs(n + 1);
    for(int i = 1; i <= n; i++) cin >> v[i];
    for(int i = 1; i <= n; i++) cin >> h[i];
    for(int i = 1; i <= n; i++) {
        s[i] = s[i - 1] + h[i];
    }
    rs[n] = h[n];
    for(int i = n - 1; i >= 1; i--) {
        rs[i] = rs[i + 1] + h[i];
    }
    vector<int> minl(n + 1), minr(n + 1);
    for(int i = 1; i <= n; i++) {
        minl[i] = h[i] * v[i] - s[i];
    }
    for(int i = 1; i <= n; i++) minl[i]++;
    for(int i = n; i >= 1; i--) {
        minr[i] = h[i] * (m - v[i]) - rs[i];
    }
    for(int i = n; i >= 1; i--) minr[i]++;
    cerr << "check minl" << endl;
    for(int i = 0; i <= n; i++) {
        cerr << "minl[" << i << "] = " << minl[i] << endl;
    }
    cerr << endl;
    reverse(minr.begin() + 1, minr.end());
    cerr << "check minr" << endl;
    for(int i = 0; i <= n; i++) {
        cerr << "minr[" << i << "] = " << minr[i] << endl;
    }
    cerr << endl;
    int q; cin >> q;
    while(q--) {
        int k; cin >> k;
        int find_minl = upper_bound(minl.begin(), minl.end(), k) - minl.begin() - 1;
        int find_minr = upper_bound(minr.begin(), minr.end(), k) - minr.begin() - 1;
        cerr << "k = " << k << endl;
        cerr << "find_minl = " << find_minl << endl;
        cerr << "find_minr = " << find_minr << endl;
        cerr << "minl = " << minl[find_minl] << endl;
        cerr << "minr = " << minr[find_minr] << endl;
        cout << min(n, (find_minl + find_minr)) << endl;
    }
    return 0;
}