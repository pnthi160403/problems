#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;

const int N = (int)1e7;

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    vector<int> min_p(N + 1, N + 1), max_p(N + 1);
    vector<int> primes;
    for(int i = 2; i <= N; i++) {
        if (max_p[i] == 0) {
            max_p[i] = i;
            min_p[i] = i;
            primes.push_back(i);
        }
        for(int p : primes) {
            if (1ll * p * i > N) break;
            min_p[p * i] = min(p, min_p[i]);
            max_p[p * i] = max(p, max_p[i]);
        }
    }
    int t; cin >> t;
    while(t--) {
        int x; cin >> x;
        cout << min_p[x] << ' ' << max_p[x] << endl;
    }
    return 0;
}