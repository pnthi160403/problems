#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

const ll INF = (ll)1e18;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n, k; cin >> n >> k;
    vector<int> h(n + 1);
    for(int i = 1; i <= n; i++) cin >> h[i];
    auto f = [&](int height) -> pair<ll,int> {
        vector<ll> s(n + 1);
        for(int i = 1; i <= n; i++) {
            s[i] = abs(height - h[i]);
            s[i] += s[i - 1];
        }
        ll ans = s[k];
        int index = k;
        for(int i = k + 1; i <= n; i++) {
            ll res = s[i] - s[i - k];
            if (ans > res) {
                ans = res;
                index = i;
            }
        }
        return {ans, index};
    };
    ll ans = INF;
    int index = -1;
    int l = 0, r = (int)1e6, res = -1;
    while(l <= r) {
        int m1 = l + (r - l) / 3;
        int m2 = r - (r - l) / 3;
        auto[ans1, index1] = f(m1);
        auto[ans2, index2] = f(m2);
        if (ans1 >= ans2) {
            l = m1 + 1;
            if (ans2 < ans) {
                ans = ans2;
                index = index2;
                res = m2;
            }
        } else {
            r = m2 - 1;
        }
    }
    for(int i = index; i >= index - k + 1; i--) h[i] = res;
    cout << ans << endl;
    for(int i = 1; i <= n; i++) {
        cout << h[i] << endl;
    }
    return 0;
}