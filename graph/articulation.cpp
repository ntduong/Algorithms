/**
    Find all articulation (cut) points in a undirected & connected graph by DFS.
    Complexity: O(|V|+|E|)

    (c) Duong Nguyen
*/

#include<cstdio>
#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>

using namespace std;
const int MAXV = 105;

// Adjacency list as graph DS
vector<int> G[MAXV];
int visited[MAXV]; // 0: not visited, 1: gray, 2: finished
int dtime[MAXV]; // DFS discover time
int nc[MAXV]; // nc[i] := number of components due to removal of i

int dfs(int v, int ts){
    visited[v] = 1; // discovered --> gray!
    dtime[v] = ts;
    int low = ts, cp = 0;

    for(auto nv : G[v]){
        if(!visited[nv]){
            int t = dfs(nv, ts+1);
            low = min(low, t);
            if(t >= ts) cp++;
        }else if(visited[nv] == 1){
            low = min(low, dtime[nv]);
        }
    }

    if(ts > 0) cp++; // not root
    nc[v] = cp;
    visited[v] = 2; // finished -> black!

    return low;
}

vector<int> find_all_cut_points(int start, int V){
    auto ret = vector<int>();
    dfs(start,0);
    for(int i = 0; i < V; i++){
        if(nc[i] >= 2){
            ret.push_back(i);
        }
    }
    return ret;
}


#define FROM_FILE

int main(){
#ifdef FROM_FILE
    freopen("art_in.txt", "r", stdin);
#endif // FROM_FILE

    int V, E;
    cin >> V >> E;
    for(int i = 0; i < E; i++){
        int from, to;
        cin >> from >> to;
        G[from].push_back(to);
        G[to].push_back(from);
    }
    fill(visited, visited+V, 0);
    fill(dtime, dtime+V, 0);

    auto cut_points = find_all_cut_points(0, V);
    for(auto cp : cut_points) cout << cp << endl;

    return 0;
}
