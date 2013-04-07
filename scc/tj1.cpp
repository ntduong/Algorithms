//Strongly connected components - Tarjan algorithm
#include<iostream>
#include<cstdio>
#include<vector>
#include<stack>
#include<algorithm>
#define MAXV 100

using namespace std;

vector<int> G[MAXV];
vector<int> scc[MAXV]; // strongly connected components

int low[MAXV], num[MAXV], time, cnt, V, E;  //cnt: number of strongly connected components
bool visited[MAXV];
stack<int> st; // to store vertices in one strongly connected component

void visit(int u){
  low[u] = num[u] = ++time;
  visited[u] = true;
  st.push(u);
  for(int i = 0; i < G[u].size(); i++){
    int v = G[u][i];
    if(num[v] == 0){
      visit(v);
      low[u] = min(low[u], low[v]);
    }
    else if(visited[v]){
      low[u] = min(low[u],num[v]);
    }
  }
  
  if(low[u] == num[u]){
    while(1){
      int w = st.top();
      st.pop();
      visited[w] = false;
      scc[cnt].push_back(w);
      if(w == u)
	break;
    }
    cnt++;
  }
}

int main(){
  cin >> V >> E;
  for(int i = 0; i < E; i++){
    int x, y;
    cin >> x >> y;
    x--, y--;
    G[x].push_back(y);
  }
  fill(low, low+V, 0);
  fill(num, num+V, 0);
  fill(visited, visited+V, false);
  for(int i = 0; i < V; i++){
    if(num[i] == 0)
      visit(i);
  }
  cout << cnt << endl;
  for(int i = 0; i < cnt; i++){
    cout << "Component " << i+1 << ": ";
    for(int j = 0; j < scc[i].size(); j++)
      cout << scc[i][j]+1 << " ";
    cout << endl;
  }
  
  return 0;
}
