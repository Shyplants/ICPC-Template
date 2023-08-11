#include<bits/stdc++.h>

using namespace std;

typedef pair<int,int> pii;
const int MAX_N = 5e3 + 3;

int dfsn[MAX_N], sn[MAX_N], id, sID;
int n;
bool finished[MAX_N];
vector<int> adj[MAX_N];
stack<int> st;

int dfs(int cur)
{
  dfsn[cur] = ++id;
  st.push(cur);

  int ret = dfsn[cur];
  for(auto nxt : adj[cur])
  {
    if(dfsn[nxt] == 0) ret = min(ret, dfs(nxt));
    else if(!finished[nxt]) ret = min(ret, dfsn[nxt]);
  }

  if(ret == dfsn[cur])
  {
    while(1)
    {
      int v = st.top(); st.pop();
      sn[v] = sID;
      finished[v] = true;

      if(v == cur) break;
    }

    sID++;
  }

  return ret;
}

int main()
{
  ios_base::sync_with_stdio(0), cin.tie(0);

  for(int i=0; i<2*k; ++i) {
    if(dfsn[i] == 0) dfs(i);
  }

  bool ans = true;
  for(int i=0; i<k; ++i) {
    if(sn[i << 1] == sn[i << 1|1]) {
      ans = false;
      break;
    }
  }

  if(!ans) {
    cout << -1 << '\n';
    return 0;
  }

  vector<int> ret(n, -1);
  vector<pii> p(n << 1);
  for(int i=0; i<2*n; ++i) {
    p[i] = make_pair(sn[i], i);
  }

  sort(p.begin(), p.end(), [](const pii& a, const pii& b) {
    return a.first > b.first;
  });

  for(int i=0; i<2*n; ++i) {
    int id = p[i].second;

    if(ret[id >> 1] == -1) {
      ret[id >> 1] = id^1;
    }
  }

  return 0;
}