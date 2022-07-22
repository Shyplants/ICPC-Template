#define SIZE 1048576
#define IDENTITY 0
ll seg[SIZE << 1];
ll op(ll a, ll b) {
    return a + b;
}
void init() {
    for (int i = SIZE - 1; i > 0; i--) {
        seg[i] = op(seg[i << 1], seg[i << 1 | 1]);
    }
}
void update(int idx, ll val) {
    seg[SIZE + idx] = val;
    for (int i = (SIZE + idx) >> 1; i > 0; i >>= 1) {
        seg[i] = op(seg[i << 1], seg[i << 1 | 1]);
    }
}
ll query(int left, int right) {
    ll ret = IDENTITY;
    for (int l = left + SIZE, r = right + SIZE; l <= r; l >>= 1, r >>= 1) {
        if (l & 1) ret = op(ret, seg[l++]);
        if (~r & 1) ret = op(ret, seg[r--]);
    }
    return ret;
}