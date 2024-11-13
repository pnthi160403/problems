// https://oj.vnoi.info/problem/fc073_dance?fbclid=IwY2xjawGdnwtleHRuA2FlbQIxMAABHd5M4TJ5u_jUrGIx6efqQdwcWUB_AbLFuW0i0_HfyFGPhyVUwClKC_0ypw_aem_7naqOzumaRhRshPiwvu4KQ
#include <bits/stdc++.h>
#define ll long long
#define endl '\n'
#define ff(i, x, y) for(int i = x; i <= y; i++)
#define pb push_back
#define fi first
#define se second
#define int ll

using namespace std;

const int MAX_H = 2000;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n, k; cin >> n >> k;
    vector<ll> boy(MAX_H + 1, 0), girl(MAX_H + 1, 0);
    ff(i, 1, n) {
        int x; cin >> x;
        if (x > 0) boy[x]++;
        else girl[abs(x)]++;
    }
    ff(i, 2, MAX_H) 
        boy[i] += boy[i - 1];
    ll ans = 0;
    ff(i, 0, MAX_H) {
        int min_h = i, max_h = min(i + k, MAX_H);
        if (i == 0) ans += girl[i] * boy[max_h];
        else ans += girl[i] * (boy[max_h] - boy[min_h - 1]);
    }
    cout << ans;
    return 0;
}