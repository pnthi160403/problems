#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

const int MOD = (int)1e9 + 7;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n;
    ll k;
    cin >> n >> k;
    vector<vector<ll>> a(n, vector<ll>(n));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }
    auto mul_matrix = [&](vector<vector<ll>> a, vector<vector<ll>> b) -> vector<vector<ll>> {
        vector<vector<ll>> c(n, vector<ll>(n, 0));
        for(int i = 0; i < a.size(); i++) {
            for(int j = 0; j < b.size(); j++) {
                for(int k = 0; k < a[i].size(); k++) {
                    c[i][j] += a[i][k] * b[k][j];
                    c[i][j] %= MOD;
                }
            }
        }
        return c;
    };
    auto bs_matrix = [&](vector<vector<ll>> a, ll b) -> vector<vector<ll>> {
        vector<vector<ll>> res(a.size(), vector<ll>(a[0].size(), 0));
        for(int i = 0; i < a.size(); i++) res[i][i] = 1;
        while(b) {
            if (b & 1)
                res = mul_matrix(res, a);
            b /= 2;
            a = mul_matrix(a, a);
        }
        return res;
    };
    vector<vector<ll>> res = bs_matrix(a, k);
    ll ans = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            ans += res[i][j];
            ans %= MOD;
        }
    }
    cout << ans;
    return 0;
}