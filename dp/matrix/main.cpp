#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

const int MOD = (int)1e9 + 7;

struct MT {
    vector<vector<int>> m;
    MT(int x, int y) {
        m.assign(x, vector<int>(y, 0));
    }
};

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n;
    ll k;
    cin >> n >> k;
    MT a(n, n);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cin >> a.m[i][j];
        }
    }
    auto mul_matrix = [&](MT &a, MT &b) -> MT {
        int n = (int)a.m.size();
        int p = (int)a.m[0].size();
        int m = (int)b.m.size();
        MT res(n, m);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                for(int k = 0; k < p; k++) {
                    res.m[i][j] += (1ll * a.m[i][k] * b.m[k][j] % MOD);
                    res.m[i][j] %= MOD;
                }
            }
        }
        return res;
    };
    auto bs_matrix = [&](MT &a, ll b) -> MT {
        int sz = (int)a.m.size();
        MT res(sz, sz);
        for(int i = 0; i < sz; i++)
            res.m[i][i] = 1ll;
        while(b) {
            if (b & 1) {
                res = mul_matrix(res, a);
            }
            a = mul_matrix(a, a);
            b /= 2;
        }
        return res;
    };
    MT res = bs_matrix(a, k);
    int ans = 0;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++) {
            ans += res.m[i][j];
            ans %= MOD;
        }
    cout << ans;
    return 0;
}
