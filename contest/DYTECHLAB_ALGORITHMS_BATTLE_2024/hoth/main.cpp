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
        int n, k; cin >> n >> k;
        map<int,int> cnt;
        ff(i, 1, n) {
            int x; cin >> x;
            cnt[x]++;
        }
        if (cnt[k] <= 1) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
    return 0;
}