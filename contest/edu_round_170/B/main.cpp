#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

const int MOD = (int)1e9 + 7;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int t;
    cin >> t;
    vector<pair<int,int>> a(t);
    for(int i = 0; i < t; i++) {
        cin >> a[i].first;
    }
    for(int i = 0; i < t; i++) {
        cin >> a[i].second;
    }

    auto bpow = [&](ll a, ll b) -> ll {
        ll res = 1;
        while(b) {
            if (b & 1) {
                res *= a;
                res %= MOD;
            }
            a *= a;
            a %= MOD;
            b >>= 1;
        }
        return res;
    };

    for(auto[n, k] : a) {
        cout << bpow(2, k) << endl;
    }
    return 0;
}