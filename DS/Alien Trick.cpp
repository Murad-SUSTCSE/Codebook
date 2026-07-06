// Aliens trick on Tree
// Maximizes total value using <= K selections
struct State {
    long long val; // best value
    int cnt;       // number of selections
};
vector<pair<int,int>> g[N]; // {to, weight}
int K;
// merge two states
State merge(State a, State b) {
    return {a.val + b.val, a.cnt + b.cnt};
}
State dfs(int u, int p, long long penalty) {
    State res = {0, 0};
    for (auto [v, w] : g[u]) {
        if (v == p) continue;
        State cur = dfs(v, u, penalty);
        // choose edge
        State take = {cur.val + w - penalty, cur.cnt + 1};
        // choose better
        if (take.val > cur.val) res = merge(res, take);
        else res = merge(res, cur);
    }
    return res;
}
// check if we can do with <= K selections
bool check(long long penalty) {
    State res = dfs(1, 0, penalty);
    return res.cnt <= K;
}
// binary search on penalty
long long solve() {
    long long lo = -1e12, hi = 1e12;
    while (lo < hi) {
        long long mid = (lo + hi + 1) / 2;
        if (check(mid)) lo = mid;
        else hi = mid - 1;
    }
    return dfs(1, 0, lo).val + lo * K;
}
