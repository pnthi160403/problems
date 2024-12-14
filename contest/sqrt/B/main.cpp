#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while(t--) {
        int k; cin >> k;
        if (k == 1) {
            cout << "2 2" << endl;
        } else if (k < (int)1e9) {
            cout << k << ' ' << k + 1 << endl;
        } else {
            cout << "-1 -1" << endl;
        }
    }
    return 0;
}