vector<int> adj[200005];
int ptrs[200005];
int in_deg[200005], out_deg[200005];
vector<int> path;   // node sequence
vector<int> edges;  // edge sequence
int to[200005];
bool used[200005];

void dfs(int u) {
    while(ptrs[u] < adj[u].size()) {
        int e = adj[u][ptrs[u]++];
        if(used[e]) continue;
        used[e] = true;
        dfs(to[e]);
        edges.push_back(e);
    }
    path.push_back(u);
}

 

        for(int i=0;i<m;i++){
            int u,v;
            cin >> u >> v;
            adj[u].push_back(i);
            to[i] = v;
            out_deg[u]++;
            in_deg[v]++;
            if(i==0) s = u;
        }

        // degree check for Euler path
        int start = -1, end = -1;
        bool ok = true;

        for(int i=0;i<n;i++){
            int diff = out_deg[i] - in_deg[i];
            if(diff == 1){
                if(start != -1) ok = false;
                start = i;
            }
            else if(diff == -1){
                if(end != -1) ok = false;
                end = i;
            }
            else if(diff != 0){
                ok = false;
            }
        }

        reverse(path.begin(), path.end());
        reverse(edges.begin(), edges.end());
 
