#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int treeSize = 1 << 20; // treeSize = 2^x,  2^x <= n < 2^(x+1)

int n, m, k;
ll tree[treeSize << 1];

void init()
{
    // tree[x] = parent, tree[x << 1] = x's leftChild, tree[x << 1|1] = x's rightChild
    for(int i=treeSize-1; i>0; --i) {
        tree[i] = tree[i << 1] + tree[i << 1|1];
    }
}

void update(int idx, ll val) {
    // update leafNode
    tree[treeSize + idx] = val;

    for(int i=(treeSize+idx) >> 1; i > 0; i >>= 1) {
        tree[i] = tree[i << 1] + tree[i << 1|1];
    }
}

// segQuery(ex. min, max, sum, xor...)
ll sum(int left, int right) {
    ll ret = 0;
    for(int l=left+treeSize, r=right+treeSize; l<=r; l>>=1, r>>=1) {
        if(l&1) ret += tree[l++];
        if(~r&1) ret += tree[r--];
    }

    return ret;
}

// [2042] 구간 합 구하기
// https://www.acmicpc.net/problem/2042
int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0);

    cin >> n >> m >> k;

    for(int i=0; i<n; ++i) cin >> tree[treeSize + i];
    init();

    int a, b;
    ll c;
    m+=k;
    while(m--) {
        cin >> a >> b >> c;
        if(a == 1) update(b-1, c);
        else cout << sum(b-1, c-1) << '\n';
    }
    return 0;
}