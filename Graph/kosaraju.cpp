typedef struct node {
   int vis;
   vector<int> adj;
   vector<int> ulta;
  } node;
  node tree[300010];
  vector<vector<int>> scc(300010);
  stack<int> st;
  int scount = 0;
  void dfs(int u) {
    tree[u].vis = 1;
    f(i,tree[u].adj.size()) {
        int next = tree[u].adj[i];
        if(tree[next].vis==0) dfs(next);
    }
    st.push(u);
  }
  void dfs2(int u) {
    // printf("%d %d\n",u,scount);
    tree[u].vis = 1;
    scc[scount-1].push_back(u); 
    f(i,tree[u].ulta.size()) {
        int next = tree[u].ulta[i];
        if(tree[next].vis==0) dfs2(next);
    }
  }