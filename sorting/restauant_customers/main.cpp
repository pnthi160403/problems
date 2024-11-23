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
    int n; cin >> n;
    vector<pair<int,int>> a;
    ff(i, 1, n) {
        int x, y; cin >> x >> y;
        a.pb({x, 1});
        a.pb({y, -1});
    }
    sort(a.begin(), a.end());
    int res = 0;
    int cur = 0;
    for(auto[x, y] : a) {
        cur += y;
        res = max(res, cur);
    }
    cout << res;
    return 0;
}