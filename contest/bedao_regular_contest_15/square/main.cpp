#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    ll n; cin >> n;
    ll sum = n * (n - 1) / 2;
    for(ll i = 1; i <= (int)1e7; i++) {
        ll k = i * i - sum - n;
        if (k >= 1) {
            for(int j = 1; j <= n - 1; j++) {
                cout << j << ' ';
            }
            cout << n + k;
            return 0;
        }
    }
    return 0;
}