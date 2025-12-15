// S(n,k) = (1/k!) * sum_{i=0..k} (-1)^i * C(k,i) * (k-i)^n
ll power(ll a, ll b) {
    ll r = 1;
    while (b) {
        if (b & 1) r = r * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return r;
}
ll modinv(ll x) { return power(x, MOD - 2); }
int main() {
    int n, k; cin >> n >> k;
    vector<ll> fact(k+1, 1), invfact(k+1, 1);
    for (int i = 1; i <= k; i++) fact[i] = fact[i-1] * i % MOD;
    invfact[k] = modinv(fact[k]);
    for (int i = k; i > 0; i--) invfact[i-1] = invfact[i] * i % MOD;
    ll ans = 0;
    for (int i = 0; i <= k; i++) {
        ll term = fact[k] * invfact[i] % MOD * invfact[k-i] % MOD;
        term = term * power(k - i, n) % MOD;
        if (i & 1) ans = (ans - term + MOD) % MOD;
        else ans = (ans + term) % MOD;
    }
    ans = ans * modinv(fact[k]) % MOD;
    cout << ans << "\n";
}
