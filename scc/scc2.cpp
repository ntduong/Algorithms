// strongly connected components in directed graph
// DFS twice algorithm
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<cstring>
#define MAXV 100

using namespace std;
int V, E; //number of vertices and edges in graph
vector<int> G[MAXV];
vector<int> rG[MAXV]; // reverse graph

vector<int> vs;
bool used[MAXV];
vector<int> cmp[MAXV];

void add_edge(int from, int to){
  G[from].push_back(to);
  rG[to].push_back(from);
}

void dfs(int v){
  used[v] = true;
  for(int i = 0; i < G[v].size(); i++){
    if(!used[G[v][i]])
      dfs(G[v][i]);
  }
  vs.push_back(v);
}

void rdfs(int v, int cnt){
  used[v] = true;
  cmp[cnt].push_back(v);
  for(int i = 0; i < rG[v].size(); i++){
    if(!used[rG[v][i]]) rdfs(rG[v][i], cnt);
  }
}

int scc(){
  memset(used, 0, sizeof(used));
  vs.clear();
  for(int v = 0; v < V; v++){
    if(!used[v])
      dfs(v);
  }
  memset(used, 0, sizeof(used));
  int cnt = 0;
  for(int i = vs.size()-1; i >= 0; i--){
    if(!used[vs[i]])
      rdfs(vs[i], cnt++);
  }
  return cnt;
}

int main(){
  cin >> V >> E;
  for(int i = 0; i < E; i++){
    int x, y;
    cin >> x >> y;
    x--, y--;
    add_edge(x, y);
  }
  int ans = scc();
  cout << ans << endl;
  
  for(int i = 0; i < ans; i++){
    cout << "Component " << i+1 << ": ";
    for(int j = 0; j < cmp[i].size(); j++){
      cout << cmp[i][j]+1 << " ";
    }
    cout << endl;
  }
  
  return 0;
}
