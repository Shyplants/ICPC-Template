#define MOD 998244353
void ntt(vector<ll> &a, bool inv) {
    int n = a.size(), j = 0;
    for (int i = 1; i < n; i++) {
        int bit = (n >> 1);
        while (j >= bit) {
            j -= bit; bit >>= 1;
        }
        j += bit;
        if (i < j) swap(a[i], a[j]);
    }
    for (int i = 2; i <= n; i <<= 1) {
        ll ang = fexp(3, (MOD - 1) / i);
        if (inv) ang = fexp(ang, MOD - 2);
        for (int j = 0; j < n; j += i) {
            ll root = 1;
            for (int k = 0; k < i / 2; k++) {
                ll tmp = root * a[j + k + i / 2] % MOD;
                (root *= ang) %= MOD;
                a[j + k + i / 2] = (a[j + k] + MOD - tmp) % MOD;
                (a[j + k] += tmp) %= MOD;
            }
        }
    }
    if (inv) for (int i = 0; i < n; i++) (a[i] *= fexp(n, MOD - 2)) %= MOD;
}
vector<ll> multiply(vector<ll> &v, vector<ll> &w) {
    vector<ll> fv(v.begin(), v.end()), fw(w.begin(), w.end());
    int n = 2; while (n < v.size() + w.size()) n <<= 1;
    fv.resize(n); fw.resize(n);
    ntt(fv, 0); ntt(fw, 0);
    for (int i = 0; i < n; i++) (fv[i] *= fw[i]) %= MOD;
    ntt(fv, 1);
    return fv;
}