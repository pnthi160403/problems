#include <bits/stdc++.h>
#define ll long long
#define int ll
#define endl '\n'

using namespace std;

struct Cow {
    int x, y, r;
};

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n, a, b; cin >> n >> a >> b;
    vector<Cow> cows;
    for(int i = 0; i < n; i++) {
        int x, y, r; cin >> x >> y >> r;
        cows.push_back({x, y, r});
    }
    auto dist = [&](int x1, int y1, int x2, int y2) -> ll {
        return 1ll * (x1 - x2) * (x1 - x2) + 1ll * (y1 - y2) * (y1 - y2);
    };
    vector<ll> d(n);
    for(int i = 0; i < n; i++) {
        auto[x, y, r] = cows[i];
        d[i] = dist(a, b, x, y);
    }
    auto check = [&](int l) -> bool {
        for(int i = 0; i < n; i++) {
            auto[x, y, r] = cows[i];
            if (1ll * (r + l) * (r + l) >= d[i]) return false;
        }
        return true;
    };
    int l = 0, r = (int)2e9, res = -1;
    while(l <= r) {
        int mid = (l + r) / 2;
        if (check(mid)) {
            res = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    cout << res;
    return 0;
};