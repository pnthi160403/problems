#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n, m; cin >> n >> m;
    vector<int> v(n + 1), h(n + 1);
    for(int i = 1; i <= n; i++) cin >> v[i];
    for(int i = 1; i <= n; i++) cin >> h[i];

    auto get_water = [&]() -> vector<ll> {
        vector<ll> water(n + 1);
        vector<int> pre(n + 1);
        v[0] = 0;
        h[0] = (int)1e9;
        vector<ll> s(n + 1);
        s[0] = h[0];
        for(int i = 1; i <= n; i++) s[i] = s[i - 1] + h[i];
        water[0] = 0;
        vector<int> st;
        st.push_back(0);
        for(int i = 1; i <= n; i++) {
            while((int)st.size() != 0 && h[st.back()] < h[i]) st.pop_back();
            pre[i] = st.back();
            st.push_back(i);
        }
        for(int i = 1; i <= n; i++) {
            int j = pre[i];
            water[i] = water[j] + 1ll * (v[i] - v[j]) * h[i] - (s[i] - s[j]);
        }
        for(int i = 1; i <= n; i++) water[i]++;
        return water;
    };

    vector<ll> water_l = get_water();
    reverse(v.begin() + 1, v.end());
    reverse(h.begin() + 1, h.end());
    for(int i = 1; i <= n; i++) v[i] = m - v[i];
    vector<ll> water_r = get_water();
    int q; cin >> q;
    while(q--) {
        ll k; cin >> k;
        int l = upper_bound(water_l.begin(), water_l.end(), k) - water_l.begin() - 1;
        int r = upper_bound(water_r.begin(), water_r.end(), k) - water_r.begin() - 1;
        cout << min(l + r, n) << endl;
    }
    return 0;
}