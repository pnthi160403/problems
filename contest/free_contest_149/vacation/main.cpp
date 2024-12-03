#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n, d; cin >> n >> d;
    vector<string> a(n);
    for(string &x : a) cin >> x;
    int l = 0, r = l;
    int ans = 0;
    for(int i = 0; i < d; i++) {
        r = i;
        bool check = true;
        for(int j = 0; j < n; j++) {
            if (a[j][i] == 'x') check = false;
        }
        if (check == false) {
            l = i + 1;
            continue;
        } else {
            ans = max(ans, r - l + 1);
        }
    }
    cout << ans;
    return 0;
}