int n;
vector<int> data(n, -1);
bool unite(int a, int b){
  int ra = find(a);
  int rb = find(b);
  if(ra != rb){
    if(data[rb] < data[ra])
      swap(ra, rb);
    data[ra] += data[rb];
    data[rb] = ra;
  }
  return (ra != rb);
}

bool same(int a, int b){
  return find(a) == find(b);
}

int find(int a){
  return ((data[a] < 0) ? a : (data[a] = find(data[a])));
}

// -data[find(i)]: number of elems in a set containing i



