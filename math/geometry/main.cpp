// https://dmoj.ctu.edu.vn/problem/cictcpc2024_geo
#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while(t--) {
        double r1, r2; cin >> r1 >> r2;
        double SABC, SABD, S1, S2;
        SABC = (double)0.5 * r1 * (r1 + r2);
        double BH = r1 * sin(atan((r1 + r2) / r1));
        double AD = 2 * sqrt(r1 * r1 - BH * BH);
        SABD = (double)0.5 * BH * AD;
        double DBC = atan((r1 + r2) / r1) - atan(r1 / (r1 + r2));
        S1 = DBC / 2 * (r1 * r1);
        S2 = atan(r1 / (r1 + r2)) / 2 * (r2 * r2);
        double ans = SABC - SABD - S1 - S2;
        cout << fixed << setprecision(10) << ans << endl;
    }
    return 0;
}