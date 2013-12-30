/**
    Topological sort for a DAG graph by DFS
    Complexity: O(|V|+|E|)
    Also, C++11 features demo.

    (c) Duong Nguyen
*/

#include<cstdio>
#include<iostream>
#include<algorithm>
#include<vector>
#include<cassert>
#include<fstream>

using namespace std;
const int MAXV = 100;

// Adjacent list as graph ds
vector<int> G[MAXV];
bool visited[MAXV];

void dfs(int v, vector<int>& ts){
    visited[v] = true;
    for(auto nv : G[v]){
        if(visited[nv]) continue;
        dfs(nv, ts);
    }
    ts.push_back(v);
}

// n is the number of vertices, n <= MAXV
vector<int> topsort(int n){
    auto ret = vector<int>();
    fill(visited, visited+n, false);
    for(int i = 0; i < n; i++){
        if(!visited[i]) dfs(i, ret);
    }
    reverse(ret.begin(), ret.end());
    return ret;
}

#define FROM_FILE

int main(){
#ifdef FROM_FILE
    ifstream fin("in.txt", ios::in);
#endif

    ios::sync_with_stdio(0);

    int V, E;
    fin >> V >> E;
    int from, to;
    for(int i = 0; i < E; i++){
        fin >> from >> to;
        G[from].push_back(to);
    }

    auto ans = topsort(V);
    for(auto v : ans){
        cout << v << "->";
    }
    cout << "END\n";

    if(fin.is_open()) fin.close();

    return 0;
}
