#include <bits/stdc++.h>
#define ll long long
#define endl '\n'
#define ff(i, x, y) for(int i = x; i <= y; i++)
#define fi first
#define se second
#define pb push_back

using namespace std;

const int N = 1001;
long long M[N][N][2], A[N][N][2];

struct Node {
    int x1, y1, x2, y2;
};

bool sub1(int n, int l, int r, vector<Node> a) {
    if (n > 200) return false;
    for(Node x : a) {
        int max_val = max({x.x1, x.y1, x.x2, x.y2});
        if (max_val > 200) return false;
    }
    return true;
}

bool sub2(int n, int l, int r, vector<Node> a) {
    for(Node x : a) {
        int max_val = max({x.x1, x.y1, x.x2, x.y2});
        if (max_val > 2000) return false;
    }
    return true;
}

bool sub3(int n, int l, int r, vector<Node> a) {
    return l == 1 && r == n;
}

bool sub4(int n, int l, int r, vector<Node> a) {
    return l == n && r == n;
}

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    freopen("rect.inp", "r", stdin);
    freopen("rect.out", "w", stdout);
    int n, l, r;
    vector<Node> a;
    cin >> n >> l >> r;
    ff(i, 0, n - 1) {
        int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
        a.pb({x1, y2, x2, y1});
    }
    int ans = 0;
    if (sub1(n, l, r, a)) {
        ff(x, 0, 200) {
            ff(y, 0, 200) {
                int cnt = 0;
                for(Node r : a) {
                    if (r.x1 <= x && x <= r.x2 && r.y1 >= y && y >= r.y2)
                        cnt++;
                }
                if (cnt >= l && cnt <= r) ans++;
            }
        }
    } else if (sub2(n, l, r, a)) {
        struct BIT2D {
            BIT2D() {
                memset(M, 0, sizeof M);
                memset(A, 0, sizeof A);
            }
            void upd2(long long t[N][N][2], int x, int y, long long mul, long long add) {
                for(int i = x; i < N; i += i & -i) {
                for(int j = y; j < N; j += j & -j) {
                    t[i][j][0] += mul;
                    t[i][j][1] += add;
                }
                }
            }
            void upd1(int x, int y1, int y2, long long mul, long long add) {
                upd2(M, x, y1, mul, -mul * (y1 - 1));
                upd2(M, x, y2, -mul, mul * y2);
                upd2(A, x, y1, add, -add * (y1 - 1));
                upd2(A, x, y2, -add, add * y2);
            }
            void upd(int x1, int y1, int x2, int y2, long long val) {
                upd1(x1, y1, y2, val, -val * (x1 - 1));
                upd1(x2, y1, y2, -val, val * x2);
            }
            long long query2(long long t[N][N][2], int x, int y) {
                long long mul = 0, add = 0;
                for(int i = y; i > 0; i -= i & -i) {
                mul += t[x][i][0];
                add += t[x][i][1];
                }
                return mul * y + add;
            }
            long long query1(int x, int y) {
                long long mul = 0, add = 0;
                for(int i = x; i > 0; i -= i & -i) {
                mul += query2(M, i, y);
                add += query2(A, i, y);
                }
                return mul * x + add;
            }
            long long query(int x1, int y1, int x2, int y2) {
                return query1(x2, y2) - query1(x1 - 1, y2) - query1(x2, y1 - 1) + query1(x1 - 1, y1 - 1);
            }
        } t;
        for(Node r : a) {
            t.upd(r.x1, r.y1, r.x2, r.y2, 1);
        }
        ff(x, 0, 2000) {
            ff(y, 0, 2000) {
                int cnt = t.query(x, y, x, y);
                if (cnt >= l && cnt <= r) ans++;
            }
        }
    } else if (sub4(n, l, r, a)) {
        int x1 = a[0].x1, y1 = a[0].y1, x2 = a[0].x2, y2 = a[0].y2;
        ff(i, 1, n - 1) {
            x1 = max(x1, a[i].x1);
            y1 = min(y1, a[i].y1);
            x2 = min(x2, a[i].x2);
            y2 = max(y2, a[i].y2);
        }
        ans = abs(x2 - x1) * abs(y2 - y1);
    }
    cout << ans;
    return 0;
}