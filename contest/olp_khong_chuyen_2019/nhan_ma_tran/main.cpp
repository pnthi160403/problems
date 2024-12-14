#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int k, n, i, j;
    ll S;
    cin >> k >> n >> i >> j >> S;
    i--, j--;
    vector<vector<vector<ll>>> matrixs(k, vector<vector<ll>>(n, vector<ll>(n)));
    for(int ii = 0; ii < k; ii++) {
        for(int jj = 0; jj < n; jj++) {
            for(int kk = 0; kk < n; kk++) {
                cin >> matrixs[ii][jj][kk];
                matrixs[ii][jj][kk] %= S;
            }
        }
    }
    auto mul_matrix = [&](vector<vector<ll>> a, vector<vector<ll>> b) -> vector<vector<ll>> {
        vector<vector<ll>> res(n, vector<ll>(n));
        for(int jj = 0; jj < n; jj++) {
            for(int kk = 0; kk < n; kk++) {
                res[i][jj] = (res[i][jj] + a[i][kk] % S * b[kk][jj] % S) % S;
            }
        }
        return res;
    };
    vector<vector<ll>> res = matrixs[0];
    for(int t = 1; t < k; t++) {
        res = mul_matrix(res, matrixs[t]);
    }
    cout << res[i][j];
    return 0;
};