typedef struct node {
   int p;
   vector<int> adj;
   int mxchild; int chain; int ind_in_chain; int subtree; int koto; int price;
} node;
node tree[200010];
vector<int> chain(200010);
vector<int> start_c(200010);
vector<vector<int>> seg(800010);
vector<vector<ll>> sum(800010);
vector<int> dfs_array(200010);
// vector<vector<seg>> segtree(500010);
int c;
int ind=-1;
void dfs(int u, int p) {
    tree[u].p = p;
    int mx=0;
    f(i, tree[u].adj.size()) {
        int v = tree[u].adj[i];
        if(p==v) continue;
        dfs(v,u);
        tree[u].subtree += tree[v].subtree;
        if(mx < tree[v].subtree) {mx = tree[v].subtree; tree[u].mxchild = v;} 
    }
}
void hld(int u) {
    dfs_array[++ind] = u;
    chain[c]++;
    // chain[c].push_back(u);
    tree[u].chain = c;
    tree[u].ind_in_chain = chain[c] - 1;
    if(tree[u].mxchild) hld(tree[u].mxchild);
    f(i, tree[u].adj.size()) {
        int v = tree[u].adj[i];
        if(v == tree[u].p || v == tree[u].mxchild) continue;
        c++;
        start_c[c] = ind+1;
        hld(v);
    }
}

void merge(int ind)  {
    int lsize = seg[2*ind+1].size();
    int rsize = seg[2*ind +2].size();
    seg[ind].clear();
    sum[ind].clear();
    seg[ind].resize(lsize+rsize);
    sum[ind].resize(lsize+rsize);
    int l = 0, r = 0,i=0;
    while(l < lsize || r < rsize) {
        if(l==lsize) {
            seg[ind][i] =(seg[2*ind +2][r]);r++;
        }
        else if(r==rsize) {
            seg[ind][i] =(seg[2*ind+1][l]);l++;
        }
        else if(seg[2*ind+1][l] < seg[2*ind +2][r]) {
            seg[ind][i] =(seg[2*ind+1][l]);l++;
        }
        else {
            seg[ind][i] =(seg[2*ind+2][r]);r++;
        }
        sum[ind][i] = ((l==0 ? 0 : sum[ind*2+1][l-1]) + (r==0 ? 0 : sum[ind*2+2][r-1]));
        i++;
    }
    // return narr;
}
void build(vector<int>& arr, int l, int r, int ind) {
     if(l==r) {
        l = arr[l];
        seg[ind].resize(1);
        sum[ind].resize(1);
        seg[ind][0] = (tree[l].price);
        sum[ind][0] = ((ll)tree[l].koto);
     } else {
        int m = (l+r)/2;
        build(arr,l,m,2*ind +1); build(arr,m+1,r,2*ind +2);
        merge(ind);
     }
}

ll query(int s, int e, int l , int r, int ind, int tar) {
    if(s>e) return 0;
    if(s==l && e==r) {
       int ans = -1;
       l = 0, r = seg[ind].size()-1;
       while(l <= r) {
          int m = (l+r)/2; 
          if(seg[ind][m] <= tar ) 
            ans = m, l = m+1;
        else r = m-1;
       } 
        return ans==-1?0:sum[ind][ans];
    } else {
        int m =(l+r)/2;
        return query(s,min(e,m),l,m,2*ind+1,tar) + query(max(s,m+1),e,m+1,r,2*ind+2,tar);
    }
}
