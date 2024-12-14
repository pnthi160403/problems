#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n, q; cin >> n >> q;
    string s; cin >> s;
    s = "#" + s;
    vector<vector<int>> cnt(n + 1, vector<int>(26));
    for(int i = 1; i <= n; i++) {
        int x = s[i] - 'a';
        cnt[i][x] = 1;
        for(int x = 0; x < 26; x++) cnt[i][x] += cnt[i - 1][x];
    }
    // cerr << "check cnt" << endl;
    // for(int i = 1; i <= n; i++) {
        // cerr << "s[" << i << "] = " << s[i] << endl;
        // cerr << "cnt[" << i << "][" << s[i] << "] = " << cnt[i][s[i] - 'a'] << endl;
    // }
    // cerr << endl;
    while(q--) {
        int l, r; cin >> l >> r;
        l++, r++;
        vector<int> tmp_cnt(26);
        int odd = 0;
        for(int i = 0; i < 26; i++) {
            tmp_cnt[i] = cnt[r][i] - cnt[l - 1][i];
            odd += (tmp_cnt[i] & 1);
        }
        // cerr << "l = " << l << " and r = " << r << endl;
        // cerr << "odd = " << odd << endl;
        if (odd & 1) {
            cout << (odd - 1) / 2 << endl;
        } else {
            cout << odd / 2 << endl;
        }
    }
    return 0;
}