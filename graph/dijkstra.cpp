// Dijkstra algorithm using priority_queue

const int INF 1 << 29;
const int MAX_V = 100;

//edge struct
struct edge{
  int to, cost;
};

//p.first is distance, p.second is vertex
typedef pair<int, int> P;

int V; //number of vertices
vector<edge> G[MAX_V]; //adjacent list graph
inr d[MAX_V];

//start from vertex s
void dijkstra(int s){
  priority_queue<P, vector<P>, greater<P> > que;
  fill(d, d+V, INF);
  d[s] = 0;
  que.push(P(0,s));
  
  while(!que.empty()){
    P p = que.top();
    que.pop();
    int v = p.second();
    if(d[v] < p.first) continue;
    for(int i = 0; i < G[v].size(); i++){
      edge e = G[v][i];
      if(d[e.to] > d[v]+e.cost){
	d[e.to] = d[v]+e.cost;
	que.push(P(d[e.to], e.to));
      }
    }
  }
}


