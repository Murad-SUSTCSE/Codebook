/**
Let  opt(i, j)  be the value of  k  that minimizes the above expression. Assuming that the cost function satisfies the quadrangle inequality, we can show that  opt(i, j) <= opt(i, j + 1) for all
i, j . This is known as the monotonicity condition. Then, we can apply divide and conquer DP. The optimal "splitting point" for a fixed  i  increases as  j  increases.
*/
int const N = 3e5 + 5, inf = 1e16;
int m, n, R = 0, L = 1, res = 0;
int ar[N], cnt[N];
vector<long long> dp_before, dp_cur;
void add(int id) {
    res += cnt[ar[id]]; cnt[ar[id]]++;
}
void Remove(int id) {
    cnt[ar[id]]--;  res -= cnt[ar[id]];
}
long long C(int l, int r) {
    while(R < r) add(++R);
    while(L > l) add(--L);
    while(L < l) Remove(L++);
    while(R > r) Remove(R--);
    return res;
}
void compute(int l, int r, int optl, int optr) {
    if (l > r) return;
    int mid = (l + r) >> 1;
    pair<long long, int> best = {LLONG_MAX, -1};
    for (int k = optl; k <= min(mid, optr); k++) best = min(best, {(k ? dp_before[k - 1] : 0) + C(k, mid), k});
    dp_cur[mid] = best.first;
    int opt = best.second;
    compute(l, mid - 1, optl, opt); compute(mid + 1, r, opt, optr);
}
void solve() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> ar[i];
    dp_before.assign(n + 1, 0); dp_cur.assign(n + 1, 0);
    for (int i = 1; i <= n; i++) dp_before[i] = C(1, i);
    for (int i = 1; i < m; i++) {
        compute(1, n, 1, n); dp_before = dp_cur;
    }
    cout << dp_before[n] << endl;
}
