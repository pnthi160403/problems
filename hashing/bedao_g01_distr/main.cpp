// https://oj.vnoi.info/problem/bedao_g01_distr
#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    s = "#" + s;
    int pos = -1;
    int cnt = 0;
    for(int i = 1; i <= n; i++) {
        // cerr << "i = " << i << "; pos = " << pos << endl;
        if(pos != -1 && i - pos <= pos / k) {
            string a = "";
            for(int j = pos + 1; j <= i; j++)
                a += s[j];
            string check_str = "";
            for(int j = 1; j <= a.size(); j++)
                check_str += s[j];
            cnt += (a == check_str);
            // cerr << "a = " << a << endl;
            // cerr << "check_str = " << check_str << endl;
            a.clear();
            check_str.clear();
        }
        if (i % k != 0)
            continue;
        string check_str = "";
        for(int j = 1; j <= i / k; j++)
            check_str += s[j];
        // cerr << "check_str_2 = " << check_str << endl;
        int cur_index = check_str.size();
        bool check = true;
        while(cur_index + check_str.size() <= i) {
            string tmp = "";
            for(int j = cur_index + 1; j <= cur_index + check_str.size(); j++) {
                tmp += s[j];
            }
            // cerr << "tmp = " << tmp << endl;
            if (tmp != check_str) {
                check = false;
                break;
            }
            tmp.clear();
            cur_index += check_str.size();
        }
        check_str.clear();
        if(check) {
            pos = i;
            cnt += 1;
        }
    }
    cout << cnt;
    return 0;
}