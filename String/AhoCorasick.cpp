#include<bits/stdc++.h>
using namespace std;
typedef struct AC {
    static const int K = 26;
    struct node {
        int nxt[K], link, leaf, par;
        vector<int> ind;
        char pch;
        node(int par = -1, char pch = '$') : par(par), pch(pch) {
            fill(begin(nxt), end(nxt), -1);
            leaf = false;
            link = -1;
        }
    };
    vector<node> t;
    vector<vector<int>> ad;
    vector<int> st, en, mp;
    vector<int> cnt;
    int dt = 0;
    AC() {
        mp = vector<int> (1<<8, 0);
        for (char ch = 'a'; ch <= 'z'; ++ch) mp[ch] = ch - 'a';
        t.resize(1);
        cnt.resize(1);
    }
    int add(string str, int i) {
        int ptr = 0;
        for (auto ch : str) {
            if(t[ptr].nxt[mp[ch]] < 0) {
                t[ptr].nxt[mp[ch]] = t.size();
                t.push_back(node(ptr, ch));
                cnt.push_back(0);
            }
            ptr = t[ptr].nxt[mp[ch]];
        }
        t[ptr].leaf = true;
        t[ptr].ind.push_back(i);
        return ptr;
    }
    int get_link(int v) {
        if(t[v].link == -1) {
            t[v].link = (!v || !t[v].par) ? 0 : go(get_link(t[v].par), t[v].pch);
        }
        return t[v].link;
    }
    int go(int v, char ch) {
        if(t[v].nxt[mp[ch]] < 0) {
            t[v].nxt[mp[ch]] = !v ? 0 : go(get_link(v), ch);
        }
        return t[v].nxt[mp[ch]];
    }
    void dfs(int v) {
        st[v] = ++dt;
        for (int u : ad[v]) {
            dfs(u);
            cnt[v] += cnt[u];
        }
        en[v] = dt;
    }
    void calc() {
        int k = t.size();
        st.resize(k);
        en.resize(k);
        ad.resize(k);
        for (int i = 1; i < k; i++)
            ad[get_link(i)].push_back(i);
        dfs(0);
    }
} cc;
int cs = 1;
void solve() {
    cc bc;
    int n; cin >> n;
    vector<int> res(n + 1, 0);
    string text;
    cin >> text;
    string p;
    for (int i = 1; i <= n; i++) {
        cin >> p;
        bc.add(p, i);
    }
    int vertex = 0;
    for (int i = 0; i < text.length(); i++) {
        vertex = bc.go(vertex, text[i]);
        bc.cnt[vertex]++;
    }
    bc.calc();
    for (int i = 1; i < bc.t.size(); i++) {
        for (int &x : bc.t[i].ind) res[x] += bc.cnt[i];
    }
    cout << "Case " << cs++ << ":\n";
    for (int i = 1; i <= n; i++) cout << res[i] << "\n";
}
int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int TestCase = 1;
    cin >> TestCase;
    while(TestCase--)
        solve();
    return 0;
}
