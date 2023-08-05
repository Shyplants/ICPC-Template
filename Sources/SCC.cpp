#include<bits/stdc++.h>

using namespace std;

const int MAX_V = 1e4 + 4;

// sn[i] = i가 속한 SCC 번호
int v, e, id, dfsn[MAX_V], sn[MAX_V];
vector<int> adj[MAX_V];
bool finished[MAX_V];
stack<int> st;
vector<vector<int>> SCC;

int dfs(int cur)
{
  dfsn[cur] = ++id;
  st.push(cur);

  int ret = dfsn[cur];
  for(int nxt : adj[cur])
  {
    // nxt 정점 방문되지 않은 상태
    if(dfsn[nxt] == 0) ret = min(ret, dfs(nxt));
    // nxt 정점 방문되었으나 scc 추출되지 않은 경우
    else if(!finished[nxt]) ret = min(ret, dfsn[nxt]);
  }

  if(ret == dfsn[cur])
  {
    vector<int> curSCC;
    while(1)
    {
      int v = st.top(); st.pop();
      curSCC.emplace_back(v);
      finished[v] = true;
      sn[v] = SCC.size();
      if(v == cur) break;
    }
    SCC.emplace_back(curSCC);
  }

  return ret;
}