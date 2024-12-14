#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    double u, v; cin >> u >> v;
    double ans = (u * u + v * v) / 4;
    cout << fixed << setprecision(2) << ans;
    return 0;
}