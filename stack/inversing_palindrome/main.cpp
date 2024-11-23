#include <bits/stdc++.h>
#define ll long long
#define endl '\n'
#define ff(i, x, y) for(int i = x; i <= y; i++)
#define fr(i, x, y) for(int i = x; i >= y; i--)
#define fi first
#define se second
#define pb push_back

using namespace std;

vector<pair<int,int>> check(string s) {
    vector<pair<int,int>> st;
    for(int i = 0; i < s.length(); i++) {
        if (st.size() == 0) st.push_back({i, s[i]});
        else {
            if (st.back().second == s[i]) {
                st.pop_back();
            } else {
                st.push_back({i, s[i]});
            }
        }
    }
    return st;
}

pair<int,int> solve(vector<pair<int,int>> a) {
    int odd = 0, even = 0;
    for(auto x : a) {
        if (x.second == '0') continue;
        if (x.first & 1) odd++;
        else even++;
    }
    return {odd, even};
}

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while(t--) {
        int n; cin >> n;
        string a, b; cin >> a >> b;
        vector<pair<int,int>> res_a = check(a);
        vector<pair<int,int>> res_b = check(b);
        auto solve_a = solve(res_a);
        auto solve_b = solve(res_b);
        if (solve_a.first == solve_b.first && solve_a.second == solve_b.second) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
    return 0;
}
