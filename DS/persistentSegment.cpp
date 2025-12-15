struct node {
    ll sum; node *left, *right;
    node(ll val = 0) {
        sum = val; left = right = NULL;
    }
    node(node *l, node *r) {
        left = l; right = r; sum = (l ? l->sum : 0) + (r ? r->sum : 0);
    }
};
int n; vector<int> v;
node* build(int start, int end) {
    if (start == end)
        return new node(v[start]);
    int mid = (start + end) >> 1;
    return new node(build(start, mid), build(mid + 1, end));
}
node* update(node* prev, int pos, ll val, int start, int end) {
    if (start == end) return new node(val);
    int mid = (start + end) >> 1;
    if (pos <= mid)return new node(update(prev->left, pos, val, start, mid), prev->right);
    else return new node(prev->left, update(prev->right, pos, val, mid + 1, end));
}
ll query(node* cur, int l, int r, int start, int end) {
    if (cur == NULL || start > r || end < l) return 0;
    if (l <= start && end <= r) return cur->sum;
    int mid = (start + end) >> 1;
    return query(cur->left, l, r, start, mid) + query(cur->right, l, r, mid + 1, end);
}
void solve() {
    cin >> n; v.resize(n);
    for (int &x : v) cin >> x;
    vector<node*> roots; roots.push_back(build(0, n - 1));
    int q; cin >> q;
    while (q--) {
        int id; cin >> id;
        if (id == 1) {
            int ver, pos; ll val; cin >> ver >> pos >> val;
            roots.push_back(update(roots[ver], pos - 1, val, 0, n - 1));
        } else {
            int ver, l, r; cin >> ver >> l >> r;
            cout << query(roots[ver], l - 1, r - 1, 0, n - 1) << "\n";
        }
    }
}
