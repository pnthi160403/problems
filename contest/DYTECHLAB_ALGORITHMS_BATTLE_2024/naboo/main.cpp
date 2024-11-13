#include <bits/stdc++.h>
#define ll long long
#define endl '\n'
#define ff(i, x, y) for(int i = x; i <= y; i++)
#define fi first
#define se second

using namespace std;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while(t--) {
        string s; cin >> s;
        map<char,int> cnt;
        for(char c : s) cnt[c]++;
        int cnt_odd = 0;
        for(pair<char,int> x : cnt) if (x.second % 2 == 1) cnt_odd++;
        cout << ((cnt_odd == 1 || cnt.size() == 1) ? "Amidala" : "Skywalker") << endl;
    }
    return 0;
}