#include <bits/stdc++.h>
#define ll long long
#define endl '\n'
#define ff(i, x, y) for(int i = x; i <= y; i++)
#define fi first
#define se second

using namespace std;

const int N = (int)1e3;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while(t--) {
        int n; cin >> n;
        int S = 0, offset = 2 * N;
        vector<int> sum(4 * N + 1, 0);
        ff(i, 1, n) {
            int x, y, h; cin >> x >> y >> h;
            sum[x - y + offset] += h;
            S += h;
        }
        auto check = [&]() -> bool {
            int cur_sum = 0;
            ff(i, -2 * N, 2 * N) {
                int j = i + offset;
                if (S - cur_sum - sum[j] == cur_sum) return true;
                cur_sum += sum[j];
                if (S - cur_sum == cur_sum) return true;
            }
            return false;
        };
        cout << (check() == true ? "YES" : "NO") << endl;
    }
    return 0;
}