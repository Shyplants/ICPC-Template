#include<bits/stdc++.h>

using namespace std;

const int INF = 0x3f3f3f3f;
const int MAX_N = 50 + 2;
const int MAX_V = 2*MAX_N;
const int S = MAX_V - 1;
const int E = MAX_V - 2;

typedef struct Edge {
	int to, c, cc, f;
	Edge* rev;
	Edge(int _to, int _c) : to(_to), c(_c){
		cc = c;
	}

	int spare() 
	{
		return c - f;
	}

	void addFlow(int flow)
	{
		f += flow;
		rev->f -= flow;
	}
} Edge;

int n, level[MAX_V], cache[MAX_V], row[MAX_N], col[MAX_N], tot;
vector<Edge*> adj[MAX_V];

void addEdge(int u, int v, int c)
{
	Edge *e1 = new Edge(v, c);
	Edge *e2 = new Edge(u, 0);

	e1->rev = e2;
	e2->rev = e1;

	adj[u].emplace_back(e1);
	adj[v].emplace_back(e2);
}

bool bfs()
{
	memset(level, -1, sizeof(level));
	queue<int> q;

	level[S] = 0;
	q.push(S);
	while(!q.empty()) {
		int cur = q.front(); q.pop();
		for(auto& e : adj[cur]) if(level[e->to] == -1 && e->spare()) {
			level[e->to] = level[cur] + 1;
			q.push(e->to);
		}
	}

	return level[E] != -1;
}

int dfs(int cur, int dest, int flow)
{
	if(cur == dest) return flow;

	for(int& i = cache[cur]; i<adj[cur].size(); ++i) {
		Edge* e = adj[cur][i];
		if(level[e->to] == level[cur] + 1 && e->spare()) {
			int f = dfs(e->to, dest, min(flow,e->spare()));
			
			if(f > 0) {
				e->addFlow(f);
				return f;
			}
		}
	}

	return 0;
}