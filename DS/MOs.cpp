const int BLOCK_SIZE = 350;
int n, q, ar[N], freq[N], res = 0, ans[10*N];
struct Query {
    int l, r, id;
    bool operator<(const Query &y) const {
        int x_block = l / BLOCK_SIZE;
        int y_block = y.l/BLOCK_SIZE;
        if(x_block == y_block)
            return r < y.r;
        return x_block < y_block;
    }
};
void add(int i) {
    int x = ar[i]; res -= freq[x] / 2; freq[x]++; res += freq[x] / 2;
}
void Remove(int i) {
    int x = ar[i]; res -= freq[x] / 2; freq[x]--; res += freq[x] / 2;
}
void solve() { // need to reset freq if neeeded
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> ar[i];
    cin >> q;
    vector<Query> qr;
    res = 0; int ii = 0;
    while(q--) {
        int l, r; cin >> l >> r; qr.push_back(Query({l, r, ii++}));
    }
    sort(qr.begin(), qr.end());
    int left = 1, right = 0;
    for (Query q : qr) {
        int l = q.l, r = q.r;
        while(right < r) add(++right);
        while(left > l) add(--left);
        while(left < l) Remove(left++);

        while(right > r) Remove(right--);
        ans[q.id] = res;
    }
    for (int i = 0; i < ii; i++) cout << ans[i] << "\n";
}
