#include<cstdio>
#include<algorithm>
#include<vector>

typedef long long LL;

using namespace std;

int treeSize = 1;
int N, M, K;

vector<LL> tree, lazy;

void update_lazy(int node, int nodeLeft, int nodeRight) {
	if (lazy[node]) {
		tree[node] += (nodeRight - nodeLeft + 1) * lazy[node];

		if (nodeLeft < nodeRight) {
			lazy[node << 1] += lazy[node];
			lazy[node << 1|1] += lazy[node];
		}
		lazy[node] = 0;
	}
}

void update(int node, int nodeLeft, int nodeRight, int left, int right, LL diff) {
	update_lazy(node, nodeLeft, nodeRight);

	if (nodeLeft > right || nodeRight < left) return;
	if (left <= nodeLeft && right >= nodeRight) {
		tree[node] += (nodeRight - nodeLeft + 1) * diff;
		if (nodeLeft < nodeRight) {
			lazy[node << 1] += diff;
			lazy[node << 1|1] += diff;
		}
		return;
	}

	int mid = (nodeLeft + nodeRight) / 2;
	update(node << 1, nodeLeft, mid, left, right, diff);
	update(node << 1|1, mid + 1, nodeRight, left, right, diff);
	tree[node] = tree[node << 1] + tree[node << 1|1];
}

LL sum(int node, int nodeLeft, int nodeRight, int left, int right) {
	update_lazy(node, nodeLeft, nodeRight);

	if (nodeLeft > right || nodeRight < left) return 0;
	if (left <= nodeLeft && right >= nodeRight) return tree[node];

	int mid = (nodeLeft + nodeRight) >> 1;
	return sum(node << 1, nodeLeft, mid, left, right) + sum(node << 1|1, mid + 1, nodeRight, left, right);
}

int main()
{
	scanf("%d %d %d", &N, &M, &K);
	M += K;
	for (; treeSize < N; treeSize *= 2);
	tree.resize(treeSize * 2);
	lazy.resize(treeSize * 2);
	for (int i = 0; i < N; i++) scanf("%lld", &tree[treeSize + i]);
	for (int i = treeSize - 1; i > 0; i--) tree[i] = tree[i << 1] + tree[i << 1|1];

	int a, b, c;
	LL d;
	while (M--) {
		scanf("%d", &a);
		if (a == 1) {
			scanf("%d %d %lld", &b, &c, &d);
			update(1, 0, treeSize - 1, b - 1, c - 1, d);
		}
		else {
			scanf("%d %d", &b, &c);
			printf("%lld\n", sum(1, 0, treeSize - 1, b - 1, c - 1));
		}
	}

    return 0;
}