#include <bits/stdc++.h>
#define ll long long
#define endl '\n'
#define ff(i, x, y) for(int i = x; i <= y; i++)
#define fi first
#define se second

using namespace std;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while(t--) {
        int n, m, L; cin >> n >> m >> L;
        vector<pair<int,int>> a;
        map<int,int> nextl;
        for(int i = 0; i < n; i++) {
            int l, r; cin >> l >> r;
            nextl[l] = r;
            a.push_back({l, -1});
        }
        for(int i = 0; i < m; i++) {
            int x, p; cin >> x >> p;
            a.push_back({x, p});
        }
        sort(a.begin(), a.end());
        // cerr << "check array a" << endl;
        // for(auto[val, type] : a) {
        //     cerr << "val = " << val << " and type = " << type << endl;
        // }
        // cerr << endl;
        int ll sum_power = 1;
        int ans = 0;
        bool ok = true;
        multiset<int> list_power;
        for(auto[val, type] : a) {
            if (type != -1) {    
                list_power.insert(type);
            } else {
                int l = val, r = nextl[l];
                int val_lr = r - l + 2;
                while(sum_power < val_lr && list_power.size()) {
                    int _power = *list_power.rbegin();
                    sum_power += _power;
                    // cerr << "pre delete" << endl;
                    // for(int x : list_power) cerr << x << ' ';
                    // cerr << endl;
                    list_power.erase(list_power.find(_power));
                    // cerr << "suf delete" << endl;
                    // for(int x : list_power) cerr << x << ' ';
                    // cerr << endl;
                    ans++;
                }
                if (sum_power < val_lr) {
                    ok = false;
                }
            }
        }
        if(ok) {
            cout << ans << endl;
        } else {
            cout << -1 << endl;
        }
    }
    return 0;
}