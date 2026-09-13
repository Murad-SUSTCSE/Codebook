void dfs(int u, int p) {
    tree[u][0] = p;
    dep[u] = dep[p] + 1;

    for(int i = 1; i < B; i++) {
        tree[u][i] = tree[tree[u][i - 1]][i - 1];
    }
    sz[u] = 1;
    for(auto v : g[u]) {
        if(v == p) continue;
        dfs(v, u);
        sz[u] += sz[v];
    }
}

int lca(int u, int v) {
    if(dep[u] > dep[v]) swap(u, v);
    for(int i = B - 1; i >= 0; i--) {
        if(dep[tree[v][i]] >= dep[u]) {
            v = tree[v][i];
        }
    }

    if(u == v) return u;
    for(int i = B - 1; i >= 0; i--) {
        if(tree[u][i] != tree[v][i]) {
            u = tree[u][i];
            v = tree[v][i];
        }
    }
    return tree[u][0];
}
