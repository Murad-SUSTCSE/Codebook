// Returns the number of paths from (0,0) to (a,b) staying at or below y = x + k
long long ballot_with_offset(int a, int b, int k) {
    if (b > a + k) return 0; // Already invalid
    long long total = nCr(a + b, a);
    long long invalid = nCr(a + b, a + k + 1);
    return (total - invalid + mod) % mod;
}

// Non-strict Ballot Number: A >= B at all prefixes
long long ballot_non_strict(int a, int b) {
    return ballot_with_offset(a, b, 0);
}

// Strict Ballot Number: A > B at all non-empty prefixes
long long ballot_strict(int a, int b) {
    if (a <= b) return 0;
    return ballot_non_strict(a - 1, b);
}