#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int q;
    cin >> q;
    while(q--) {
        string s, t;
        cin >> s >> t;
        int x = 0;
        for(int i = 0; i < min(s.size(), t.size()); i++) {
            if (s[i] == t[i])
                x++;
            else
                break;
        }
        if (x == 0)
            cout << s.length() + t.length() << endl;
        else
            cout << s.length() + t.length() - x + 1 << endl;
    }
    return 0;
}