const int N = 3e5 + 9;

struct Trie {
    static const int B = 31;

    struct node {
        node* nxt[2];
        int sz;

        node() {
            nxt[0] = nxt[1] = NULL;
            sz = 0;
        }
    } *root;
    Trie() {
        root = new node();
    }
    void insert(int val) {
        node* cur = root;
        cur->sz++;
        for (int i = B - 1; i >= 0; i--) {
            int b = (val >> i) & 1;
            if (cur->nxt[b] == NULL)
                cur->nxt[b] = new node();
            cur = cur->nxt[b];
            cur->sz++;
        }
    }
    void remove(int val) {
        node* cur = root;
        cur->sz--;

        for (int i = B - 1; i >= 0; i--) {
            int b = (val >> i) & 1;

            cur = cur->nxt[b];
            cur->sz--;
        }
    }
    int get_min(int x) {
        node* cur = root;
        int ans = 0;

        for (int i = B - 1; i >= 0; i--) {
            int b = (x >> i) & 1;
                 if (cur->nxt[b] && cur->nxt[b]->sz > 0) {
                cur = cur->nxt[b];
            }
            else {
                cur = cur->nxt[!b];
                ans |= (1LL << i);
            }
        }

        return ans;
    }

    int get_max(int x) {
        node* cur = root;
        int ans = 0;

        for (int i = B - 1; i >= 0; i--) {
            int b = (x >> i) & 1;
            if (cur->nxt[!b] && cur->nxt[!b]->sz > 0) {
                cur = cur->nxt[!b];
                ans |= (1LL << i);
            }
            else {
                cur = cur->nxt[b];
            }
        }
        return ans;
    }
    int query(int x, int k) {
        node* cur = root;
        int ans = 0;

        for (int i = B - 1; i >= 0; i--) {
            if (cur == NULL) break;

            int b1 = (x >> i) & 1;
            int b2 = (k >> i) & 1;

            if (b2 == 1) {
                if (cur->nxt[b1])
                    ans += cur->nxt[b1]->sz;

                cur = cur->nxt[!b1];
            }
            else {
                cur = cur->nxt[b1];
            }
        }
        return ans;
    }
    void del(node* cur) {
        for (int i = 0; i < 2; i++) {
            if (cur->nxt[i])
                del(cur->nxt[i]);
        }
        delete cur;
    }
    ~Trie() {
        del(root);
    }
} t;
