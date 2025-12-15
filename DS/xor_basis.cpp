struct XorBasis {
    vector<ll> basis;
    ll N = 0, tmp = 0;
    void add(ll x) {
        N++;
        tmp ^= x;
        for (ll b : basis) x = min(x, x ^ b);
        if (!x) return;
        for (ll &b : basis) if ((b ^ x) < b) b ^= x;
        basis.push_back(x);
        sort(basis.rbegin(), basis.rend());
    }
    // number of basis vectors (rank)
    ll size() { return (ll) basis.size(); }
    // clear everything
    void clear() { N = 0; tmp = 0; basis.clear(); }
    // returns true if x can be formed
    bool possible(ll x) {
        for (ll b : basis) x = min(x, x ^ b);
        return x == 0;
    }
    // returns maximum xor value
    ll maxxor(ll x = 0) {
        for (ll b : basis) x = max(x, x ^ b);
        return x;
    }
    // returns minimum xor value
    ll minxor(ll x = 0) {
        for (ll b : basis) x = min(x, x ^ b);
        return x;
    }
    // returns count of subsets which xor to x (modded)
    ll cntxor(ll x) {
        if (!possible(x)) return 0LL;
        ll freebits = N - size();
        ll res = 1;
        while (freebits--) res = (res * 2) % MOD;
        return res;
    }
    // returns sum of xor of all subsets
    ll sumOfAll() {
        return tmp * (1LL << (N - 1));
    }
    // returns k-th smallest xor value (1-indexed)
    ll kth(ll k) {
        ll sz = size();
        if (k > (1LL << sz)) return -1;
        k--;
        ll ans = 0;
        for (ll i = 0; i < sz; i++)
            if (k >> (sz - 1 - i) & 1) ans ^= basis[i];
        return ans;
    }
} xb;
