// Common prime for NTT: 998244353 = 119 * 2^23 + 1
// Primitive root: 3
const int MOD = 998244353;
const int G = 3;
// Number Theoretic Transform
// on: true for Inverse NTT, false for Forward NTT
void ntt(vector<long long>& a, bool invert) {
    int n = a.size();

    // Bit-reversal permutation
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1)
            j ^= bit;
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }
    // Butterfly operations
    for (int len = 2; len <= n; len <<= 1) {
        long long wlen = power(G, (MOD - 1) / len);
        if (invert) wlen = modInverse(wlen);
        
        for (int i = 0; i < n; i += len) {
            long long w = 1;
            for (int j = 0; j < len / 2; j++) {
                long long u = a[i + j], v = (a[i + j + len / 2] * w) % MOD;
                a[i + j] = (u + v) < MOD ? (u + v) : (u + v - MOD);
                a[i + j + len / 2] = (u - v >= 0) ? (u - v) : (u - v + MOD);
                w = (w * wlen) % MOD;
            }
        }
    }
    // Scale results for Inverse NTT
    if (invert) {
        long long n_inv = modInverse(n);
        for (long long& x : a)
            x = (x * n_inv) % MOD;
    }
}
// Polynomial Multiplication
vector<long long> multiply(vector<long long> const& a, vector<long long> const& b) {
    vector<long long> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < a.size() + b.size()) 
        n <<= 1;
    fa.resize(n);
    fb.resize(n);
    ntt(fa, false);
    ntt(fb, false);
    for (int i = 0; i < n; i++)
        fa[i] = (fa[i] * fb[i]) % MOD;
    ntt(fa, true);
    // Optional: Resize to actual degree (removes trailing zeros)
    // while (fa.size() > 1 && fa.back() == 0) fa.pop_back(); 
    return fa;
}