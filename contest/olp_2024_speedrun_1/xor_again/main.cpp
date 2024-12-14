#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

struct Node {
    int c[2];
    int cnt, exist;
};

struct Trie {
    int cur;
    vector<Node> trie;
    void init(int n) {
        trie.resize(n + 1);
        cur = 0;
        new_node();
    }
    int new_node() {
        for(int i = 0; i < 2; i++) {
            trie[cur].c[i] = -1;
        }
        trie[cur].cnt = trie[cur].exist = 0;
        return cur++;
    }
    void add_string(string s) {
        int cur_node = 0;
        for(int i = 0; i < s.length(); i++) {
            int x = s[i] - '0';
            if (trie[cur_node].c[x] == -1) trie[cur_node].c[x] = new_node();
            cur_node = trie[cur_node].c[x];
            trie[cur_node].cnt++;
        }
        trie[cur_node].exist++;
    }
    bool del_string(string &s, int cur_node, int i) {
        if (i == s.length()) trie[cur_node].exist--;
        else {
            int x = s[i] - '0';
            bool is_del = del_string(s, trie[cur_node].c[x], i + 1);
            if (is_del) trie[cur_node].c[x] = -1;
        }
        if (cur_node != 0) {
            trie[cur_node].cnt--;
            if (trie[cur_node].cnt == 0) return true;
        }
        return false;
    }
};

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    auto convert_string = [&](int x) -> string {
        string res = "";
        for(int i = 31; i >= 0; i--) {
            if (x & (1 << i)) res += '1';
            else res += '0';
        }
        return res;
    };
    auto convert_int = [&](string s) -> int {
        reverse(s.begin(), s.end());
        int res = 0;
        for(int i = 0; i < s.length(); i++) {
            if (s[i] == '1') res += (1 << i);
        }
        return res;
    };
    int q; cin >> q;
    Trie t;
    t.init(32 * (int)2e5);
    while(q--) {
        string type; cin >> type;
        if (type == "ADD") {
            int x; cin >> x;
            t.add_string(convert_string(x));
        } else if (type == "REMOVE") {
            int x; cin >> x;
            string sx = convert_string(x);
            t.del_string(sx, 0, 0);
        } else if (type == "MAX") {
            int y; cin >> y;
            string sy = convert_string(y);
            string sx = "";
            int cur_node = 0;
            for(int i = 0; i < sy.length(); i++) {
                int x = sy[i] - '0';
                int need = 1 - x;
                if (t.trie[cur_node].c[need] != -1) {
                    sx += (need == 1 ? '1' : '0');
                    cur_node = t.trie[cur_node].c[need];
                } else {
                    sx += (x == 1 ? '1' : '0');
                    cur_node = t.trie[cur_node].c[x];
                }
            }
            int x = convert_int(sx);
            cout << (x ^ y)  << endl;
        } else if (type == "SECOND_MAX") {
            int y; cin >> y;
            string sy = convert_string(y);
            string sx = "";
            int cur_node = 0;
            for(int i = 0; i < sy.length(); i++) {
                int x = sy[i] - '0';
                int need = 1 - x;
                if (t.trie[cur_node].c[need] != -1) {
                    sx += (need == 1 ? '1' : '0');
                    cur_node = t.trie[cur_node].c[need];
                } else {
                    sx += (x == 1 ? '1' : '0');
                    cur_node = t.trie[cur_node].c[x];
                }
            }
            string tmp = sx;
            t.del_string(tmp, 0, 0);
            sx = "";
            cur_node = 0;
            for(int i = 0; i < sy.length(); i++) {
                int x = sy[i] - '0';
                int need = 1 - x;
                if (t.trie[cur_node].c[need] != -1) {
                    sx += (need == 1 ? '1' : '0');
                    cur_node = t.trie[cur_node].c[need];
                } else {
                    sx += (x == 1 ? '1' : '0');
                    cur_node = t.trie[cur_node].c[x];
                }
            }
            int x = convert_int(sx);
            cout << (x ^ y) << endl;
            t.add_string(tmp);
        }
    }
    return 0;
}