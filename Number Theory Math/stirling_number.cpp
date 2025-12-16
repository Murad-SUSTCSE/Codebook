// S(n,k) = (1/k!) * sum_{i=0..k} (-1)^i * C(k,i) * (k-i)^n
int main() {
    int n, k; cin >> n >> k;
    vector<ll> fact(k+1, 1), invfact(k+1, 1);
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
