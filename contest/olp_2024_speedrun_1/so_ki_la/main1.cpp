#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    ll l, r;
    cin >> l >> r;
    int ans = 0;
    for(ll x = l; x <= r; x++) {
        vector<int> numbers;
        ll tmp = x;
        while(tmp) {
            numbers.push_back(tmp % 10);
            tmp /= 10;
        }
        vector<int> a = {2, 3, 5, 7};
        int cnt = 0;
        for(int y : a) {
            if (numbers[0] == y) {
                cnt++;
                break;
            }
        }
        for(int y : a) {
            if (numbers.back() == y) {
                cnt++;
                break;
            }
        }
        if (cnt < 2) continue;
        int sum = 0;
        for(int y : numbers) sum += y;
        ans += sum % 3 == 0;
    }
    cout << ans;
    return 0;
}