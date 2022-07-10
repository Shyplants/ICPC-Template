#define MOD 1000000007
#define SIZE 300001
ll fact[SIZE], invfact[SIZE];
ll fexp(ll a, ll b) {
    ll res = 1;
    for (; b > 0; b >>= 1) {
        if (b & 1) (res *= a) %= MOD;
        (a *= a) %= MOD;
    }
    return res;
}
void precompute() {
    fact[0] = 1;
    for (int i = 1; i < SIZE; i++) fact[i] = fact[i - 1] * i % MOD;
    for (int i = 0; i < SIZE; i++) invfact[i] = fexp(fact[i], MOD - 2);
}
ll catalan(int n) {
    ll res = fact[2 * n] * invfact[n + 1] % MOD;
    return res * invfact[n] % MOD;
}
ll combination(int n, int k) {
    ll res = fact[n] * invfact[k] % MOD;
    return res * invfact[n - k] % MOD;
}