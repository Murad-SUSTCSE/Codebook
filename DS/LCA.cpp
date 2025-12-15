typedef struct node {
     int val;vector<int> adj;vector<int> p;vector<int> ele;int childv;int dep;
} node;
node tree[100005];
void dfs(int u , int p) {
    tree[u].p[0] = p;
    tree[u].dep = tree[p].dep + 1;
    for(int i = 1; i <= (int)log2(n) +1; i++) {
      if(tree[u].p[i-1] == 0) break;
      tree[u].p[i] = tree[tree[u].p[i-1]].p[i-1];
    }
   for(int i = 0; i < tree[u].adj.size(); i++)  if(tree[u].adj[i] != p) dfs(tree[u].adj[i],u);
}
int lca(int u, int v) {
   if(tree[v].dep < tree[u].dep) swap(v,u);
   for(int i = (int)log2(n) + 1; i >= 0; i--) {
    if(tree[v].p[i] && (tree[tree[v].p[i]].dep >= tree[u].dep)) {
       v = tree[v].p[i];
    }
   }
   if(v==u) return v;
   for(int i = (int)log2(n) + 1; i >= 0; i--) {
    if(tree[v].p[i] != tree[u].p[i]) {
       v = tree[v].p[i]; u = tree[u].p[i];
     }
   }
   return tree[v].p[0];
}