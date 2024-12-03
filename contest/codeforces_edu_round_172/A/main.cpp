#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while(t--) {
        int n, k; cin >> n >> k;
        vector<int> a(n);
        for(int &x : a) cin >> x;
        sort(a.begin(), a.end());
        reverse(a.begin(), a.end());
        int i = 0;
        int sum = 0;
        while(i < a.size()) {
            if (sum + a[i] > k) break;
            sum += a[i];
            i++;
        }
        cout << k - sum << endl;
    }
    return 0;
}