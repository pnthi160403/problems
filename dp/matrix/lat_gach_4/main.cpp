// https://oj.vnoi.info/problem/latgach4
#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

const ll MOD = (ll)(111539786);

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    auto mul_matrix = [&](vector<vector<ll>> &a, vector<vector<ll>> &b) -> vector<vector<ll>> {
        int n = a.size();
        int m = a[0].size();
        int p = b.size();
        vector<vector<ll>> res(n, vector<ll>(p, 0));
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                for(int k = 0; k < p; k++) {
                    res[i][j] += a[i][k] * b[k][j] % MOD;
                    res[i][j] %= MOD;
                }
            }
        }
        return res;
    };
    auto bs = [&](vector<vector<ll>> &a, ll b) -> vector<vector<ll>> {
        int n = a.size();
        vector<vector<ll>> res(n, vector<ll>(n));
        for(int i = 0; i < n; i++) res[i][i] = 1;
        while(b) {
            if (b & 1) {
                res = mul_matrix(res, a);
            }
            a = mul_matrix(a, a);
            b >>= 1;
        }
        return res;
    };
    int t; cin >> t;
    while(t--) {
        int n; cin >> n;
        if (n <= 2) {
            cout << n << endl;
            continue;
        }
        vector<vector<ll>> a = {
            {1, 1},
            {1, 0}
        };
        vector<vector<ll>> b = {
            {2},
            {1}
        };
        a = bs(a, n - 2);
        vector<vector<ll>> res = mul_matrix(a, b);
        cout << res[0][0] << endl;
    }
    return 0;
}