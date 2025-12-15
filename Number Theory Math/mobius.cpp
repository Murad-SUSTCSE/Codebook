int mob[N];
void mobius() {
  mob[1] = 1;
  for (int i = 2; i < N; i++){
    mob[i]--;
    for (int j = i + i; j < N; j += i) {
      mob[j] -= mob[i];
    }
  }
}
bool vis[N];
vector<int> d[N];
int mul[N];
void add(int x, int k) {
  for (auto y: d[x]) {
    mul[y] += k;
  }
}
int query(int x) {
  int ans = 0;
  for (auto y: d[x]) {
    ans += mul[y] * mob[y];
  }
  return ans;
}