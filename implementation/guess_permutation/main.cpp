// https://www.hackerearth.com/practice/algorithms/searching/linear-search/practice-problems/algorithm/permutation-swaps-2-01766245/
#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        vector<int> a(n + 1, 0);
        int min_val = 0;
        for(int i = 1; i <= n; i++) {
            cin >> a[i];
            a[i] += a[i - 1];
            min_val = min(min_val, a[i]);
        }
        int add = 1 - min_val;
        for(int i = 0; i <= n; i++) {
            a[i] += add;
        }
        vector<int> b;
        for(int x : a)
            b.push_back(x);
        sort(a.begin(), a.end());
        bool ok = true;
        for(int i = 1; i <= n; i++) {
            if (a[i - 1] < a[i])
                continue;
            ok = false;
            break;
        }
        if (a.back() != a.size()) {
            ok = false;
        }
        if (ok == false) {
            cout << -1 << endl;
        } else {
            for(int x : b)
                cout << x << ' ';
            cout << endl;
        }
    }
    return 0;
}