#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    ll n, m, s; cin >> n >> m >> s;
    auto get_max = [&](ll i, ll j) -> ll {
        return (i - 1) / s + (j - i) / s + 1;
    };
    ll cnt_n = 0, max_n = 0, cnt_m = 0, max_m = 0;
    for(int i = 1; i <= n; i++) {
        ll get_n = get_max(i, n);
        if (get_n == max_n) cnt_n++;
        else if (get_n > max_n) {
            max_n = get_n;
            cnt_n = 1;
        }
    }
    for(int i = 1; i <= m; i++) {
        ll get_m = get_max(i, m);
        if (get_m == max_m) cnt_m++;
        else if (get_m > max_m) {
            max_m = get_m;
            cnt_m = 1;
        }
    }
    cout << cnt_n * cnt_m;
    return 0;
}