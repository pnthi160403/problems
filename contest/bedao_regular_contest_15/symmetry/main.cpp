#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int l, r; cin >> l >> r;
    ll sum = 0;
    auto dq = [&](auto dq, int i, vector<int> &nums, int n) {
        if (i == n) {
            ll n1 = 0;
            for(int x : nums) {
                n1 = n1 * 10 + x;
            }
            ll n2 = n1;
            for(int j = i - 1; j >= 0; j--) {
                n1 = n1 * 10 + nums[j];
            }
            if (n1 >= l && n1 <= r) {
                sum += n1;
            }
            for(int j = i - 2; j >= 0; j--) {
                n2 = n2 * 10 + nums[j];
            }
            if (n2 >= l && n2 <= r) {
                sum += n2;
            }
            return;
        }
        int min_d = 0;
        if (i == 0) min_d = 1;
        for(int d = min_d; d <= 9; d++) {
            nums.push_back(d);
            dq(dq, i + 1, nums, n);
            nums.pop_back();
        }
    };
    for(int n = 1; n <= 5; n++) {
        vector<int> nums;
        dq(dq, 0, nums, n);
    }
    cout << sum;
    return 0;
}