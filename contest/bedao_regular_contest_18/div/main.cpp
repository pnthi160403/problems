#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int q;
    cin >> q;
    while(q--) {
        ll a, b;
        cin >> a >> b;
        ll g = gcd(abs(a), abs(b));
        a /= g;
        b /= g;
        if (a == 0) {
            cout << "0 1" << endl;
            continue;
        }
        if (a + b > 0) {
            cout << a << ' ' << b << endl;
        } else if (a + b == 0) {
            cout << "0 0" << endl;
        } else {
            a *= -1;
            b *= -1;
            cout << a << ' ' << b << endl;
        }
    }
    return 0;
}