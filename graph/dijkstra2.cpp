//Dijkstra algorithm using set

const int MAX_V = 100;
const int INF = 1 << 29;
typedef pair<int, int> P;
struct edge{
  int to, cost;
};

int V;
vector<edge> G[MAX_V];
int d[MAX_V];

void dijkstra(int s){
  fill(d, d+V, INF);
  d[s] = 0;
  set<P> Q;
  Q.insert(P(0, s));
  
  while(!Q.empty()){
    P top = *Q.begin();
    Q.erase(Q.begin());
    int v = top.second();
    int d = top.first();
    
    for(int i = 0; i < G[v].size(); i++){
      edge e = G[v][i];
      if(d[e.to] > d[v]+e.cost){
	if(d[e.to] != INF){
	  Q.erase(Q.find(P(d[e.to], e.to)));

	}
	d[e.to] = d[v]+e.cost;
	Q.insert(P(d[e.to], e.to));
      }
    }
  }
}

