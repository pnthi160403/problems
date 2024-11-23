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
        int n; cin >> n;
        if (n <= 4) {
            cout << -1 << endl;
        } else {
            for(int i = 2; i <= n; i += 2) {
                if (i != 4) {
                    cout << i << ' ';
                }
            }
            cout << 4 << ' ';
            if (n <= 4) {
                cout << endl;
                continue;
            }
            cout << 5 << ' ';
            for(int i = 1; i <= n; i += 2) {
                if (i != 5) {
                    cout << i << ' ';
                }
            }
            cout << endl;
        }
    }
    return 0;
}