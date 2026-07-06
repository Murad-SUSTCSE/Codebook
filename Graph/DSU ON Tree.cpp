// DSU on Tree (Sack)
// Computes for each node some info about its subtree efficiently
const int N = 200005;
vector<int> tree[N];
int col[N], sz[N];
bool big[N];
int cnt[N];        // frequency of colors
int cur_ans = 0;   // example answer (can be modified)
int answer[N];     // answer for each node
// compute subtree sizes
void dfs_sz(int u, int p) {
    sz[u] = 1;
    for (int v : tree[u]) {
        if (v == p) continue;
        dfs_sz(v, u);
        sz[u] += sz[v];
    }
}
// add/remove contribution of subtree
void add(int u, int p, int val) {
    cnt[col[u]] += val;
    // example logic: maintain max frequency
    cur_ans = max(cur_ans, cnt[col[u]]);
    for (int v : tree[u]) {
        if (v == p || big[v]) continue;
        add(v, u, val);
    }
}
// main DSU dfs
void dfs(int u, int p, bool keep) {
    int mx = -1, heavy = -1;
    for (int v : tree[u]) {
        if (v != p && sz[v] > mx) {
            mx = sz[v];
            heavy = v;
        }
    }
    // process light children
    for (int v : tree[u]) {
        if (v != p && v != heavy)dfs(v, u, false);
    }
    // process heavy child
    if (heavy != -1) {
        dfs(heavy, u, true); big[heavy] = true;
    }
    // add current node and light children
    add(u, p, +1); answer[u] = cur_ans;
    if (heavy != -1) big[heavy] = false;
    // clear data if not keeping
    if (!keep) {
        add(u, p, -1); cur_ans = 0;
    }
}
