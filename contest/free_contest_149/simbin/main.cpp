#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int q; cin >> q;
    map<pair<int,int>, int> len;
    while(q--) {
        len.clear();
        int t, l, r, k; cin >> t >> l >> r >> k;
        auto dq_len = [&](auto dq_len, int l, int r) -> int {
            if (len.find({l, r}) != len.end()) return len[{l, r}];
            if (l == r) {
                len[{l, r}] = 1;
                return 1;
            }
            int mid = (l + r) / 2;
            int sz_l = dq_len(dq_len, l, mid);
            int sz_r = dq_len(dq_len, mid + 1, r);
            len[{l, r}] = 1 + sz_l + sz_r;
            return len[{l, r}];
        };
        dq_len(dq_len, l, r);
        k++;
        auto dq = [&](auto dq, int l, int r, int k) -> int {
            if (l == r) {
                if (k == 1) return 1;
                else return -1;
            }
            if (k == 1) {
                return r - l + 1;
            }
            k--;
            int mid = (l + r) / 2;
            int len_l = len[{l, mid}];
            if (len_l >= k) return dq(dq, l, mid, k);
            return dq(dq, mid + 1, r, k - len_l);
        };
        cout << dq(dq, l, r, k) << endl;
    }
    return 0;
}