#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while(t--) {
        int n; cin >> n;
        vector<ll> a(n);
        for(ll &x : a) cin >> x;
        // cerr << "check array a" << endl;
        // for(int i = 0; i < n; i++) {
        //     cerr << "a[" << i << "] = " << a[i] << endl;
        // }
        // cerr << endl;
        auto solve = [&](int index) -> int {
            if (a[index] != 1) return index + 1;
            // cerr << "check with index = " << index << endl;
            ll power = 1;
            for(int i = index; i < n; i++) {
                // cerr << "i = " << i << " and power = " << power << endl;
                if (a[i] <= power) {
                    power += a[i];
                } else {
                    return i;
                }
            }
            for(int i = index - 1; i >= 0; i--) {
                // cerr << "i = " << i << " and power = " << power << endl;
                if (a[i] <= power) {
                    power += a[i];
                } else {
                    return -1;
                }
            }
            return n + 1;
        };
        bool check = false;
        for(int i = 0; i < n; i++) {
            int index = solve(i);
            if (index == -1) break;
            if (index == n + 1) {
                check = true;
                break;
            }
            i = index - 1;
        }
        cout << (check == true ? "YES" : "NO") << endl;
    }
    return 0;
}