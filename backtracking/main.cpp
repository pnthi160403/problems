#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

const int INF = (int)1e9;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    const int n = 4;
    vector<string> a(n), b(n);
    for(string &x : a) cin >> x;
    for(string &x : b) cin >> x;
    vector<pair<int,int>> sa, sb;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if (a[i][j] == '1' && a[i][j] == b[i][j]) continue;
            if (a[i][j] == '1') sa.push_back({i, j});
            if (b[i][j] == '1') sb.push_back({i, j});
        }
    }
    vector<int> arr;
    for(int i = 0; i < sa.size(); i++) arr.push_back(i);
    int ans = INF;
    do {
        int res = 0;
        for(int i = 0; i < arr.size(); i++) {
            res += abs(sa[i].first - sb[arr[i]].first) + abs(sa[i].second - sb[arr[i]].second);
        }
        ans = min(ans, res);
    } while(next_permutation(arr.begin(), arr.end()));
    cout << ans;
    return 0;
}