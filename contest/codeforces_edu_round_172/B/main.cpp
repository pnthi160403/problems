#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while(t--) {
        int n; cin >> n;
        vector<int> d(n + 1);
        for(int i = 1; i <= n; i++) {
            int x; cin >> x;
            d[x]++;
        }
        int cnt = 0, sum = 0;
        for(int i = 1; i <= n; i++) {
            if (d[i] == 0) continue;
            sum++;
            if (d[i] == 1) cnt++;
        }
        if (cnt & 1) {
            cout << (cnt + 1) + (sum - cnt) << endl;
        } else {
            cout << cnt + (sum - cnt) << endl;
        }
    }
    return 0;
}