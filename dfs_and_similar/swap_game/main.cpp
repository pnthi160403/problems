// https://cses.fi/problemset/task/1670
#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    string arr = "123456789";
    vector<string> numbers;
    do {
        numbers.push_back(arr);
    } while(next_permutation(arr.begin(), arr.end()));
    sort(numbers.begin(), numbers.end());
    vector<vector<int>> map_cnt(3, vector<int>(3));
    int cnt = 0;
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            map_cnt[i][j] = cnt++;
        }
    }
    vector<int> dx = {-1, 1, 0, 0}, dy = {0, 0, -1, 1};
    vector<vector<int>> adj(numbers.size() + 1, vector<int>());
    vector<vector<int>> l;
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            for(int d = 0; d < 4; d++) {
                int ii = i + dx[d];
                int jj = j + dy[d];
                if (ii < 0 || ii >= 3 || jj < 0 || jj >= 3) continue;
                l.push_back({i, j, ii, jj});
            }
        }
    }
    int _cnt = 0;
    for(string number : numbers) {
        string tmp = number;
        vector<vector<bool>> used(3, vector<bool>(3, false));
        for(auto _l : l) {
            int i = _l[0], j = _l[1], ii = _l[2], jj = _l[3];
            if (used[ii][jj]) continue;
            _cnt++;
            int x = map_cnt[i][j];
            int y = map_cnt[ii][jj];
            swap(tmp[x], tmp[y]);
            int u = lower_bound(numbers.begin(), numbers.end(), number) - numbers.begin();
            int v = lower_bound(numbers.begin(), numbers.end(), tmp) - numbers.begin(); 
            adj[u].push_back(v);
            swap(tmp[x], tmp[y]);
            used[i][j] = true;
        }
    }
    int t = lower_bound(numbers.begin(), numbers.end(), "123456789") - numbers.begin();
    string tmp = "";
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            char c; cin >> c;
            tmp += c;
        }
    }
    int s = lower_bound(numbers.begin(), numbers.end(), tmp) - numbers.begin();
    auto bfs = [&](int s, int t) -> int {
        int n = numbers.size();
        vector<bool> used(n + 1, false);
        queue<pair<int,int>> q;
        q.push({s, 0});
        used[s] = true;
        while(q.size()) {
            auto[u, cost] = q.front();
            q.pop();
            if (u == t) return cost;
            for(int v : adj[u]) {
                if (used[v]) continue;
                used[v] = true;
                q.push({v, cost + 1});
            }
        }
        return -1;
    };
    cout << bfs(s, t);
    return 0;
}