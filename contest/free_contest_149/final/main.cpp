#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n, m, k, q; cin >> n >> m >> k >> q;
    vector<int> ms;
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        ms.push_back(x);
    }
    sort(ms.begin(), ms.end());
    for(int i = 0; i < m; i++) {
        int cnt = 0;
        vector<int> new_ms;
        for(int x : ms) {
            cnt++;
            if (cnt > k) {
                new_ms.push_back(x);
            } else {
                new_ms.push_back(x + 1);
            }
        }
        ms.clear();
        for(int x : new_ms) ms.push_back(x);
        sort(ms.begin(), ms.end());
        new_ms.clear();
    }
    vector<int> a;
    for(int x : ms) a.push_back(x);
    reverse(a.begin(), a.end());
    int cnt = 1;
    int ans = 1;
    for(int i = 1; i < a.size(); i++) {
        if (a[i] == a[i - 1]) {
            ans++;
        } else {
            cnt++;
            if (cnt > q) {
                break;
            } else {
                ans++;
            }
        }
    }
    cout << ans;
    return 0;
}