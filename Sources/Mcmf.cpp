#include<bits/stdc++.h>

using namespace std;

const int INF = 0x3f3f3f3f;
const int MAX_N = 55;
const int MAX_M = 55;
const int MAX_V = MAX_N*MAX_M;
const int S = MAX_V - 1;
const int E = MAX_V - 2;
 
typedef struct Edge {
	int to, c, f, d;
	Edge* rev;

	Edge(int _to, int _c) : to(_to), c(_c) {
		d = INF;
		f = 0;
	}

	Edge(int _to, int _c, int _d) : to(_to), c(_c), d(_d) {
		f = 0;
	}

	bool spare() {
		return c - f;
	}
	
	void addFlow(int _f) {
		f += _f;
		rev->f -= _f;
	}	
}Edge;

int n, m, dist[MAX_V], _prev[MAX_V];
char board[MAX_N][MAX_M];
vector<Edge*> adj[MAX_V];
Edge* path[MAX_V];
bool InQ[MAX_V];

void addEdge(int u, int v, int c, int d)
{
	Edge *e1, *e2;
	e1 = new Edge(v, c, d);
	e2 = new Edge(u, 0, -d);

	e1->rev = e2;
	e2->rev = e1;
	
	adj[u].emplace_back(e1);
	adj[v].emplace_back(e2);
}

int dy[] = {-1, 1, 0, 0};
int dx[] = {0, 0, -1, 1};

bool OOB(int y, int x) {
	return y < 0 || y >=n || x < 0 || x >= m;
}

int main()
{
	ios_base::sync_with_stdio(0), cin.tie(0);
	
	int ans = 0;
	while(1) {
		queue<int> q;
		memset(dist, 0x3f, sizeof(dist));
		memset(InQ, 0, sizeof(InQ));
		dist[S] = 0;
		InQ[S] = true;
		q.push(S);

		while(!q.empty()) {
			int cur = q.front(); q.pop();
			InQ[cur] = false;

			for(auto& e : adj[cur]) {
				if(!e->spare() || dist[e->to] <= dist[cur] + e->d) continue;

				_prev[e->to] = cur;
				path[e->to] = e;
				dist[e->to] = dist[cur] + e->d;

				if(!InQ[e->to]) {	
					InQ[e->to] = true;
					q.push(e->to);
				}
			}
		}

		if(dist[E] == INF) break;

		for(int v = E; v != S; v = _prev[v])
		{
			path[v]->addFlow(1);
			ans -= path[v]->d;
		}
	}

	cout << ans << '\n';
	return 0;
}