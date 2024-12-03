#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

const int N = (int)1e5;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n; cin >> n;
    map<int,int> cnt;
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        cnt[x]++;
    }
    ll ans = 0;
    for(auto[val, _cnt] : cnt) {
        ans += 1ll * _cnt * (_cnt - 1) / 2;
        if (val % 2 == 1 && cnt.find(val - 1) != cnt.end()) {
            ans += 1ll * _cnt * cnt[val - 1];
        }
    }
    cout << ans;
    return 0;
}