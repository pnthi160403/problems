#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int t;
    cin >> t;
    while(t--) {
        int n, k;
        cin >> n >> k;
        map<int,int> cnt;
        for(int i = 0; i < n; i++) {
            int x;
            cin >> x;
            cnt[x]++;
        }
        vector<int> a;
        for(auto[val, num] : cnt) {
            a.push_back(val);
        }
        sort(a.begin(), a.end());
        int ans = 0, sum = 0;
        deque<int> d;
        for(int x : a) {
            if (d.size() == 0) {
                d.push_back(x);
                sum += cnt[x];
            } else {
                if (x - d.back() != 1) {
                    d.clear();
                    d.push_back(x);
                    sum = cnt[x];
                } else {
                    if (d.size() + 1 <= k) {
                        d.push_back(x);
                        sum += cnt[x];
                    } else {
                        int pop_val = d.front();
                        d.pop_front();
                        sum -= cnt[pop_val];
                        d.push_back(x);
                        sum += cnt[x];
                    }
                }
            }
            ans = max(ans, sum);
        }
        cout << ans << endl;
    }
    return 0;
}