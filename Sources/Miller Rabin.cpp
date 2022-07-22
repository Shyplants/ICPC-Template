ull fexp(ull a, ull b, ull mod) {
    ull res = 1;
    for (; b > 0; b >>= 1) {
        if (b & 1) (res *= a) %= mod;
        (a *= a) %= mod;
    }
    return res;
}
bool isprime(ull d) {
    if (d <= 1) return false;
    int a[3] = {2, 7, 61};
    ull n = d, s = 0; d--;
    while (~d & 1) d >>= 1, s++;
    for (int i = 0; i < 3; i++) {
        if (a[i] >= n) break;
        bool composite = true;
        for (int j = 0; j < s; j++) {
            if (fexp(a[i], d, n) == 1 || fexp(a[i], (1ULL << j) * d, n) == n - 1) composite = false;
        }
        if (composite) return false;
    }
    return true;
}