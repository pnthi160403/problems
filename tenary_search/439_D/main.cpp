// https://codeforces.com/problemset/problem/439/D
#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

const ll INF = (ll)1e18;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int na, nb;
    cin >> na >> nb;
    vector<int> a(na), b(nb);
    for(int &x : a) cin >> x;
    for(int &x : b) cin >> x;

    auto f = [&](int val) -> ll {
        ll cost = 0;
        for(int x : a)
            if (x < val)    
                cost += val - x;
        for(int x : b)
            if (x > val)
                cost += x - val;
        return cost;
    };
    int l = 1, r = (int)1e9, ans = INF;
    while(l <= r) {
        int m1 = l + (r - l) / 3;
        int m2 = r - (r - l) / 3;
        ll f1 = f(m1);
        ll f2 = f(m2);
        if (f1 >= f2) {
            l = m1 + 1;
            ans = min(ans, f2);
        } else {
            r = m2 - 1;
        }
    }
    cout << ans;
    return 0;
}