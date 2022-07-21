#include<bits/stdc++.h>
using namespace std;
const int MAX_N = 5e5 + 5;
const int MAX_B = 16;
int n, m;
int dep[MAX_N], spa[MAX_B][MAX_N];
vector<int> adj[MAX_N];
void makeTree(int cur, int par) {
	for(auto& nxt : adj[cur]) if(par != nxt) {
		dep[nxt] = dep[cur] + 1;
		spa[0][nxt] = cur;
		makeTree(nxt, cur);
	}
}
int lca(int u, int v) {
	if(dep[v] > dep[u]) return lca(v, u);
	// dep[u] >= dep[v]
	int gap = dep[u] - dep[v];
	for(int i=MAX_B-1; i>=0; --i) {
		if((gap >> i) & 1) {
			u = spa[i][u];
		}
	}
	if(u == v) return u;
	for(int i=MAX_B-1; i>=0; --i) {
		if(spa[i][u] != spa[i][v]) {
			u = spa[i][u];
			v = spa[i][v];
		}
	}
	return spa[0][u];
}

int main()
{
	ios_base::sync_with_stdio(0), cin.tie(0);
	cin >> n;
	int u, v;
	for(int i=0; i<n-1; ++i) {
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	dep[1] = 0;
	memset(spa, -1, sizeof(spa));
	makeTree(1, -1);
	for(int i=1; i<MAX_B; ++i) {
		for(int j=1; j<=n; ++j) {
			if(spa[i-1][j] == -1) continue;
			spa[i][j] = spa[i-1][spa[i-1][j]];
		}
	}
	cin >> m;
	while(m--) {
		cin >> u >> v;
		cout << lca(u, v) << '\n';
	}
	return 0;
}