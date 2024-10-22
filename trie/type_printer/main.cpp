#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

const int N = (int)1e5;

struct Node {
    int c[26]; // index of child node
    int cnt, exist; // cnt prefix string and number string of node
};

struct Trie {
    vector<Node> trie;
    int cur; // number node in trie

    Trie(int _n) : cur(0), trie(_n) {
        new_node();
    }

    int new_node() {
        trie[cur].cnt = trie[cur].exist = 0;
        for(int i = 0; i < 26; i++) trie[cur].c[i] = -1;
        return cur++;
    }

    void add_string(string &s) {
        int cur_node = 0;
        for(int i = 0; i < s.length(); i++) {
            if (trie[cur_node].c[s[i] - 'a'] == -1) trie[cur_node].c[s[i] - 'a'] = new_node();
            cur_node = trie[cur_node].c[s[i] - 'a'];
            trie[cur_node].cnt++;
        }
        trie[cur_node].exist++;
    }

    bool del_string(int cur_node, string &s, int i) {
        if (i == s.length()) trie[cur_node].exist--;
        else {
            int x = s[i] - 'a';
            bool deleted_all_prefix = del_string(trie[cur_node].c[x], s, i + 1);
            if (deleted_all_prefix) trie[cur_node].c[x] = -1;
        }

        if (cur_node != 0) {
            trie[cur_node].cnt--;
            if (trie[cur_node].cnt == 0) return true;
        }
        return false;
    }

    bool find_string(string &s) {
        int cur_node = 0;
        for(int i = 0; i < s.length(); i++) {
            if (trie[cur_node].c[s[i] - 'a'] == -1) return false;
            cur_node = trie[cur_node].c[s[i] - 'a'];
        }
        return trie[cur_node].exist > 0;
    }
};

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n;
    cin >> n;
    Trie t(N * 21);
    for(int i = 0; i < n; i++) {
        string s; cin >> s;
        t.add_string(s);
    }
    vector<int> h(N * 21, 0), max_h(N * 21, 0);
    auto dfs_h = [&](auto dfs_h, int cur_node) -> void {
        for(int i = 0; i < 26; i++) {
            int v = t.trie[cur_node].c[i];
            if (v == -1) continue;
            h[v] = h[cur_node] + 1;
            dfs_h(dfs_h, v);
        }
        max_h[cur_node] = h[cur_node];
        for(int i = 0; i < 26; i++) {
            int v = t.trie[cur_node].c[i];
            if (v == -1) continue;
            max_h[cur_node] = max(max_h[cur_node], max_h[v]);
        }
    };
    dfs_h(dfs_h, 0);
    string res = "";
    auto dfs = [&](auto dfs, int cur_node) -> void {
        for(int i = 0; i < t.trie[cur_node].exist; i++)
            res += 'P';
        for(int i = 0; i < 26; i++) {
            int v = t.trie[cur_node].c[i];
            if (v == -1) continue;
            if (max_h[v] < max_h[cur_node]) {
                res += (char)(i + 'a');
                dfs(dfs, v);
            }
        }
        for(int i = 0; i < 26; i++) {
            int v = t.trie[cur_node].c[i];
            if (v == -1) continue;
            if (max_h[v] == max_h[cur_node]) {
                res += (char)(i + 'a');
                dfs(dfs, v);
            }
        }
        res += '-';
    };
    dfs(dfs, 0);
    while(res.back() == '-') res.pop_back();
    cout << res.size() << endl << res;
    return 0;
}