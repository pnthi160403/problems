#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

ll INF = (ll)1e18;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int k; cin >> k;
    vector<ll> p(k);
    for(ll &x : p) cin >> x;
    ll C; cin >> C;
    ll ans = -1;
    for(ll i = 1; i <= (ll)1e6; i++) {
        if (i * i * i == C) {
            ans = i;
            break;
        }
    }
    cout << ans;
    return 0;
}