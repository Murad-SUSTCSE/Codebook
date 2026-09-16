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


    // Ret: #subsets with XOR sum S where (S & x) == x (mod) | O(B^2), B = basis.size()
ll cntSuperset(ll x) {
    vector<ll> tb;
    for (ll b : basis) {
        ll v = b & x;
        for (ll t : tb) v = min(v, v ^ t);
        if (v) { tb.push_back(v); sort(tb.rbegin(), tb.rend()); }
    }
    ll t = x;
    for (ll b : tb) t = min(t, t ^ b);
    if (t) return 0;
    ll f = N - tb.size(), r = 1;
    while (f--) r = r * 2 % mod;
    return r;
}

// Ret: #subsets with XOR sum S where (S & ~x) == 0 (mod) | O(B^2), B = basis.size()
ll cntSubmask(ll x) {
    vector<ll> tb;
    for (ll b : basis) {
        ll v = b & ~x;
        for (ll t : tb) v = min(v, v ^ t);
        if (v) { tb.push_back(v); sort(tb.rbegin(), tb.rend()); }
    }
    ll f = N - tb.size(), r = 1;
    while (f--) r = r * 2 % mod;
    return r;
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
