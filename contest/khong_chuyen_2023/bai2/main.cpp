#include <bits/stdc++.h>
#define ll long long
#define int ll
#define endl '\n'

using namespace std;

const int INF = (int)1e18;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n, m; cin >> n >> m;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) cin >> a[i];
    auto check_sub1 = [&]() -> bool {
        for(int i = 2; i <= n; i++) {
            if (a[i] < a[i - 1]) return false;
        }
        return true;
    };
    auto solve_sub1 = [&]() -> void {
        int max_range = 0, sum = 0;
        for(int i = 2; i <= n; i++) {
            max_range = max(max_range, a[i] - a[i - 1]);
            sum += a[i] - a[i - 1];
        }
        cout << sum - max_range + 1;
    };
    auto check_sub2 = [&]() -> bool {
        return max(n, m) <= (int)1e3;
    };
    auto solve_sub2 = [&]() -> void {
        auto check = [&](int x) -> int {
            int ans = 0;
            for(int i = 2; i <= n; i++) {
                if (a[i] == a[i - 1]) continue;
                if (a[i] == x) ans++;
                else if (a[i] > a[i - 1]) {
                    if (a[i - 1] >= x) ans += a[i] - a[i - 1];
                    else {
                        if (a[i] > x) ans += a[i] - x + 1;
                        else ans += a[i] - a[i - 1];
                    }
                } else if (a[i] < a[i - 1]) {
                    if (a[i - 1] >= x) ans += m - a[i - 1] + a[i];
                    else ans += 1 + m - x + a[i];
                }
            }
            return ans;
        };
        int ans = INF;
        for(int x = 0; x < m; x++) {
            ans = min(ans, check(x));
        }
        cout << ans;
    };
    if (check_sub1()) {
        solve_sub1();
    } else if (check_sub2()) {
        solve_sub2();
    }
    return 0;
}