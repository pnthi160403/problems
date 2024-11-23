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
        int k; cin >> k;
        map<int,int> cnt;
        for(int i = 0; i < k; i++) {
            int x; cin >> x;
            cnt[x]++;
        }
        k -= 2;
        int n, m;
        for(pair<int,int> x : cnt) {
            if (k % x.first) continue;
            if (x.first != k / x.first) {
                if (cnt[x.first] > 0 && cnt[k / x.first] > 0) {
                    n = x.first;
                    m = k / x.first;
                }
            } else {
                if (cnt[x.first] >= 2) {
                    n = x.first;
                    m = x.first;
                }
            }
        }
        cout << n << ' ' << m << endl;
    }
    return 0;
}