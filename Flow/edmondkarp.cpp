// edmonds karp ve^2 call while(bfs(n) != 0)
typedef struct node {
    int vis; int p;vector<int> adj;vector<ll> cap;
} node;
node graph[519];
ll bfs(int n) {
    queue<int> qu;
    vector<bool> vis(510,0);
    vis[1] =1;
    qu.push(1);
    while(!qu.empty()) {
        int cur = qu.front();
        // printf("cur-- %d\n",cur);
        qu.pop();
        f(i,graph[cur].adj.size()) {
            int nex=graph[cur].adj[i];
            if(vis[nex] == 0 && graph[cur].cap[nex] > 0) { 
            graph[nex].p = cur; vis[nex]= 1;
            if(nex==n) break; 
            qu.push(nex);
            }
        }
    }
    if(vis[n] == 0) return 0;
    ll maxflow = LLONG_MAX;
    int cur = n;
    while(cur != 1) {
         maxflow = min(maxflow, graph[graph[cur].p].cap[cur]);
         cur = graph[cur].p;
        //  printf("%d ",cur);
    }
    // printf("max %d\n", maxflow);
    cur = n;
    while(cur != 1) {
         graph[graph[cur].p].cap[cur] -= maxflow;
         graph[cur].cap[graph[cur].p] += maxflow;
         cur = graph[cur].p;
    }
    return maxflow;
}

// call after getting max flow 
vector<int> getCut(int n) {
    vector<int> vis(510,0);
    queue<int> q;
    q.push(1);
    vis[1] = 1;
    while(!q.empty()) {
        int u = q.front(); q.pop();
        for(int v : graph[u].adj) {
            if(!vis[v] && graph[u].cap[v] > 0) {  // residual capacity
                vis[v] = 1;
                q.push(v);
            }
        }
    }
    return vis;  // vis[v] = 1 -> reachable -> S-side
}
