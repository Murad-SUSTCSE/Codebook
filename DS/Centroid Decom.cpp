struct node {
    vector<int> adj; int sub = 1; int p = -1;      // centroid parent
    int dep = 0; int vis = 0;     // removed (centroid)
};
node tree[N]; int n; ll ans = 0;int root;
/* ---------------- SUBTREE SIZE ---------------- */
void dfs(int u, int p) {
    tree[u].sub = 1;
    for (int v : tree[u].adj) {
        if (v != p && tree[v].vis == 0) {
            dfs(v, u);
            tree[u].sub += tree[v].sub;
        }
    }
}
/* ---------------- FIND CENTROID ---------------- */
int dfs2(int u, int p, int tot) {
    for (int v : tree[u].adj) {
        if (v != p && tree[v].vis == 0 && tree[v].sub > tot / 2) {
            return dfs2(v, u, tot);
        }
    }
    return u;
}
/* ---------------- COLLECT LEVEL INFO (OPTIONAL) ---------------- */
/* Keep this if you need depth / distance info */
void nextlev(int u, int p, int d) {
    tree[u].dep = d;
    for (int v : tree[u].adj) {
        if (v != p && tree[v].vis == 0) {
            nextlev(v, u, d + 1);
        }
    }
}
/* ---------------- SOLVE FOR A CENTROID ---------------- */
// void solve(int c) {
//     // example placeholder // do calculations using centroid c
// }
/* ---------------- BUILD DECOMPOSITION ---------------- */
void build(int u, int p) {
    dfs(u, -1);
    int c = dfs2(u, -1, tree[u].sub);
    tree[c].p = p;
    if (p == -1) root = c;
    // optional: gather depth info from centroid
    nextlev(c, -1, 0);
    solve(c);
    tree[c].vis = 1;
    for (int v : tree[c].adj) {
        if (tree[v].vis == 0) {
            build(v, c);
        }
    }
}
// Build the tree inside main and call build(1, -1);