#include <bits/stdc++.h>
#define ll long long
#define int ll
#define endl '\n'

using namespace std;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n, m, c; cin >> n >> m >> c;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) cin >> a[i];
    multiset<int> ms;
    for(int i = 1; i < m; i++) {
        ms.insert(a[i]);
    }
    bool check = false;
    for(int i = m; i <= n; i++) {
        ms.insert(a[i]);
        int min_val = *ms.begin();
        int max_val = *ms.rbegin();
        int diff = abs(max_val - min_val);
        if (diff <= c) {
            cout << i - m + 1 << endl;
            check = true;
        }
        auto it = ms.find(a[i - m + 1]);
        ms.erase(it);
    }
    if (check == false) {
        cout << "NONE";
    }
    return 0;
}