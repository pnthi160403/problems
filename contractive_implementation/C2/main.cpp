// https://codeforces.com/contest/2021/problem/C2
#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int t;
    cin >> t;
    while(t--) {
        int n, m, q;
        cin >> n >> m >> q;
        vector<int> a(n + 1), b(m + 1), pos(n + 1), min_index(n + 1);
        for(int i = 1; i <= n; i++) {
            cin >> a[i];
            pos[a[i]] = i;
        }
        vector<set<int>> indexs(n + 1);
        for(int i = 1; i <= m; i++) {
            cin >> b[i];
            indexs[b[i]].insert(i);
        }
        for(int i = 1; i <= n; i++) {
            if (indexs[a[i]].empty()) {
                min_index[i] = m + 1;
            } else {
                min_index[i] = *(indexs[a[i]].begin());
            }
        }

        int cnt = 0;
        for(int i = 1; i <= n - 1; i++) {
            if (min_index[i] > min_index[i + 1])
                cnt++;
        }
        auto print_ans = [&]() -> void {
            cout << (cnt == 0 ? "YA" : "TIDAK") << endl;
        };
        print_ans();
        
        auto update = [&](int index, int type) -> void {
            int pre_index = index - 1;
            int suf_index = index + 1;
            if (type == 0) {
                if (pre_index >= 1) {
                    cnt -= min_index[pre_index] > min_index[index];
                }
                if (suf_index <= n) {
                    cnt -= min_index[suf_index] < min_index[index];
                }
            } else {
                if (pre_index >= 1) {
                    cnt += min_index[pre_index] > min_index[index];
                }
                if (suf_index <= n) {
                    cnt += min_index[suf_index] < min_index[index];
                }
            }
        };

        while(q--) {
            int id, new_val;
            cin >> id >> new_val;
            int old_val = b[id];
            if (new_val == old_val) {
                print_ans();
                continue;
            }
            b[id] = new_val;
            update(pos[new_val], 0);
            indexs[new_val].insert(id);
            min_index[pos[new_val]] = *(indexs[new_val].begin());
            update(pos[new_val], 1);
            update(pos[old_val], 0);
            indexs[old_val].erase(id);
            if (indexs[old_val].size()) {
                min_index[pos[old_val]] = *(indexs[old_val].begin());
            } else {
                min_index[pos[old_val]] = m + 1;
            }
            update(pos[old_val], 1);
            print_ans();
        }
    }
    return 0;
}