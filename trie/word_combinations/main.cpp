#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

const int MOD = (int)1e9 + 7;

struct Node {
    int c[26];
    int cnt, exist;
};

struct Trie {
    vector<Node> trie;
    int cur;
    void init(int _n) {
        trie.resize(_n);
        cur = -1;
        new_node();
    }
    int new_node() {
        cur++;
        for(int i = 0; i < 26; i++) {
            trie[cur].c[i] = -1;
        }
        trie[cur].cnt = trie[cur].exist = 0;
        return cur;
    }
    void add_string(string s) {
        int cur_node = 0;
        for(int i = 0; i < s.length(); i++) {
            int x = s[i] - 'a';
            if (trie[cur_node].c[x] == -1) trie[cur_node].c[x] = new_node();
            cur_node = trie[cur_node].c[x];
            trie[cur_node].cnt++;
        }
        trie[cur_node].exist++;
    }
};

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    Trie t;
    t.init((int)1e6 + 1);
    string s; cin >> s;
    int k; cin >> k;
    for(int i = 0; i < k; i++) {
        string x; cin >> x;
        reverse(x.begin(), x.end());
        t.add_string(x);
    }
    int n = s.length();
    vector<int> dp(n + 1);
    dp[0] = 1;
    for(int i = 1; i <= n; i++) {
        int cur_node = 0;
        for(int j = i; j >= 1; j--) {
            int x = s[j - 1] - 'a';
            int next_node = t.trie[cur_node].c[x];
            if (next_node == -1) break;
            if (t.trie[next_node].exist >= 1) {
                dp[i] += dp[j - 1];
                dp[i] %= MOD;
            }
            cur_node = next_node;
        }
    }
    cout << dp[n];
    return 0;
}