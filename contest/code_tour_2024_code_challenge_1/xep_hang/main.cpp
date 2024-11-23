#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

struct FT {
    int n;
    vector<int> bit;
    void init(int _n) {
        n = _n;
        bit.assign(n + 2, 0);
    }
    void add(int x, int val) {
        for(int i = x; i <= n; i += i & -i) bit[i] += val;
    }
    int get(int x) {
        int res = 0;
        for(int i = x; i >= 1; i -= i & -i) res += bit[i];
        return res;
    }
    int get(int l, int r) {
        if (l - 1 < 1) return get(r);
        return get(r) - get(l - 1);
    }
};

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n, q; cin >> n >> q;
    vector<int> h(n + 1);
    vector<int> a;
    for(int i = 1; i <= n; i++) {
        cin >> h[i];
        a.push_back(h[i]);
    }
    vector<int> b(q + 1);
    for(int i = 1; i <= q; i++) {
        cin >> b[i];
        a.push_back(b[i]);
    }
    sort(a.begin(), a.end());
    vector<int> _a;
    _a.push_back(a[0]);
    for(int i = 1; i < a.size(); i++) {
        if (a[i] != a[i - 1]) _a.push_back(a[i]);
    }
    a = _a;
    FT ft;
    ft.init(a.size());
    vector<int> map_index(max(n, q) + 1, 0);
    for(int i = 1; i <= n; i++) {
        int index = lower_bound(a.begin(), a.end(), h[i]) - a.begin();
        map_index[i] = index;
    }
    for(int i = 1; i <= n; i++) {
        int index = map_index[i];
        ft.add(index + 1, 1);
    }
    for(int i = 1; i <= q; i++) {
        int index = lower_bound(a.begin(), a.end(), b[i]) - a.begin();
        map_index[i] = index;        
    }
    for(int i = 1; i <= q; i++) {
        int index = map_index[i];
        int get = ft.get(1, index + 1);
        cout << get + 1 << endl;
        ft.add(index + 1, 1);
    }
    return 0;
}